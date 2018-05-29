#pragma once
#ifndef _MP_SSEVECTOR_4_H_
#define _MP_SSEVECTOR_4_H_

#include <xmmintrin.h>
#include "SSEVector3.hpp"

namespace LinearMath
{
  class SSEVector4
  {
  public:

    SSEVector4( void );
    SSEVector4( float val );
    SSEVector4( float X, float Y, float Z, float W );
    SSEVector4( const SSEVector4& val );
    SSEVector4( const __m128& mmVal );

    ~SSEVector4( void );

    // Operators
    SSEVector4 operator +( const SSEVector4& v ) const;

    SSEVector4& operator +=( const SSEVector4& v );

    SSEVector4 operator -( const SSEVector4& v ) const;

    SSEVector4& operator -=( const SSEVector4& v );

    float operator *( const SSEVector4& v ) const;

    SSEVector4 operator *( const float& scalar ) const;

    SSEVector4& operator *=( const float& scalar );

    friend SSEVector4 operator *( const float& scalar, const SSEVector4& v );

    SSEVector4 operator /( const float& scalar ) const;

    SSEVector4& operator /=( const float& scalar );

    float operator []( Numerics::uint8 idx ) const;

    float LengthSquared() const;

    float Length() const;

    void Normalize();

    SSEVector4 NormalizedCopy() const;

    float DotProduct( const SSEVector4& v ) const;

    float GetX() const;
    float GetY() const;
    float GetZ() const;
    float GetW() const;
    float GetElem(Numerics::uint8 idx) const;

    void GetFloatArray( float* floats ) const;

    SSEVector3 GetXYZ() const;

    void SetX(float value);
    void SetY(float value);
    void SetZ(float value);
    void SetW(float value);
    void SetElem(Numerics::uint8 idx, float value);

    __m128 vec;

  private:
  };
}

#endif // ifndef _MP_SSEVECTOR_4_H_
