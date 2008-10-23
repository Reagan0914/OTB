// Define useful short names to aid wrapper configuration.  Only
// define names for types that have been included by the wrapper
// configuration file that includes this file.

#if defined(__itkVector_h)
namespace itkvector
{
  typedef itk::Vector< float,  2>  F2;
  typedef itk::Vector< float,  3>  F3;
  typedef itk::Vector< double, 2>  D2;
  typedef itk::Vector< double, 3>  D3;
}
#endif
#if defined(__itkCovariantVector_h)
namespace covariantvector
{
  typedef itk::CovariantVector< float,  2>  F2;
  typedef itk::CovariantVector< float,  3>  F3;
  typedef itk::CovariantVector< double, 2>  D2;
  typedef itk::CovariantVector< double, 3>  D3;
}
#endif
#if defined(__otbImage_h)
namespace image
{
  //typedef itk::Image<bool, 2> B2;
  //typedef itk::Image<bool, 3> B3;

  typedef otb::MetaDataKey otbMetaDataKey;
  typedef itk::MetaDataDictionary itkMetaDataDictionary;
  typedef otb::ImageBase otbImageBase;
  typedef otb::Image<float         , 2> F2;
  typedef otb::Image<double        , 2> D2;
  typedef otb::Image<unsigned char , 2> UC2;
  typedef otb::Image<unsigned short, 2> US2;
  typedef otb::Image<unsigned int  , 2> UI2;
  typedef otb::Image<unsigned long , 2> UL2;
  typedef otb::Image<signed char   , 2> SC2;
  typedef otb::Image<signed short  , 2> SS2;
  typedef otb::Image<signed int    , 2> SI2;
  typedef otb::Image<signed long   , 2> SL2;


  typedef otb::Image<float         , 3> F3;
  typedef otb::Image<double        , 3> D3;
  typedef otb::Image<unsigned char , 3> UC3;
  typedef otb::Image<unsigned short, 3> US3;
  typedef otb::Image<unsigned int  , 3> UI3;
  typedef otb::Image<unsigned long , 3> UL3;
  typedef otb::Image<signed char   , 3> SC3;
  typedef otb::Image<signed short  , 3> SS3;
  typedef otb::Image<signed int    , 3> SI3;
  typedef otb::Image<signed long   , 3> SL3;
}

# if defined(__itkVector_h)
namespace image
{
  typedef otb::Image< itkvector::F2, 2 > VF2;
  typedef otb::Image< itkvector::F3, 3 > VF3;
  typedef otb::Image< itkvector::F2, 2 > VD2;
  typedef otb::Image< itkvector::F3, 3 > VD3;
  typedef otb::Image< itkvector::F2, 2 > V2F2;
  typedef otb::Image< itkvector::F2, 3 > V2F3;
}
# endif
# if defined(__itkCovariantVector_h)
namespace image
{
  typedef otb::Image< covariantvector::F2, 2 > CVF2;
  typedef otb::Image< covariantvector::F3, 3 > CVF3;
  typedef otb::Image< covariantvector::D2, 2 > CVD2;
  typedef otb::Image< covariantvector::D3, 3 > CVD3;
}
# endif
#endif
#if defined (__otbVectorImage_h)
namespace image
{
  typedef otb::VectorImage<float         , 2> VIF2;
  typedef otb::VectorImage<double        , 2> VID2;
  typedef otb::VectorImage<unsigned char , 2> VIUC2;
  typedef otb::VectorImage<unsigned short, 2> VIUS2;
  typedef otb::VectorImage<unsigned int  , 2> VIUI2;
  typedef otb::VectorImage<unsigned long , 2> VIUL2;
  typedef otb::VectorImage<signed char   , 2> VISC2;
  typedef otb::VectorImage<signed short  , 2> VISS2;
  typedef otb::VectorImage<signed int    , 2> VISI2;
  typedef otb::VectorImage<signed long   , 2> VISL2;
}
#endif

/* namespace imageslist */
/* { */
/* 	typedef otb::ImageList<image::F2> ILF2; */
/*   	typedef otb::ImageList<image::D2> ILD2; */
/* 	typedef otb::ImageList<image::UC2> ILUC2; */
/* 	typedef otb::ImageList<image::US2> ILUS2; */
/* 	typedef otb::ImageList<image::UI2> ILUI2; */
/* 	typedef otb::ImageList<image::UL2> ILUL2; */
/* 	typedef otb::ImageList<image::SC2> ILSC2; */
/* 	typedef otb::ImageList<image::SS2> ILSS2; */
/* 	typedef otb::ImageList<image::SL2> ILSL2; */
/* } */


