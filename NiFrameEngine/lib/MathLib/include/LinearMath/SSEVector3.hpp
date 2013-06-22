#pragma once
#ifndef _MP_SSEVECTOR_3_H_
	#define _MP_SSEVECTOR_3_H_

	#include "MathLibPCH.hpp"
	#include <xmmintrin.h>

namespace LinearMath
{
	class SSEVector3
	{
	public:

		SSEVector3( void );
		SSEVector3( float val );
		SSEVector3( float X, float Y, float Z );
		SSEVector3( const SSEVector3& val );
		SSEVector3( const __m128& mmVal );

		~SSEVector3( void );

		// Operators
		SSEVector3 operator +( const SSEVector3& v ) const;

		SSEVector3& operator +=( const SSEVector3& v );

		SSEVector3 operator -( const SSEVector3& v ) const;

		SSEVector3& operator -=( const SSEVector3& v );

		float operator *( const SSEVector3& v ) const;

		SSEVector3 operator *( const float& scalar ) const;

		SSEVector3& operator *=( const float& scalar );

		friend SSEVector3 operator *( const float& scalar, const SSEVector3& v );

		SSEVector3 operator /( const float& scalar ) const;

		SSEVector3& operator /=( const float& scalar );

		SSEVector3 operator ^( const SSEVector3& v ) const;

		float LengthSquared() const;

		float Length() const;

		void Normalize();

		SSEVector3 NormalizedCopy() const;

		SSEVector3 CrossProduct( const SSEVector3& v ) const;

		float DotProduct( const SSEVector3& v ) const;

		float GetX() const;

		float GetY() const;

		float GetZ() const;

		__m128 vec;

	private:
	};
}

#endif // ifndef _MP_SSEVECTOR_3_H_
