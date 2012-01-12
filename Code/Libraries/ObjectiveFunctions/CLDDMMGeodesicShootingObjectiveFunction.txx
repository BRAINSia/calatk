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

#ifndef C_LDDMM_GEODESIC_SHOOTING_OBJECTIVE_FUNCTION_TXX
#define C_LDDMM_GEODESIC_SHOOTING_OBJECTIVE_FUNCTION_TXX

template < class TState >
CLDDMMGeodesicShootingObjectiveFunction< TState >::CLDDMMGeodesicShootingObjectiveFunction()
    : DefaultNumberOfDiscretizationVolumesPerUnitTime( 10.0 ), m_ExternallySetNumberOfDiscretizationVolumesPerUnitTime( false ),
      DefaultEstimateInitialImage( false ), m_ExternallySetEstimateInitialImage( false ),
      DefaultSigmaSqr( 0.01 ), m_ExternallySetSigmaSqr( false )
{
    m_NumberOfDiscretizationVolumesPerUnitTime = DefaultNumberOfDiscretizationVolumesPerUnitTime;
    m_EstimateInitialImage = DefaultEstimateInitialImage;
    m_SigmaSqr = DefaultSigmaSqr;
}

template < class TState >
CLDDMMGeodesicShootingObjectiveFunction< TState >::~CLDDMMGeodesicShootingObjectiveFunction()
{
}

template < class TState >
void CLDDMMGeodesicShootingObjectiveFunction< TState >::SetAutoConfiguration( Json::Value& ConfValue )
{
  Superclass::SetAutoConfiguration( ConfValue );
  Json::Value& currentConfiguration = this->m_jsonConfig.GetFromKey( "LDDMMGeodesicShooting", Json::nullValue );

  SetJSONNumberOfDiscretizationVolumesPerUnitTime( this->m_jsonConfig.GetFromKey( currentConfiguration, "NumberOfDiscretizationVolumesPerUnitTime", GetExternalOrDefaultNumberOfDiscretizationVolumesPerUnitTime() ).asDouble() );
  SetJSONEstimateInitialImage( this->m_jsonConfig.GetFromKey( currentConfiguration, "EstimateInitialImage", GetExternalOrDefaultEstimateInitialImage() ).asBool() );
  SetJSONSigmaSqr( this->m_jsonConfig.GetFromKey( currentConfiguration, "SigmaSqr", GetExternalOrDefaultSigmaSqr() ).asDouble() );
}



template < class TState >
void CLDDMMGeodesicShootingObjectiveFunction< TState >::GetInitialImage( VectorImageType* ptrIm )
{
  ptrIm->copy( this->m_pState->GetPointerToInitialImage() );
}

template < class TState >
void CLDDMMGeodesicShootingObjectiveFunction< TState >::GetInitialMomentum( VectorImageType* ptrMomentum )
{
  ptrMomentum->copy( this->m_pState->GetPointerToInitialMomentum() );
}

template < class TState >
void CLDDMMGeodesicShootingObjectiveFunction< TState >::ComputeVelocity( const VectorImagePointerType ptrI, const VectorImagePointerType ptrP, VectorFieldPointerType ptrVout, VectorFieldPointerType ptrTmpField )
{
  /**
    * Computes the velocity given an image and a momentum
    * Computes
    \f[
      v = -K*(p\nabla I)
    \f]
    */

    unsigned int dim = ptrI->getDim();
    ptrVout->setConst(0);

    for ( unsigned int iD = 0; iD<dim; iD++ )
    {
        VectorFieldUtils< T, TState::VImageDimension >::computeCentralGradient( ptrI, iD, ptrTmpField );
        VectorImageUtils< T, TState::VImageDimension >::multiplyVectorByImageDimensionInPlace( ptrP, iD, ptrTmpField );
        ptrVout->addCellwise( ptrTmpField );
    }

    this->m_ptrKernel->ConvolveWithKernel( ptrVout );
    ptrVout->multConst( -1.0 );

}


#endif