/*=========================================================================

  Program:   Insight Segmentation & Registration Toolkit
  Module:    $RCSfile: itkAzimuthElevationToCartesianTransform.txx,v $
  Language:  C++
  Date:      $Date: 2006-10-14 19:58:31 $
  Version:   $Revision: 1.19 $

  Copyright (c) Insight Software Consortium. All rights reserved.
  See ITKCopyright.txt or http://www.itk.org/HTML/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even 
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifndef __itkAzimuthElevationToCartesianTransform_txx
#define __itkAzimuthElevationToCartesianTransform_txx

#include "itkAzimuthElevationToCartesianTransform.h"

namespace itk
{

// Constructor with default arguments
template<class TScalarType, unsigned int NDimensions>
AzimuthElevationToCartesianTransform<TScalarType, NDimensions>::
AzimuthElevationToCartesianTransform()
// add this construction call when deriving from itk::Transform
// :Superclass(SpaceDimension,ParametersDimension)
{
  m_MaxAzimuth = 0;
  m_MaxElevation = 0;
  m_RadiusSampleSize = 1;
  m_AzimuthAngularSeparation = 1;
  m_ElevationAngularSeparation = 1;
  m_FirstSampleDistance = 0;
  m_ForwardAzimuthElevationToPhysical = true;

}

// Destructor
template<class TScalarType, unsigned int NDimensions>
AzimuthElevationToCartesianTransform<TScalarType, NDimensions>::
~AzimuthElevationToCartesianTransform()
{
  return;
}


// Print self
template<class TScalarType, unsigned int NDimensions>
void
AzimuthElevationToCartesianTransform<TScalarType, NDimensions>::
PrintSelf(std::ostream &os, Indent indent) const
{
  Superclass::PrintSelf(os,indent);

  os << indent << "x = z*tan(Azimuth)" << std::endl;
  os << indent << "y = z*tan(Elevation)" << std::endl;
  os << indent << "z = sqrt(r*r * cos(Azimuth)*cos(Azimuth) "
     << " / (1 + cos(Azimuth) * cos(Azimuth) * tan(Elevation)"
     << "* tan(Elevation)))" << std::endl;
  os << indent << "Azimuth = 1 / (tan(x/y))" << std::endl;
  os << indent << "Elevation = 1 / (tan(y/z))" << std::endl;
  os << indent << "r = sqrt(x*x + y*y + z*z)" << std::endl;
  os << indent << "m_MaxAzimuth = " << m_MaxAzimuth << std::endl;
  os << indent << "m_MaxElevation = " << m_MaxElevation << std::endl;
  os << indent << "m_RadiusSampleSize = " << m_RadiusSampleSize << std::endl;
  os << indent << "m_AzimuthAngularSeparation = ";
  os << indent << m_AzimuthAngularSeparation << std::endl;
  os << indent << "m_ElevationAngularSeparation = ";
  os << indent << m_ElevationAngularSeparation << std::endl;
  os << indent << "m_FirstSampleDistance = "; 
  os << indent << m_FirstSampleDistance << std::endl;
  os << indent << "m_ForwardAzimuthElevationToPhysical = ";
  os << indent << (m_ForwardAzimuthElevationToPhysical ? "True" : "False");
  os << indent << std::endl;
}


template<class TScalarType, unsigned int NDimensions>
typename AzimuthElevationToCartesianTransform<TScalarType, NDimensions>
::OutputPointType
AzimuthElevationToCartesianTransform<TScalarType, NDimensions>::
TransformPoint(const InputPointType &point) const 
{
  OutputPointType result;
  if (m_ForwardAzimuthElevationToPhysical)
    {
    result = TransformAzElToCartesian(point);
    }
  else
    {
    result = TransformCartesianToAzEl(point);
    }
  return result;
}


/** Transform a point, from azimuth-elevation to cartesian */
template<class TScalarType, unsigned int NDimensions>
typename AzimuthElevationToCartesianTransform<TScalarType, NDimensions>
::OutputPointType
AzimuthElevationToCartesianTransform<TScalarType, NDimensions>::
TransformAzElToCartesian(const InputPointType &point) const 
{
  OutputPointType result;
  ScalarType Azimuth = ((2*vnl_math::pi) / 360) 
                       * (point[0]*m_AzimuthAngularSeparation 
                       - ((m_MaxAzimuth-1)/2.0) );
  ScalarType Elevation   = ((2*vnl_math::pi) / 360) 
                           * (point[1]*m_ElevationAngularSeparation 
                           - ((m_MaxElevation-1)/2.0) );
  ScalarType r = (m_FirstSampleDistance + point[2]) * m_RadiusSampleSize;

  ScalarType cosOfAzimuth = vcl_cos(Azimuth);
  ScalarType tanOfElevation = vcl_tan(Elevation);
  result[2] = vcl_sqrt((r*r*cosOfAzimuth*cosOfAzimuth)
                   / (1 + cosOfAzimuth * cosOfAzimuth * tanOfElevation
                   * tanOfElevation));
  result[0] = result[2] * vcl_tan(Azimuth);
  result[1] = result[2] * tanOfElevation;
  return result;
}

template<class TScalarType, unsigned int NDimensions>
typename AzimuthElevationToCartesianTransform<TScalarType, NDimensions>
::OutputPointType
AzimuthElevationToCartesianTransform<TScalarType, NDimensions>::
TransformCartesianToAzEl(const OutputPointType &point) const 
{
  InputPointType result;       // Converted point
  result[0] = (atan(point[0] / point[2])) * (360 / (2*vnl_math::pi)) 
                                            + ((m_MaxAzimuth-1)/2.0);
  result[1] = (atan(point[1] / point[2])) * (360 / (2*vnl_math::pi)) 
                                            + ((m_MaxElevation-1)/2.0);
  result[2] = ((sqrt( point[0] * point[0] +
                      point[1] * point[1] +
                      point[2] * point[2]) / m_RadiusSampleSize) 
                      - m_FirstSampleDistance);
  return result;
}


// Set parameters
template<class TScalarType, unsigned int NDimensions>
void
AzimuthElevationToCartesianTransform<TScalarType, NDimensions>::
SetAzimuthElevationToCartesianParameters(const double sampleSize, 
                                         const double firstSampleDistance,
                                         const long maxAzimuth, 
                                         const long maxElevation,
                                         const double azimuthAngleSeparation,
                                         const double elevationAngleSeparation)
{
  SetMaxAzimuth(static_cast<long>(static_cast<double>(maxAzimuth) 
                                                   * azimuthAngleSeparation));
  SetMaxElevation(static_cast<long>(static_cast<double>(maxElevation) 
                                                 * elevationAngleSeparation));
  SetRadiusSampleSize(sampleSize);
  SetAzimuthAngularSeparation(azimuthAngleSeparation);
  SetElevationAngularSeparation(elevationAngleSeparation);
  SetFirstSampleDistance(firstSampleDistance / sampleSize);
}

template<class TScalarType, unsigned int NDimensions>
void
AzimuthElevationToCartesianTransform<TScalarType, NDimensions>::
SetAzimuthElevationToCartesianParameters(const double sampleSize, 
                                         const double firstSampleDistance,
                                         const long maxAzimuth, 
                                         const long maxElevation )
{
  SetAzimuthElevationToCartesianParameters(sampleSize, firstSampleDistance, 
                                          maxAzimuth, maxElevation, 1.0, 1.0);
}


template<class TScalarType, unsigned int NDimensions>
void
AzimuthElevationToCartesianTransform<TScalarType, NDimensions>::
SetForwardAzimuthElevationToCartesian()
{
  m_ForwardAzimuthElevationToPhysical = true;
}


template<class TScalarType, unsigned int NDimensions>
void
AzimuthElevationToCartesianTransform<TScalarType, NDimensions>::
SetForwardCartesianToAzimuthElevation()
{
  m_ForwardAzimuthElevationToPhysical = false;
}


}//namespace
#endif
