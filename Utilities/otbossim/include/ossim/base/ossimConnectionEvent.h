//*******************************************************************
// Copyright (C) 2000 ImageLinks Inc. 
//
// License:  LGPL
// 
// See LICENSE.txt file in the top level directory for more details.
//
// Author: Garrett Potts
// 
//*************************************************************************
// $Id: ossimConnectionEvent.h 9094 2006-06-13 19:12:40Z dburken $
#ifndef ossimConnectionEvent_HEADER
#define ossimConnectionEvent_HEADER

#include <vector>

#include <ossim/base/ossimEventIds.h>
#include <ossim/base/ossimEvent.h>
#include <ossim/base/ossimConnectableObject.h>

class OSSIMDLLEXPORT ossimConnectionEvent : public ossimEvent
{
public:
   enum ossimConnectionDirectionType
   {
      OSSIM_DIRECTION_UNKNOWN  = 0,
      OSSIM_INPUT_DIRECTION    = 1,
      OSSIM_OUTPUT_DIRECTION   = 2,
      OSSIM_INPUT_OUTPUT_DIRECTION = 3
   };
   
   ossimConnectionEvent(ossimObject* object=NULL,
                        long id=OSSIM_EVENT_NULL_ID);

   ossimConnectionEvent(ossimObject* object,
                        long id,
                        const std::vector<ossimConnectableObject*>& newList,
                        const std::vector<ossimConnectableObject*>& oldList,
                        ossimConnectionDirectionType whichDirection);

   ossimConnectionEvent(ossimObject* object,
                        long id,
                        ossimConnectableObject* newConnectableObject,
                        ossimConnectableObject* oldConnectableObject,
                        ossimConnectionDirectionType whichDirection);
   
   ossimConnectionEvent(const ossimConnectionEvent& rhs);

   ossimObject* dup()const;
   
   virtual void setDirection(ossimConnectionDirectionType direction);
   
   virtual ossimConnectionDirectionType getDirection()const;

   virtual ossim_uint32 getNumberOfNewObjects()const;
   
   virtual ossim_uint32 getNumberOfOldObjects()const;
   
   virtual ossimConnectableObject* getOldObject(ossim_uint32 i=0)const;

   virtual ossimConnectableObject* getNewObject(ossim_uint32 i=0)const;

   virtual bool isDisconnect()const;
   
   virtual bool isConnect()const;
      
   virtual bool isInputDirection()const;
   
   virtual bool isOutputDirection()const;
   
protected:
   std::vector<ossimConnectableObject*> theNewObjectList;
   std::vector<ossimConnectableObject*> theOldObjectList;
   ossimConnectionDirectionType         theDirectionType;

TYPE_DATA
};

#endif
