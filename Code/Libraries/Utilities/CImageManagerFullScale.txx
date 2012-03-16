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

#ifndef C_IMAGE_MANAGER_FULL_SCALE_TXX
#define C_IMAGE_MANAGER_FULL_SCALE_TXX

//
// empty constructor
//
template <class T, unsigned int VImageDimension >
CImageManagerFullScale< T, VImageDimension >::CImageManagerFullScale()
  : DefaultSigma( 0.05 ), DefaultBlurImage( false ), m_ExternallySetSigma( false ), m_ExternallySetBlurImage( false )
{
  m_BlurImage = DefaultBlurImage;
  SetSigma( DefaultSigma );
}

//
// destructor
//
template <class T, unsigned int VImageDimension >
CImageManagerFullScale< T, VImageDimension >::~CImageManagerFullScale()
{
}

//
// SetSigma
//
template <class T, unsigned int VImageDimension >
void CImageManagerFullScale< T, VImageDimension >::SetSigma( T dSigma )
{
  m_Sigma = dSigma;
  m_GaussianKernel.SetSigma( m_Sigma );
}

//
// Loads image and potentially transform for a given image information structure
//
template <class T, unsigned int VImageDimension >
void CImageManagerFullScale< T, VImageDimension>::GetImage( ImageInformation* imageInformation )
{
  // do we need to load the image?
  if ( imageInformation->Image.GetPointer() == NULL )
    {
    if ( imageInformation->ImageFileName.compare("")!=0 ) // set to something
      {
      // load it
      std::cout << "Loading " << imageInformation->ImageFileName << " ... ";
      imageInformation->Image = VectorImageUtils< T, VImageDimension>::readFileITK( imageInformation->ImageFileName );


      if ( this->GetAutoScaleImages() )
      {
        std::cout << " auto-scaling ... ";
        CALATK::VectorImageUtils< T, VImageDimension >::normalizeClampNegativeMaxOne( imageInformation->Image );
      }

      // determine min max
      T dMinVal = CALATK::VectorImageUtils< T, VImageDimension >::minAll( imageInformation->Image );
      T dMaxVal = CALATK::VectorImageUtils< T, VImageDimension >::maxAll( imageInformation->Image );

      if ( m_BlurImage )
        {
        std::cout << "WARNING: blurring the original image" << std::endl;
        this->m_GaussianKernel.ConvolveWithKernel( imageInformation->Image );
        }

      imageInformation->OriginalImage = imageInformation->Image;
      std::cout << "done. [" << dMinVal << "," << dMaxVal << "] " << std::endl;

      if ( dMinVal < 0 || dMaxVal > 1 )
      {
        std::cout << "WARNING: Recommended scale for image intensities is [ 0 , 1 ]." << std::endl;
      }

      }
    }
  
  // do we need to load the transform?
  if ( imageInformation->pTransform.GetPointer() == NULL )
    {
    if ( imageInformation->ImageTransformationFileName.compare("")!=0 ) // set to something
      {
      // load it
      
      assert( imageInformation->Image.GetPointer() != NULL ); // image should have been loaded in previous step
      
      typename VectorFieldType::Pointer mapTrans;
      unsigned int szX, szY, szZ;
      T spX, spY, spZ;
      
      switch ( VImageDimension )
        {
        case 2:
          szX = imageInformation->Image->GetSizeX();
          szY = imageInformation->Image->GetSizeY();
          spX = imageInformation->Image->GetSpacingX();
          spY = imageInformation->Image->GetSpacingY();
          mapTrans = new VectorFieldType( szX, szY );
          mapTrans->SetSpacingX( spX );
          mapTrans->SetSpacingY( spY );
          break;
        case 3:
          szX = imageInformation->Image->GetSizeX();
          szY = imageInformation->Image->GetSizeY();
          szZ = imageInformation->Image->GetSizeZ();
          spX = imageInformation->Image->GetSpacingX();
          spY = imageInformation->Image->GetSpacingY();
          spZ = imageInformation->Image->GetSpacingZ();
          mapTrans = new VectorFieldType( szX, szY, szZ );
          mapTrans->SetSpacingX( spX );
          mapTrans->SetSpacingY( spY );
          mapTrans->SetSpacingZ( spZ );
          break;
        default:
          throw std::runtime_error( "Dimension not supported for transform" );
        }
      
      
      VectorFieldUtils<T, VImageDimension>::identityMap( mapTrans );
      
      std::cout << "Initializing affine map for source image" << std::endl;
      typename ITKAffineTransform<T,VImageDimension>::Type::Pointer aTrans = VectorImageUtils< T, VImageDimension>::readAffineTransformITK( imageInformation->ImageTransformationFileName );
      VectorFieldUtils< T, VImageDimension>::affineITKtoMap( aTrans, mapTrans );
      
      imageInformation->pTransform = mapTrans;
      
      }
    }
}

#endif
