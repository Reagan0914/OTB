#
# Copyright (C) 2005-2017 Centre National d'Etudes Spatiales (CNES)
#
# This file is part of Orfeo Toolbox
#
#     https://www.orfeo-toolbox.org/
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

#Contact: Jordi Inglada  <jordi.inglada@cesbio.eu>
otb_fetch_module(OTBTemporalGapFilling
  "Gapfilling for time series replaces invalid pixels (as designated by a mask)
  by an interpolation using the valid dates of the series.
A more detailed description can be found on the project website:
https://gitlab.orfeo-toolbox.org/jinglada/temporalgapfilling
"
  GIT_REPOSITORY https://gitlab.orfeo-toolbox.org/jinglada/temporalgapfilling.git
  # Commit on develop branch which includes patches for Windows support
  GIT_TAG 4fc4a71acf7b9b051cda5a3b950de2cdb9d26287
)
