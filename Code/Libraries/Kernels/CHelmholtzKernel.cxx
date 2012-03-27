/*
*
*  Copyright 2011 by the CALATK development team
*
*   Licensed under the Apache License, Version 2.0 (the "License");
*   you may not use this file except in compliance with the License.
*   You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
*   Unless required by applicable law or agreed to in writing, software
*   distributed under the License is distributed on an "AS IS" BASIS,
*   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*   See the License for the specific language governing permissions and
*   limitations under the License.
*
*
*/

#include "CHelmholtzKernel.txx"

namespace CALATK
{

template class CHelmholtzKernel< float, 1 >;
template class CHelmholtzKernel< float, 2 >;
template class CHelmholtzKernel< float, 3 >;
template class CHelmholtzKernel< double, 1 >;
template class CHelmholtzKernel< double, 2 >;
template class CHelmholtzKernel< double, 3 >;

} // namespace CALATK
