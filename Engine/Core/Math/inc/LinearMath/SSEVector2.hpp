#pragma once
#ifndef _MP_SSEVECTOR_2_H_
  #define _MP_SSEVECTOR_2_H_

  #include <xmmintrin.h>
#include "MathHelper.hpp"

namespace LinearMath
{
  class SSEVector2
  {
  public:

    SSEVector2( void );
    SSEVector2( float val );
    SSEVector2( float X, float Y );
    SSEVector2( const SSEVector2& val );
    SSEVector2( const __m128& mmVal );

    ~SSEVector2( void );

    // Operators
    SSEVector2 operator +( const SSEVector2& v ) const;

    SSEVector2& operator +=( const SSEVector2& v );

    SSEVector2 operator -( const SSEVector2& v ) const;

    SSEVector2& operator -=( const SSEVector2& v );

    float operator *( const SSEVector2& v ) const;

    SSEVector2 operator *( const float& scalar ) const;

    SSEVector2& operator *=( const float& scalar );

    friend SSEVector2 operator *( const float& scalar, const SSEVector2& v );

    SSEVector2 operator /( const float& scalar ) const;

    SSEVector2& operator /=( const float& scalar );

    SSEVector2 ComponentMul( const SSEVector2& vec) const;

    float LengthSquared() const;

    float Length() const;

    void Normalize();

    SSEVector2 NormalizedCopy() const;

    float DotProduct( const SSEVector2& v ) const;

    float GetX() const;

    float GetY() const;

    float operator []( Numerics::uint8 idx ) const;
    float GetElem( Numerics::uint8 idx ) const;


    __m128 vec;

  private:
  };
}

#endif // ifndef _MP_SSEVECTOR_2_H_
