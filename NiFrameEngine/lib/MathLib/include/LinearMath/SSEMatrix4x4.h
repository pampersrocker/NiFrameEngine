#pragma once

#include "MathLibPCH.h"
#include <xmmintrin.h>
#include "MathHelper.h"

#ifndef SSEMatrix4x4_h__
#define SSEMatrix4x4_h__

namespace LinearMath
{
	class SSEVector3;

	__declspec(align(16)) class SSEMatrix4x4
	{
	public:
		SSEMatrix4x4();
		SSEMatrix4x4( const __m128& col0, const __m128& col1, const __m128& col2, const __m128& col3 );
		SSEMatrix4x4( 
			float M11, float M12, float M13, float M14,
			float M21, float M22, float M23, float M24,
			float M31, float M32, float M33, float M34,
			float M41, float M42, float M43, float M44
			);
		SSEMatrix4x4( const SSEMatrix4x4& matrix );

		SSEMatrix4x4 operator +(const SSEMatrix4x4& matrix) const;
		SSEMatrix4x4& operator +=(const SSEMatrix4x4& matrix);

		SSEMatrix4x4 operator -( const SSEMatrix4x4& matrix) const;
		SSEMatrix4x4 operator -=( const SSEMatrix4x4& matrix);

		SSEMatrix4x4 operator *( const SSEMatrix4x4& matrix ) const;
		SSEMatrix4x4& operator *=( const SSEMatrix4x4& matrix );

		static const SSEMatrix4x4 ZERO;
		static const SSEMatrix4x4 ZERO_AFFINE;
		static const SSEMatrix4x4 IDENTITY;

		static SSEMatrix4x4 CreateLookAt( const SSEVector3& from, const SSEVector3& to, const SSEVector3& up );
		static SSEMatrix4x4 CreateLookDir( const SSEVector3& dir, const SSEVector3& up );
		static SSEMatrix4x4 CreateProjectionMatrix( float viewAngle, float aspectRatio, float nearPlane, float farPlane );

		static SSEMatrix4x4 CreateRotationX( const Radian_tpl<float>& angle );
		static SSEMatrix4x4 CreateRotationY( const Radian_tpl<float>& angle );
		static SSEMatrix4x4 CreateRotationZ( const Radian_tpl<float>& angle );


		static SSEMatrix4x4 CreateTranslation( const SSEVector3& translation );


		static SSEMatrix4x4 CreateScale( const SSEVector3& scale );

		void Invert();
		SSEMatrix4x4 InvertedCopy() const;

		SSEMatrix4x4 TransposedCopy() const;
		void Transpose();

		void GetAsFloatArray(float* arr) const;

		float GetM_1_1() const;
		float GetM_1_2() const;
		float GetM_1_3() const;
		float GetM_1_4() const;

		float GetM_2_1() const;
		float GetM_2_2() const;
		float GetM_2_3() const;
		float GetM_2_4() const;

		float GetM_3_1() const;
		float GetM_3_2() const;
		float GetM_3_3() const;
		float GetM_3_4() const;

		float GetM_4_1() const;
		float GetM_4_2() const;
		float GetM_4_3() const;
		float GetM_4_4() const;


		~SSEMatrix4x4();

	private:

		__m128 m_col0, m_col1, m_col2, m_col3;

	};
}

#endif // SSEMatrix4x4_h__