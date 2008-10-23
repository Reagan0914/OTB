//*******************************************************************
// Copyright (C) 2000 ImageLinks Inc.
//
// License:  See top level LICENSE.txt file.
//
// Author:  Garrett Potts
//
// Description:
//
// MeanRadialLens distortion.
//*******************************************************************
//  $Id: ossimMeanRadialLensDistortion.cpp 11024 2007-05-23 17:56:00Z gpotts $
#include <ossim/projection/ossimMeanRadialLensDistortion.h>

#include <ossim/base/ossimCommon.h>
#include <ossim/base/ossimKeywordlist.h>
#include <ossim/base/ossimString.h>

RTTI_DEF1(ossimMeanRadialLensDistortion, "ossimMeanRadialLensDistortion", ossimLensDistortion);

void ossimMeanRadialLensDistortion::solveCoefficients(const std::vector<double>& radialDistance,
                                                      const std::vector<double>& radialDistortion)
{
   NEWMAT::ColumnVector distanceVec((int)radialDistance.size());
   NEWMAT::ColumnVector distortionVec((int)radialDistortion.size());
   ossim_uint32 idx = 0;

   theCoefficients[0] = 0;
   theCoefficients[1] = 0;
   theCoefficients[2] = 0;
   theCoefficients[3] = 0;
   if(radialDistance.size() == radialDistortion.size())
   {
      for(idx = 0; idx < radialDistance.size();++idx)
      {
         distanceVec[idx]   = radialDistance[idx];
         distortionVec[idx] = radialDistortion[idx];
      }
      solveCoefficients(distanceVec,
                        distortionVec);
   }
}

void ossimMeanRadialLensDistortion::solveCoefficients(const NEWMAT::ColumnVector &radialDistance,
                                                      const NEWMAT::ColumnVector &radialDistortion)
{
   NEWMAT::ColumnVector coefficients(4);
   theCoefficients.resize(4);
   theCoefficients[0] = 0;
   theCoefficients[1] = 0;
   theCoefficients[2] = 0;
   theCoefficients[3] = 0;
   if((radialDistance.Nrows() == 0) ||
      (radialDistortion.Nrows() == 0))
   {
      return;
   }
   if(radialDistance.Nrows() == radialDistortion.Nrows())
   {
      NEWMAT::Matrix M(radialDistance.Nrows(), 4);
      
      // set up the matrix
      for(long row = 0; row < M.Nrows(); row++)
      {
         M[row][0] = radialDistance[row];
         M[row][1] = M[row][0]*radialDistance[row]*radialDistance[row];
         M[row][2] = M[row][1]*radialDistance[row]*radialDistance[row];
         M[row][3] = M[row][2]*radialDistance[row]*radialDistance[row];
      }
      
      NEWMAT::Matrix mTranspose = M.t();
      coefficients = ((mTranspose*M).i())*(mTranspose*radialDistortion);

      theCoefficients[0] = coefficients[0];
      theCoefficients[1] = coefficients[1];
      theCoefficients[2] = coefficients[2];
      theCoefficients[3] = coefficients[3];
   }
   else
   {
   }
}

double ossimMeanRadialLensDistortion::deltaR(double radius)const
{
  double r3 = radius*radius*radius;
  double r5 = r3*radius*radius;
  double r7 = r5*radius*radius;

  return (radius*theCoefficients[0] +r3*theCoefficients[1] + r5*theCoefficients[2] + r7*theCoefficients[3]);
}

void ossimMeanRadialLensDistortion::distort(const ossimDpt& input, ossimDpt& output)const
{
   int iters = 0;

   //***
   // Begin with guess. Forward transform is defined as trasforming left to
   // right. We are therefore solving for left:
   //***
   ossimDpt left (input);
   ossimDpt left_dx;
   ossimDpt left_dy;
   ossimDpt right;
   ossimDpt right_dx;
   ossimDpt right_dy;
   ossimDpt dr_dx;
   ossimDpt dr_dy;
   ossimDpt r_diff;
   ossimDpt l_diff;
   double inverse_norm;
   
   //***
   // Begin iterations:
   //***
   do
   {
      //***
      // establish perturbed image points about the guessed point:
      //***
      left_dx.x = left.x + 1.0;
      left_dx.y = left.y;
      left_dy.x = left.x;
      left_dy.y = left.y + 1.0;
      
      //***
      // Compute numerical partials at current guessed point:
      //***
      undistort(left,    right);
      undistort(left_dx, right_dx);
      undistort(left_dy, right_dy);

      dr_dx.x = (right_dx.x - right.x); //e
      dr_dx.y = (right_dx.y - right.y); //g
      dr_dy.x = (right_dy.x - right.x); //f
      dr_dy.y = (right_dy.y - right.y); //h

      //***
      // Test for convergence:
      //***
      r_diff = input - right;
      
      //***
      // Compute linearized estimate of image point given gp delta:
      //***
      inverse_norm = dr_dy.u*dr_dx.v - dr_dx.u*dr_dy.v; // fg-eh
      if (inverse_norm != 0)
      {
          l_diff.u = (-dr_dy.v*r_diff.u + dr_dy.u*r_diff.v)/inverse_norm;
          l_diff.v = ( dr_dx.v*r_diff.u - dr_dx.u*r_diff.v)/inverse_norm;
          left += l_diff;
      }
      else
      {
         l_diff.u = 0;
         l_diff.v = 0;
      }

      iters++;
      
   } while (((fabs(l_diff.u) > theConvergenceThreshold) ||
             (fabs(l_diff.v) > theConvergenceThreshold)) &&
            (iters < theMaxIterations));


   output = left;
}

void ossimMeanRadialLensDistortion::undistort(const ossimDpt& input, ossimDpt& output)const
{
   ossimDpt deltaPosition(input.x - theCenter.x,
                          input.y - theCenter.y);
   double r = sqrt(deltaPosition.x*deltaPosition.x + 
                   deltaPosition.y*deltaPosition.y);
   double deltaRadius = deltaR(r);
   
   if((fabs(r) <= FLT_EPSILON)||
      (fabs(deltaRadius) <= FLT_EPSILON))
   {
      output = input;
      return;
   }
   
   double deltaX      = (deltaPosition.x*(deltaRadius/r)); 
   double deltaY      = (deltaPosition.y*(deltaRadius/r)); 
   
   output.x = deltaPosition.x-deltaX;
   output.y = deltaPosition.y-deltaY;
}

bool ossimMeanRadialLensDistortion::saveState(ossimKeywordlist& kwl,
                                              const char* prefix)const
{
   kwl.add(prefix,
           "k0",
           theCoefficients[0],
           true);
   
   kwl.add(prefix,
           "k1",
           theCoefficients[1],
           true);
   kwl.add(prefix,
           "k2",
           theCoefficients[2],
           true);
   
   kwl.add(prefix,
           "k3",
           theCoefficients[3],
           true);

   return ossimLensDistortion::saveState(kwl, prefix);
}

bool ossimMeanRadialLensDistortion::loadState(const ossimKeywordlist& kwl,
                                              const char* prefix)
{
   const char* k0 = kwl.find(prefix, "k0");
   const char* k1 = kwl.find(prefix, "k1");
   const char* k2 = kwl.find(prefix, "k2");
   const char* k3 = kwl.find(prefix, "k3");

   if(k1&&k2&&k3&&k3)
   {
      theCoefficients[0] = ossimString(k0).toDouble();
      theCoefficients[1] = ossimString(k1).toDouble();
      theCoefficients[2] = ossimString(k2).toDouble();
      theCoefficients[3] = ossimString(k3).toDouble();
   }
   else
   {
      std::vector<double> distances;
      std::vector<double> distortions;
      ossim_uint32 idx = 0;
      const char* distance   = kwl.find(prefix, "distance0");
      const char* distortion = kwl.find(prefix, "distortion0");

      while(distance&&distortion)
      {
         distances.push_back(ossimString(distance).toDouble());
         distortions.push_back(ossimString(distortion).toDouble());
         ++idx;
         distance   = kwl.find(prefix,
                               ossimString("distance")+ossimString::toString(idx));
         distortion = kwl.find(prefix,
                               ossimString("distortion")+ossimString::toString(idx));
      }

      solveCoefficients(distances, distortions);
   }

   return ossimLensDistortion::loadState(kwl, prefix);
   
}
