MESSAGE(STATUS "Importing Jpeg2000...")
# Use the openjpeg library.
OPTION(OTB_USE_JPEG2000 "Use to support jpeg2000 image file format." ON)

# JPEG2000 specification control
SET(OTB_COMPILE_JPEG2000 0)
IF( OTB_USE_JPEG2000 )
  SET(OTB_COMPILE_JPEG2000 1)
  IF(OTB_USE_EXTERNAL_ITK)
        MESSAGE(STATUS "  WARNING: Due to conflicting libraries, jpeg2000 support is disabled when using external ITK.")
        SET(OTB_COMPILE_JPEG2000 0)
  ENDIF(OTB_USE_EXTERNAL_ITK)
  IF(CMAKE_GENERATOR MATCHES "^Visual Studio 7$")
        MESSAGE(STATUS "  WARNING: For Visual Studio 7, jpeg2000 support is disabled.")
        SET(OTB_COMPILE_JPEG2000 0)
  ENDIF(CMAKE_GENERATOR MATCHES "^Visual Studio 7$")
  IF(CMAKE_GENERATOR MATCHES "^Visual Studio 7 .NET 2003$")
        MESSAGE(STATUS "  WARNING: For Visual Studio 7, jpeg2000 support is disabled.")
        SET(OTB_COMPILE_JPEG2000 0)
  ENDIF(CMAKE_GENERATOR MATCHES "^Visual Studio 7 .NET 2003$")
  IF(CYGWIN)
        MESSAGE(STATUS "  WARNING: For cygwin, jpeg2000 support is disabled.")
        SET(OTB_COMPILE_JPEG2000 0)
  ENDIF(CYGWIN)
  
  IF(OTB_COMPILE_JPEG2000)
    MESSAGE(STATUS "  Enabling Jpeg2000 support (internal)")
  ELSE(OTB_COMPILE_JPEG2000)
    MESSAGE(STATUS "  Disabling Jpeg2000 support")
  ENDIF(OTB_COMPILE_JPEG2000)
  
ELSE( OTB_USE_JPEG2000 )
    MESSAGE(STATUS "  Disabling Jpeg2000 support")
ENDIF( OTB_USE_JPEG2000 )

# Check jpeg2000 support
IF(OTB_COMPILE_JPEG2000)
  ADD_DEFINITIONS(-DOTB_COMPILE_JPEG2000 -DUSE_OPJ_DEPRECATED)
  IF(NOT BUILD_SHARED_LIBS)
        ADD_DEFINITIONS(-DOPJ_STATIC)
  ENDIF(NOT BUILD_SHARED_LIBS)
ENDIF(OTB_COMPILE_JPEG2000)
