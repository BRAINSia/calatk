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

#ifndef C_LDDMM_SIMPLIFIED_GEODESIC_SHOOTING_OBJECTIVE_FUNCTION_H
#define C_LDDMM_SIMPLIFIED_GEODESIC_SHOOTING_OBJECTIVE_FUNCTION_H

#include "CLDDMMGeodesicShootingObjectiveFunction.h"
#include "CALATKCommon.h"
#include "LDDMMUtils.h"

namespace CALATK
{
/**
  * Implements a simplified geodesic shooting method inspired by
  *
  * Ashburner et al., ...
  *
  * However, instead of computing the solution propagating the vector-valued momentum forward,
  * here the gradient descent is performed directly on the initial Hamiltonian momentum (the adjoint to the image).
  *
  * Is computationally more efficient than the full adjoint solution and requires only little memory.
  */

template < class TState >
class CLDDMMSimplifiedGeodesicShootingObjectiveFunction
    : public CLDDMMGeodesicShootingObjectiveFunction< TState >
{
public:

  /* Some useful typedefs */

  typedef CLDDMMGeodesicShootingObjectiveFunction< TState > Superclass;

  typedef typename TState::TFloat T;

  typedef typename Superclass::CEnergyValues CEnergyValues;

  typedef typename Superclass::VectorImageType VectorImageType;
  typedef typename Superclass::VectorFieldType VectorFieldType;

  CLDDMMSimplifiedGeodesicShootingObjectiveFunction();
  virtual ~CLDDMMSimplifiedGeodesicShootingObjectiveFunction();

  void InitializeState();
  void InitializeState( TState* pState );

  void GetImage( VectorImageType* ptrIm, T dTime );
  void GetMomentum( VectorImageType* ptrMomentum, T dTime );

  void GetMap( VectorFieldType* ptrMap, T dTime );
  void GetMapFromTo(VectorFieldType *ptrMap, T dTimeFrom, T dTimeTo);

  CEnergyValues GetCurrentEnergy();
  void ComputeGradient();

  void OutputStateInformation( unsigned int uiIter, std::string outputPrefix="" );

protected:

  void DeleteData();

private:
  // maps to keep track of the current deformation (and temporary storage for the solver)
  VectorFieldPointerType m_ptrMapIn; // map for the numerical solution
  VectorFieldPointerType m_ptrMapOut; // map for the numerical solution
  VectorFieldPointerType m_ptrMapTmp; // map for the numerical solution

  VectorImagePointerType m_ptrDeterminantOfJacobian;

};

#include "CLDDMMSimplifiedGeodesicShootingObjectiveFunction.txx"

} // end namespace

#endif // C_LDDMM_SIMPLIFIED_GEODESIC_SHOOTING_OBJECTIVE_FUNCTION_H