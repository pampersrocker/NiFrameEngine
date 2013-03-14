#pragma once
#ifndef NiFramePrerequisites_h__
#define NiFramePrerequisites_h__

#include "NiFrameEnginePCH.h"
#include <string>
#include <stdint.h>

//Import MathLib
#include <Vector2.h>
#include <Vector3.h>
#include <Matrix4x4.h>

//Active this switch if you want do enable double precision
//#define USE_DOUBLE_PRECISION


//Use SSE if we are not using double precision
#ifndef USE_DOUBLE_PRECISION
#include <SSEVector3.h>
#endif // !USE_DOUBLE_PRECISION


namespace NiFrame
{
#ifdef USE_DOUBLE_PRECISION
	typedef double Real;
	typedef LinearMath::Vector3_tpl<double> Vector3;
	typedef LinearMath::Vector2_tpl<double> Vector2;
	typedef LinearMath::Matrix4x4_tpl<double> Matrix4x4;
#else //Use single precision
	typedef float Real;
	typedef LinearMath::SSEVector3 Vector3;
	typedef LinearMath::Vector2_tpl<float> Vector2;
	typedef LinearMath::Matrix4x4_tpl<float> Matrix4x4;

#endif // USE_DOUBLE_PRECISSION

	struct RealHelper
	{
		static const Real ZERO;
		static const Real ONE;
		static const Real NEGATIVE_ONE;
	};



	typedef std::string String;
	typedef std::stringbuf StringBuffer;

	typedef uint64_t uint64;
	typedef uint32_t uint32;
	typedef uint16_t uint16;
	typedef uint8_t uint8;

	typedef int64_t int64;
	typedef int32_t int32;
	typedef int16_t int16;
	typedef int8_t int8;



	typedef std::exception exception;

}
#endif // NiFramePrerequisites_h__