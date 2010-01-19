/*=========================================================================

  Program:   ORFEO Toolbox
  Language:  C++
  Date:      $Date$
  Version:   $Revision$


  Copyright (c) Centre National d'Etudes Spatiales. All rights reserved.
  See OTBCopyright.txt for details.


     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#if defined(_MSC_VER)
#pragma warning ( disable : 4786 )
#endif

#ifdef __BORLANDC__
#define ITK_LEAN_AND_MEAN
#endif

//  Software Guide : BeginCommandLineArgs
//    INPUTS: {QB_Suburb.png}, {QB_SuburbR10X13Y17.png}
//    OUTPUTS: {AffineTransformationOutput.png}
//    2 3 0 0 0.5 1 AffineTransformationTxtOutput.txt
//  Software Guide : EndCommandLineArgs

// Software Guide : BeginLatex
//
// This example demonstrates the use of the
// \doxygen{otb}{KeyPointSetsMatchingFilter} for transformation 
// estimation between 2 images. The idea here is to match SIFTs extracted from both the
// fixed and the moving images. The use of SIFTs is demonstrated in
// section \ref{sec:SIFTDetector}. The
// \doxygen{otb}{LeastSquareAffineTransformEstimator} will be used
// to generate a transformation field by using
// mean square optimisation to estimate
// an affine transfrom from the point set.
//
// The first step toward the use of these filters is to include the
// appropriate header files.
//
// Software Guide : EndLatex


// Software Guide : BeginCodeSnippet

#include "otbKeyPointSetsMatchingFilter.h"
#include "otbImageToSIFTKeyPointSetFilter.h"

// Disabling deprecation warning if on visual
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4996)
#endif
#include "itkDeformationFieldSource.h"
// Enabling remaining deprecation warning
#ifdef _MSC_VER
#pragma warning(pop)
#endif


// Software Guide : EndCodeSnippet

#include "otbImage.h"
#include "otbMacro.h"
#include "otbImageFileReader.h"
#include "otbImageFileWriter.h"
#include "itkPointSet.h"
#include "otbLeastSquareAffineTransformEstimator.h"
#include "itkResampleImageFilter.h"

int main (int argc, char* argv[])
{
  if (argc!= 11)
  {
    std::cerr <<"Usage: "<<argv[0];
    std::cerr<<"fixedFileName movingFileName resamplingImageFileName octaves scales threshold ratio secondOrderThreshold useBackMatching transfofname" << std::endl;
    return EXIT_FAILURE;
  }

  const char * fixedfname           = argv[1];
  const char * movingfname          = argv[2];
  const char * outputImageFilename  = argv[3];
  
  const unsigned int octaves        = atoi(argv[4]);
  const unsigned int scales         = atoi(argv[5]);
  float threshold                   = atof(argv[6]);
  float ratio                       = atof(argv[7]);
  const double secondOrderThreshold = atof(argv[8]);
  const bool useBackMatching        = atoi(argv[9]);
  const char * outputTransformationFilename  = argv[10];
  
  const unsigned int Dimension      = 2;

  // Software Guide : BeginLatex
  //
  // Then we must decide what pixel type to use for the image. We choose to do
  // all the computations in floating point precision and rescale the results
  // between 0 and 255 in order to export PNG images.
  //
  // Software Guide : EndLatex

  // Software Guide : BeginCodeSnippet

  typedef double        RealType;
  typedef unsigned char OutputPixelType;

  typedef otb::Image<RealType,Dimension>        ImageType;
  typedef otb::Image<OutputPixelType,Dimension> OutputImageType;

  // Software Guide : EndCodeSnippet
  // Software Guide : BeginLatex
  //
  // The SIFTs obtained for the matching will be stored in vector
  // form inside a point set. So we need the following types:
  //
  // Software Guide : EndLatex

  // Software Guide : BeginCodeSnippet

  typedef itk::VariableLengthVector<RealType>     RealVectorType;
  typedef itk::PointSet<RealVectorType,Dimension> PointSetType;

  // Software Guide : EndCodeSnippet
 // Software Guide : BeginLatex
  //
  // The filter for computing the SIFTs has a type defined as follows:
  //
  // Software Guide : EndLatex

  // Software Guide : BeginCodeSnippet

  //typedef otb::SiftFastImageFilter<ImageType,PointSetType>
  //ImageToSIFTKeyPointSetFilterType;
  typedef otb::ImageToSIFTKeyPointSetFilter<ImageType,PointSetType>
  ImageToSIFTKeyPointSetFilterType;

  // Software Guide : EndCodeSnippet
// Software Guide : BeginLatex
  //
  // Although many choices for evaluating the distances during the
  // matching procedure exist, we choose here to use a simple
  // Euclidean distance. We can then define the type for the matching filter.
  //
  // Software Guide : EndLatex

  // Software Guide : BeginCodeSnippet

  typedef itk::Statistics::EuclideanDistance<RealVectorType> DistanceType;
  typedef otb::KeyPointSetsMatchingFilter<PointSetType, DistanceType>
  EuclideanDistanceMatchingFilterType;
  // Software Guide : EndCodeSnippet
  // Software Guide : BeginLatex
  //
  // The following types are needed for dealing with the matched points.
  //
  // Software Guide : EndLatex

  // Software Guide : BeginCodeSnippet

  typedef PointSetType::PointType           PointType;
  typedef std::pair<PointType,PointType>    MatchType;
  typedef std::vector<MatchType> MatchVectorType;
  typedef EuclideanDistanceMatchingFilterType::LandmarkListType
  LandmarkListType;

  typedef PointSetType::PointsContainer    PointsContainerType;
  typedef PointsContainerType::Iterator    PointsIteratorType;
  typedef PointSetType::PointDataContainer PointDataContainerType;
  typedef PointDataContainerType::Iterator PointDataIteratorType;

  // Software Guide : EndCodeSnippet


  // Software Guide : BeginLatex
  //
  // We define the type for the image reader.
  //
  // Software Guide : EndLatex

  // Software Guide : BeginCodeSnippet

  typedef otb::ImageFileReader<ImageType> ReaderType;

  // Software Guide : EndCodeSnippet

  // Software Guide : BeginLatex
  //
  // Two readers are instantiated : one for the fixed image, and one
  // for the moving image.
  //
  // Software Guide : EndLatex

  // Software Guide : BeginCodeSnippet

  ReaderType::Pointer fixedReader  = ReaderType::New();
  ReaderType::Pointer movingReader = ReaderType::New();

  fixedReader->SetFileName(fixedfname);
  movingReader->SetFileName(movingfname);
  fixedReader->UpdateOutputInformation();
  movingReader->UpdateOutputInformation();

  // Software Guide : EndCodeSnippet
  // Software Guide : BeginLatex
  //
  // We will now instantiate the 2 SIFT filters and the filter used
  // for the matching of the points.
  //
  // Software Guide : EndLatex

  // Software Guide : BeginCodeSnippet

  ImageToSIFTKeyPointSetFilterType::Pointer filter1 =
    ImageToSIFTKeyPointSetFilterType::New();
  ImageToSIFTKeyPointSetFilterType::Pointer filter2 =
    ImageToSIFTKeyPointSetFilterType::New();
  EuclideanDistanceMatchingFilterType::Pointer euclideanMatcher =
    EuclideanDistanceMatchingFilterType::New();

  // Software Guide : EndCodeSnippet
  // Software Guide : BeginLatex
  //
  // We plug the pipeline and set the parameters.
  //
  // Software Guide : EndLatex

  // Software Guide : BeginCodeSnippet

  filter1->SetInput( fixedReader->GetOutput() );
  filter2->SetInput( movingReader->GetOutput() );
  
  filter1->SetOctavesNumber(octaves);
  filter1->SetScalesNumber(scales);

  filter1->SetDoGThreshold(threshold);
  filter1->SetEdgeThreshold(ratio);

  filter2->SetOctavesNumber(octaves);
  filter2->SetScalesNumber(scales);

  filter2->SetDoGThreshold(threshold);
  filter2->SetEdgeThreshold(ratio);
// Software Guide : EndCodeSnippet


  // Software Guide : BeginLatex
  //
  // We use a simple Euclidean distance to select
  // matched points.
  //
  // Software Guide : EndLatex

  // Software Guide : BeginCodeSnippet

  euclideanMatcher->SetInput1(filter1->GetOutput());
  euclideanMatcher->SetInput2(filter2->GetOutput());

  euclideanMatcher->SetDistanceThreshold(secondOrderThreshold);
  euclideanMatcher->SetUseBackMatching(useBackMatching);
  //std::cout << "Update euclidian distance" << std::endl;
  euclideanMatcher->Update();

  // Software Guide : EndCodeSnippet



  // Software Guide : BeginLatex
  //
  // The matched points will be stored into a landmark list.
  //
  // Software Guide : EndLatex

  // Software Guide : BeginCodeSnippet

  LandmarkListType::Pointer landmarkList;
  landmarkList = euclideanMatcher->GetOutput();
  //std::cout << "Get landmarkList" << std::endl;
  // Software Guide : EndCodeSnippet

 // Software Guide : BeginLatex
  //
  // Apply Mean square algorithm
  //
  // Software Guide : EndLatex
// Software Guide : BeginCodeSnippet
  typedef itk::Point<double,2>                                 MyPointType;
  typedef otb::LeastSquareAffineTransformEstimator<MyPointType> EstimatorType;
  
  // instantiation
  EstimatorType::Pointer estimator = EstimatorType::New();
  std::cout << "landmark list size " << landmarkList->Size() << std::endl;  
  for (LandmarkListType::Iterator it = landmarkList->Begin();
     it != landmarkList->End(); ++it)
  {       
        //std::cout << "landmark1" << it.Get()->GetPoint1() << std::endl;   
        //std::cout << "landmark2" << it.Get()->GetPoint2() << std::endl;        
        estimator->AddTiePoints(it.Get()->GetPoint1(),it.Get()->GetPoint2());
  }

  // Trigger computation
  estimator->Compute();
  // meanSquarestimator->SetInput(euclideanMatcher->GetOutput());
// Software Guide : EndCodeSnippet

 // Software Guide : BeginLatex
  //
  // Resample the initial image with the transformation evaluated
  //
  // Software Guide : EndLatex
//  Software Guide : BeginLatex
  //
  //  It is common, as the last step of a registration task, to use
  //  the resulting transform to map the moving image into the fixed
  //  image space.  This is easily done with the
  //  \doxygen{itk}{ResampleImageFilter}. First, a ResampleImageFilter
  //  type is instantiated using the image types. It is convenient to
  //  use the fixed image type as the output type since it is likely
  //  that the transformed moving image will be compared with the
  //  fixed image.
  //
  //  Software Guide : EndLatex

  // Software Guide : BeginCodeSnippet
  typedef itk::ResampleImageFilter<
  ImageType,
  OutputImageType >    ResampleFilterType;
  // Software Guide : EndCodeSnippet

  //  Software Guide : BeginLatex
  //
  //  A resampling filter is created and the moving image is connected as
  //  its input.
  //
  //  Software Guide : EndLatex

  // Software Guide : BeginCodeSnippet
  ResampleFilterType::Pointer resampler = ResampleFilterType::New();
  resampler->SetInput( movingReader->GetOutput() );

  //typedef itk::ImageRegistrationMethod<
  //ImageType,
  //ImageType >    RegistrationType;
  
  //RegistrationType::Pointer   registration  = RegistrationType::New();

  // Software Guide : EndCodeSnippet

  //  Software Guide : BeginLatex
  //
  //  The Transform that is produced as output need to be inversed to 
  //  We apply here the resampling algorithm to the "fixed" image 
  // to produce the moving image. Or apply to the moving image
  //
  //
  //  Software Guide : EndLatex

  // Write the transformation to a file
  std::ofstream ofs;
  ofs.open(outputTransformationFilename);

  // Set floatfield to format properly
  ofs.setf(std::ios::fixed, std::ios::floatfield);
  ofs.precision(10);

  ofs<<"Estimated affine matrix: "<<std::endl;
  ofs<<estimator->GetMatrix()<<std::endl;
  ofs<<"Estimated affine offset: "<<std::endl;
  ofs<<estimator->GetOffset()<<std::endl;
  ofs<<"RMS error: "<<std::endl;
  ofs<<estimator->GetRMSError()<<std::endl;
  ofs<<"Relative residual: "<<std::endl;
  ofs<<estimator->GetRelativeResidual()<<std::endl;
  ofs.close();

  // Software Guide : BeginCodeSnippet
  // Get the output transform 
  typedef EstimatorType::AffineTransformType AffineTransformType;
  AffineTransformType::Pointer transform = AffineTransformType::New();
  transform->GetInverse( estimator->GetAffineTransform() );
  
  resampler->SetTransform( transform );
  resampler->SetSize( fixedReader->GetOutput()->GetLargestPossibleRegion().GetSize() );
  resampler->SetOutputOrigin( fixedReader->GetOutput()->GetOrigin() );
  resampler->SetOutputSpacing( fixedReader->GetOutput()->GetSpacing() );
  resampler->SetDefaultPixelValue( 100 );

  // Software Guide : EndCodeSnippet

  //  Software Guide : BeginLatex
  //
  //  Write resampled image to png
  //
  //  Software Guide : EndLatex
    
  // Software Guide : BeginCodeSnippet
  typedef otb::ImageFileWriter< OutputImageType > WriterType;
  WriterType::Pointer writer = WriterType::New();

  writer->SetInput( resampler->GetOutput() );
  writer->SetFileName( outputImageFilename );
  writer->Update();
  // Software Guide : EndCodeSnippet
  
   // Software Guide : BeginLatex
  //
  // Figure~\ref{fig:SIFTDME} shows the result of the resampled image using the
  // estimated transformation based on SIFT points 
  //
  // \begin{figure}
  // \center
  // \includegraphics[width=0.40\textwidth]{QB_Suburb.eps}
  // \includegraphics[width=0.40\textwidth]{QB_SuburbR10X13Y17.eps}
  // \includegraphics[width=0.40\textwidth]{AffineTransformationOutput.eps}
  // \itkcaption[Estimation of affine transformation from SIFT ]{From left
  // to right and top to bottom: fixed input image, moving image,
  // resampled moving image.}
  // \label{fig:SIFTDME}
  // \end{figure}
  //
  // Software Guide : EndLatex
  
  return EXIT_SUCCESS;
}

