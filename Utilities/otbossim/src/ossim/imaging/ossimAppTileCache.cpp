//******************************************************************
// Copyright (C) 2000 ImageLinks Inc.
//
// License:  LGPL
//
// See LICENSE.txt file in the top level directory for more details.
//
// Author: Garrett Potts
//
// Description: This file contains the Application cache algorithm
//
//***********************************
// $Id: ossimAppTileCache.cpp 9251 2006-07-13 20:04:49Z gpotts $

#include <ossim/imaging/ossimAppTileCache.h>
#include <ossim/imaging/ossimTileCache.h>
#include <ossim/base/ossimDataObject.h>
#include <ossim/base/ossimPreferences.h>

ossimAppTileCache* ossimAppTileCache::theInstance = NULL;

// we will need to grab this from the preferences
const ossim_uint32 ossimAppTileCache::DEFAULT_SIZE          = 80*1024*1024;
const ossim_uint32 ossimAppTileCache::DEFAULT_BUCKET_SIZE          = 293;
ossimAppTileCache::ossimAppCacheId ossimAppTileCache::theUniqueAppIdCounter = 1;

ossimAppTileCache *ossimAppTileCache::instance(ossim_uint32  maxSize)
{
   if(!theInstance)
   {
      if(maxSize < 1)
      {
         ossimString cacheSize = ossimPreferences::instance()->findPreference("cache_size");
         if(cacheSize!="")
         {
            maxSize = cacheSize.toUInt32()*1024*1024;
         }
         else
         {
            maxSize = DEFAULT_SIZE;
         }
         cout << "Setting SIZE----------------------- " << maxSize << std::endl;
      }
      theInstance = new ossimAppTileCache(maxSize);
   }

   return theInstance;
}

ossimAppTileCache::~ossimAppTileCache()
{
   deleteAll();
}

ossimAppTileCache::ossimAppCacheId ossimAppTileCache::newTileCache(ossim_uint32 bucketSize)
{
   ossimTileCache *aCache = NULL;
   ossimAppCacheId result = 0;

   aCache = new ossimTileCache(bucketSize);

   if(aCache)
   {
      theAppCache.insert(make_pair(theUniqueAppIdCounter, aCache));
      result = theUniqueAppIdCounter;
      ++theUniqueAppIdCounter;
   }

   return result;
}

/*!
 * Will retrieve a tile from the cache.
 */
ossimDataObject *ossimAppTileCache::get(ossimAppCacheId id,
                                        const ossimDpt3d &origin,
                                        ossim_uint32 resLevel)
{
   ossimDataObject* result = NULL;
   if(id>0)
   {
      ossimTileCache *aCache = this->get(id);
      if(aCache)
      {
         result = aCache->get(origin,
                              resLevel);
         if(result)
         {
            adjustQueue(id, origin, resLevel);
         }
      }
   }

   return result;
}

ossimDataObject* ossimAppTileCache::removeTile(ossimAppCacheId id,
                                              const ossimDpt3d &origin,
                                              unsigned long resLevel)
{
   ossimDataObject *result = NULL;
   if(id>0)
   {
      ossimTileCache *aCache = this->get(id);
      if(aCache)
      {
         // remove from cache
         result = aCache->remove(origin,
                                 resLevel);
         // adjust the byte count
         if(result)
         {
            theCurrentCacheSize -= result->getDataSizeInBytes();
         }
         removeTileFromQueue(id, origin, resLevel);
      }
   }

   return result;
}

ossimDataObject* ossimAppTileCache::insert(ossimAppCacheId appId,
                                          const ossimDpt3d &origin,
                                          const ossimDataObject* data,
                                          ossim_uint32 resLevel)
{
   static char *MODULE = "ossimAppTileCache::insert";
   ossimDataObject *result = NULL;

   // find the cache and if it's not there then return NULL
   ossimTileCache *aCache = this->get(appId);
   if(!aCache)
   {         
      return result;
   }
   
   ossimDataObject *tileToInsert = NULL;
   long dataSize = data->getDataSizeInBytes();
   
   if( (theCurrentCacheSize+dataSize) > theMaxCacheSize)
   {
      ossimDataObject *tempTile     = NULL;
      do
      {
         tempTile = removeTile();

         if(tempTile)
         {
            delete tempTile;
            tempTile = NULL;
         }
      }while((theCurrentCacheSize+dataSize) > theMaxCacheSize);
   }

   if(data)
   {
      tileToInsert = (ossimDataObject*)data->dup();

      result = aCache->insert(origin,
                              tileToInsert,
                              resLevel);
      if(!result)
      {
         cout << MODULE << " ERROR: can't insert and should not happen"
              << endl;

         delete tileToInsert;
      }
      else
      {
         theCurrentCacheSize += dataSize;
         theUsedQueue.push_back(ossimAppCacheTileInfo(appId,
                                                 origin,
                                                 resLevel));
      }
   }

   return result;
}


ossimTileCache* ossimAppTileCache::get(ossimAppCacheId id)
{
   ossimTileCache *result=NULL;
   
   AppIdIterator anIterator = theAppCache.find(id);
   
   if(anIterator != theAppCache.end())
   {
      result = (*anIterator).second;
   }

   return result;
}

void ossimAppTileCache::deleteCache(ossimAppCacheId appId)
{
   // first delete the cache
   AppIdIterator anIterator = theAppCache.find(appId);
   if(anIterator != theAppCache.end())
   {
      ossimTileCache *aCache = (*anIterator).second;
      theCurrentCacheSize -= aCache->sizeInBytes();

      delete aCache;

      theAppCache.erase(anIterator);      
   }
   // now delete all occurences of the appCacheId in the queue
   // used for LRU algorithm.
   deleteAppCacheFromQueue(appId);
}

void ossimAppTileCache::deleteAll()
{
   AppIdIterator iter = theAppCache.begin();

   while(iter != theAppCache.end())
   {
      delete (*iter).second;
      ++iter;
   }
   
   theAppCache.clear();
}

void ossimAppTileCache::removeTileFromQueue(ossimAppCacheId appId,
                                       const ossimDpt3d &origin,
                                       ossim_uint32 resLevel)
{
   list<ossimAppCacheTileInfo>::iterator anIterator;

   anIterator = theUsedQueue.begin();
   while(anIterator != theUsedQueue.end())
   {
      if( ((*anIterator).theAppCacheId == appId) &&
          ((*anIterator).theOrigin     == origin)&&
          ((*anIterator).theResLevel   == resLevel))
      {
         theUsedQueue.erase(anIterator);
         return;
      }
      else
      {
         ++anIterator;
      }
   }
}

void ossimAppTileCache::deleteAppCacheFromQueue(ossimAppCacheId appId)
{
   list<ossimAppCacheTileInfo>::iterator anIterator;

   anIterator = theUsedQueue.begin();
   while(anIterator != theUsedQueue.end())
   {
      if( (*anIterator).theAppCacheId == appId)
      {
         anIterator = theUsedQueue.erase(anIterator);
      }
      else
      {
         ++anIterator;
      }
   }
}

ossimDataObject* ossimAppTileCache::removeTile()
{
   ossimDataObject *result = NULL;
   if(!theUsedQueue.empty())
   {
      ossimAppCacheTileInfo &info = *(theUsedQueue.begin());

      ossimTileCache *aCache = get(info.theAppCacheId);
      if(aCache)
      {
         result            = aCache->remove(info.theOrigin,
                                            info.theResLevel);
         theCurrentCacheSize -= result->getDataSizeInBytes();
      }
      theUsedQueue.erase(theUsedQueue.begin());
   }

   return result;
}

void ossimAppTileCache::adjustQueue(ossimAppCacheId id,
                                    const ossimDpt3d &origin,
                                    ossim_uint32 resLevel)
{
   list<ossimAppCacheTileInfo>::iterator anIterator = theUsedQueue.begin();
   ossimAppCacheTileInfo info(id, origin, resLevel);
   
   while(anIterator != theUsedQueue.end())
   {
     
      if((*anIterator) == info)
      {
         theUsedQueue.erase(anIterator);
         theUsedQueue.push_back(info);
         return;
      }
      ++anIterator;
   }              
}
