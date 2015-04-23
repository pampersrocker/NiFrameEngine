#pragma once
#ifndef NiFramePrerequisites_h__
  #define NiFramePrerequisites_h__

  #include "NFMacros.hpp"
  #include <string>
  #include <stdint.h>

// Import MathLib
  #include <LinearMath/Vector2.hpp>
  #include <LinearMath/Vector3.hpp>
  #include <LinearMath/Matrix4x4.hpp>

// Active this switch if you want do enable double precision
// #define USE_DOUBLE_PRECISION

// Use SSE if we are not using double precision
  #ifndef USE_DOUBLE_PRECISION
    #include <LinearMath/SSEVector3.hpp>
  #endif  // !USE_DOUBLE_PRECISION

namespace nfe
{
  #ifdef USE_DOUBLE_PRECISION
  typedef double Real;
  #else  // Use single precision
  typedef float Real;
  #endif  // USE_DOUBLE_PRECISSION

  NIFRAME_TPL_EXPORT template class NIFRAME_DLL_EXPORT LinearMath::Vector3_tpl< Real >;
  NIFRAME_TPL_EXPORT template class NIFRAME_DLL_EXPORT LinearMath::Vector2_tpl< Real >;
  NIFRAME_TPL_EXPORT template class NIFRAME_DLL_EXPORT LinearMath::Matrix4x4_tpl< Real >;
  typedef LinearMath::Vector3_tpl< Real > NIFRAME_DLL_EXPORT Vector3;
  typedef LinearMath::Vector2_tpl< Real > NIFRAME_DLL_EXPORT Vector2;
  typedef LinearMath::Matrix4x4_tpl< Real > NIFRAME_DLL_EXPORT Matrix4x4;

  struct RealHelper
  {
    static const Real ZERO;
    static const Real ONE;
    static const Real NEGATIVE_ONE;
  };

  NIFRAME_TPL_EXPORT template class NIFRAME_DLL_EXPORT std::basic_string< char >;

  typedef std::basic_string< char > String;
  typedef std::stringbuf StringBuffer;

  typedef uint64_t uint64;
  typedef uint32_t uint32;
  typedef uint16_t uint16;
  typedef uint8_t uint8;

  typedef int64_t int64;
  typedef int32_t int32;
  typedef int16_t int16;
  typedef int8_t int8;

  typedef size_t NFSize;

  typedef std::exception exception;
}
#endif  // NiFramePrerequisites_h__
