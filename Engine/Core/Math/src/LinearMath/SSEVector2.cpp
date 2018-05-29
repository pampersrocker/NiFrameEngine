#include "NFMathPCH.hpp"
#include "LinearMath/SSEVector2.hpp"
#include <smmintrin.h>

namespace LinearMath
{
  SSEVector2::SSEVector2()
  {
    vec = _mm_set_ps( 0, 0, 0, 0 );
  }

  SSEVector2::SSEVector2( float val )
  {
    vec = _mm_set_ps( 0, val, val, 1 );
  }

  SSEVector2::SSEVector2( float X, float Y )
  {
    vec = _mm_set_ps( 0, Y, X, 1 );
  }

  SSEVector2::SSEVector2( const SSEVector2& val )
  {
    vec =  __m128( val.vec );
  }

  SSEVector2::SSEVector2( const __m128& mmVal )
  {
    vec = mmVal;
  }

  SSEVector2::~SSEVector2()
  {
  }

  LinearMath::SSEVector2 SSEVector2::operator +( const SSEVector2& v ) const
  {
    return SSEVector2( _mm_add_ps( vec, v.vec ) );
  }

  SSEVector2& SSEVector2::operator +=( const SSEVector2& v )
  {
    vec = _mm_add_ps( vec, v.vec );
    return *this;
  }

  LinearMath::SSEVector2 SSEVector2::operator -( const SSEVector2& v ) const
  {
    return SSEVector2( _mm_sub_ps( vec, v.vec ) );
  }

  SSEVector2& SSEVector2::operator -=( const SSEVector2& v )
  {
    vec = _mm_sub_ps( vec, v.vec );
    return *this;
  }

  float SSEVector2::operator *( const SSEVector2& v ) const
  {
    float result[ 4 ];

    // Store in lowest float, do not multiply fourth amd first value: 1110 0001
    const int mask = 0x61;
    _mm_store_ss( result, _mm_dp_ps( vec, v.vec, mask ) );
    return result[ 0 ];
  }

  LinearMath::SSEVector2 SSEVector2::operator *( const float& scalar ) const
  {
    return SSEVector2( _mm_mul_ps( vec, _mm_set_ps( 0, scalar, scalar, 1 ) ) );
  }

  SSEVector2 operator *( const float& scalar, const SSEVector2& v )
  {
    return v * scalar;
  }

  SSEVector2& SSEVector2::operator *=( const float& scalar )
  {
    vec = _mm_mul_ps( vec, _mm_set_ps( 0, scalar, scalar, 1 ) );
    return *this;
  }

  LinearMath::SSEVector2 SSEVector2::operator /( const float& scalar ) const
  {
    return SSEVector2( _mm_div_ps( vec, _mm_set_ps( 0, scalar, scalar, 1 ) ) );
  }

  SSEVector2& SSEVector2::operator /=( const float& scalar )
  {
    vec = _mm_div_ps( vec, _mm_set_ps( 0, scalar, scalar, 1 ) );
    return *this;
  }

  float SSEVector2::LengthSquared() const
  {
    return *this * *this;
  }

  float SSEVector2::Length() const
  {
    float result[ 4 ];

    // Store in all floats, do not multiply fourth and first value: 0110 1111
    const int mask = 0x6F;
    _mm_store_ss( result, _mm_sqrt_ss( _mm_dp_ps( vec, vec, mask ) ) );
    return result[ 0 ];
  }

  void SSEVector2::Normalize()
  {
    // Store in all floats, do not multiply fourth and first value: 0110 1111
    const int mask = 0x6F;
    vec =  _mm_div_ps( vec, _mm_sqrt_ps( _mm_dp_ps( vec, vec, mask ) ) );
  }

  LinearMath::SSEVector2 SSEVector2::NormalizedCopy() const
  {
    SSEVector2 result( *this );
    result.Normalize();
    return result;
  }

  float SSEVector2::DotProduct( const SSEVector2& v ) const
  {
    return *this * v;
  }

  float SSEVector2::GetX() const
  {
    float result[ 4 ];
    _mm_storeu_ps( result, vec );
    return result[ 1 ];
  }

  float SSEVector2::GetY() const
  {
    float result[ 4 ];
    _mm_storeu_ps( result, vec );
    return result[ 2 ];
  }

  float SSEVector2::operator[]( Numerics::uint8 idx ) const
  {
    return GetElem( idx );
  }

  float SSEVector2::GetElem( Numerics::uint8 idx ) const
  {
    float result[ 4 ];
    _mm_storeu_ps( result, vec );
    return result[ idx ];
  }

  LinearMath::SSEVector2 SSEVector2::ComponentMul( const SSEVector2& InVec ) const
  {
    return SSEVector2( _mm_mul_ps( this->vec, InVec.vec ) );
  }

}
