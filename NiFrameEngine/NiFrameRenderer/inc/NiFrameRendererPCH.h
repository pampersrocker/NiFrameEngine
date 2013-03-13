#pragma once
//Activate this switch to use double precision
//#define USE_DOUBLE_PRECISION

//Import MathLib
#include <Vector2.h>
#include <Vector3.h>
#include <Matrix4x4.h>

//Use SSE if we are not using double precision
#ifndef USE_DOUBLE_PRECISION
	#include <SSEVector3.h>
#endif // !USE_DOUBLE_PRECISION


namespace NiFrame
{
	namespace Renderer
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

	}
}