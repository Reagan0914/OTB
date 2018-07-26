/*
 * Copyright (C) 2005-2017 Centre National d'Etudes Spatiales (CNES)
 *
 * This file is part of Orfeo Toolbox
 *
 *     https://www.orfeo-toolbox.org/
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "itkIteratorsExtern.h"

namespace itk {
// Prevent implicit instanciation of common types to improve build performance
// Explicit instanciations are provided in the .cxx

// Following template does not compile at the moment (error in ITK ?)
//template class OTBExtern_EXPORT_EXPLICIT_TEMPLATE ImageConstIterator<otb::VectorImage<double>>;
template class OTBExtern_EXPORT_EXPLICIT_TEMPLATE ImageConstIterator<otb::Image<double>>;
template class OTBExtern_EXPORT_EXPLICIT_TEMPLATE ImageRegionConstIterator<otb::VectorImage<double>>;
template class OTBExtern_EXPORT_EXPLICIT_TEMPLATE ImageRegionConstIterator<otb::Image<double>>;
template class OTBExtern_EXPORT_EXPLICIT_TEMPLATE ImageScanlineConstIterator<otb::VectorImage<double>>;
template class OTBExtern_EXPORT_EXPLICIT_TEMPLATE ImageScanlineConstIterator<otb::Image<double>>;
template class OTBExtern_EXPORT_EXPLICIT_TEMPLATE Neighborhood<double,2>;
template class OTBExtern_EXPORT_EXPLICIT_TEMPLATE ImageBoundaryCondition<otb::Image<double, 2>, otb::Image<double, 2> >;
template class OTBExtern_EXPORT_EXPLICIT_TEMPLATE ZeroFluxNeumannBoundaryCondition<otb::Image<double, 2>, otb::Image<double, 2> >;
template class OTBExtern_EXPORT_EXPLICIT_TEMPLATE itk::ConstNeighborhoodIterator<otb::Image<double, 2> >;

template class OTBExtern_EXPORT_EXPLICIT_TEMPLATE ImageConstIterator<otb::Image<float>>;
template class OTBExtern_EXPORT_EXPLICIT_TEMPLATE ImageRegionConstIterator<otb::VectorImage<float>>;
template class OTBExtern_EXPORT_EXPLICIT_TEMPLATE ImageRegionConstIterator<otb::Image<float>>;
template class OTBExtern_EXPORT_EXPLICIT_TEMPLATE ImageScanlineConstIterator<otb::VectorImage<float>>;
template class OTBExtern_EXPORT_EXPLICIT_TEMPLATE ImageScanlineConstIterator<otb::Image<float>>;
template class OTBExtern_EXPORT_EXPLICIT_TEMPLATE Neighborhood<float,2>;
template class OTBExtern_EXPORT_EXPLICIT_TEMPLATE ImageBoundaryCondition<otb::Image<float, 2>, otb::Image<float, 2> >;
template class OTBExtern_EXPORT_EXPLICIT_TEMPLATE ZeroFluxNeumannBoundaryCondition<otb::Image<float, 2>, otb::Image<float, 2> >;
template class OTBExtern_EXPORT_EXPLICIT_TEMPLATE itk::ConstNeighborhoodIterator<otb::Image<float, 2> >;
}