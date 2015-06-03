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
  #include "LinearMath/MathHelper.hpp"


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
#ifdef WIN32
  NIFRAME_TPL_EXPORT template class NIFRAME_API LinearMath::Vector3_tpl< Real >;
  NIFRAME_TPL_EXPORT template class NIFRAME_API LinearMath::Vector2_tpl< Real >;
  NIFRAME_TPL_EXPORT template class NIFRAME_API LinearMath::Matrix4x4_tpl< Real >;
#elif defined(ORBIS)

}
namespace LinearMath
{
  //NIFRAME_TPL_EXPORT template class NIFRAME_API Vector3_tpl < nfe::Real > ;
  //NIFRAME_TPL_EXPORT template class NIFRAME_API Vector4_tpl < nfe::Real > ;
  //NIFRAME_TPL_EXPORT template class NIFRAME_API Vector2_tpl < nfe::Real > ;
  //NIFRAME_TPL_EXPORT template class NIFRAME_API Matrix4x4_tpl < nfe::Real > ;

}
namespace nfe
{
#endif
  typedef LinearMath::Vector3_tpl< Real > Vector3;
  typedef LinearMath::Vector4_tpl< Real > Vector4;
  typedef LinearMath::Vector2_tpl< Real > Vector2;
  typedef LinearMath::Matrix4x4_tpl< Real > Matrix4x4;
  typedef LinearMath::Radian_tpl< Real> Radian;
  typedef LinearMath::Degree_tpl< Real> Degree;


  struct RealHelper
  {
    static const Real ZERO;
    static const Real ONE;
    static const Real NEGATIVE_ONE;
  };
#ifdef WIN32
  NIFRAME_API std::string;
#endif

  typedef std::string String;
  typedef std::stringbuf StringBuffer;

  typedef uint64_t uint64;
  typedef uint32_t uint32;
  typedef uint16_t uint16;
  typedef uint8_t uint8;

  static_assert( sizeof( uint8 ) == 1, "Size of uint8 is incorrect!" );

  typedef int64_t int64;
  typedef int32_t int32;
  typedef int16_t int16;
  typedef int8_t int8;

  typedef size_t NFSize;
#ifdef WIN32
  typedef HWND NativeHandle;
  typedef HRESULT NativeInstance;
#elif ORBIS
  //TODO
  typedef uint32 NativeInstance;
  typedef uint32 NativeHandle;
#endif
  typedef std::exception exception;
}
#endif  // NiFramePrerequisites_h__
