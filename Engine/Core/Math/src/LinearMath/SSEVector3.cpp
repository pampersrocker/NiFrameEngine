#include "NFMathPCH.hpp"
#include "LinearMath/SSEVector3.hpp"
#include <smmintrin.h>
#include <stdint.h>

namespace LinearMath
{
  SSEVector3::SSEVector3()
  {
    vec = _mm_set_ps( 0, 0, 0, 0 );
  }

  SSEVector3::SSEVector3( float val )
  {
    vec = _mm_set_ps( 0, val, val, val );
  }

  SSEVector3::SSEVector3( float X, float Y, float Z )
  {
    vec = _mm_set_ps( 0, Z, Y, X );
  }

  SSEVector3::SSEVector3( const SSEVector3& val )
  {
    vec =  __m128( val.vec );
  }

  SSEVector3::SSEVector3( const __m128& mmVal )
  {
    vec = mmVal;
  }

  SSEVector3::~SSEVector3()
  {
  }

  LinearMath::SSEVector3 SSEVector3::operator +( const SSEVector3& v ) const
  {
    return SSEVector3( _mm_add_ps( vec, v.vec ) );
  }

  SSEVector3& SSEVector3::operator +=( const SSEVector3& v )
  {
    vec = _mm_add_ps( vec, v.vec );
    return *this;
  }

  LinearMath::SSEVector3 SSEVector3::operator -( const SSEVector3& v ) const
  {
    return SSEVector3( _mm_sub_ps( vec, v.vec ) );
  }

  SSEVector3& SSEVector3::operator -=( const SSEVector3& v )
  {
    vec = _mm_sub_ps( vec, v.vec );
    return *this;
  }

  float SSEVector3::operator *( const SSEVector3& v ) const
  {
    float result[ 4 ];

    // Store in lowest float, do not multiply fourth value: 1110 0001
    const int mask = 0x71;
    _mm_store_ss( result, _mm_dp_ps( vec, v.vec, mask ) );
    return result[ 0 ];
  }

  LinearMath::SSEVector3 SSEVector3::operator *( const float& scalar ) const
  {
    return SSEVector3( _mm_mul_ps( vec, _mm_set_ps( 0, scalar, scalar, scalar ) ) );
  }

  SSEVector3 operator *( const float& scalar, const SSEVector3& v )
  {
    return v * scalar;
  }

  SSEVector3& SSEVector3::operator *=( const float& scalar )
  {
    vec = _mm_mul_ps( vec, _mm_set_ps( 0, scalar, scalar, scalar ) );
    return *this;
  }

  LinearMath::SSEVector3 SSEVector3::operator /( const float& scalar ) const
  {
    return SSEVector3( _mm_div_ps( vec, _mm_set_ps( 0, scalar, scalar, scalar ) ) );
  }

  SSEVector3& SSEVector3::operator /=( const float& scalar )
  {
    vec = _mm_div_ps( vec, _mm_set_ps( 0, scalar, scalar, scalar ) );
    return *this;
  }

  LinearMath::SSEVector3 SSEVector3::operator ^( const SSEVector3& v ) const
  {
    return SSEVector3
         (
      _mm_sub_ps
      (
      _mm_mul_ps(

      // Y,Z,X,W
      _mm_shuffle_ps( vec, vec, _MM_SHUFFLE( 3,0, 2, 1 ) ),

      // Z,X,Y,W
      _mm_shuffle_ps( v.vec, v.vec, _MM_SHUFFLE( 3,1, 0, 2 ) )
      ),
      _mm_mul_ps(

      // Z,X,Y,W
      _mm_shuffle_ps( vec, vec, _MM_SHUFFLE( 3,1, 0, 2 ) ),

      // Y,Z,X,W
      _mm_shuffle_ps( v.vec, v.vec, _MM_SHUFFLE( 3,0, 2, 1 ) )
      )
      )
         );
  }

  float SSEVector3::LengthSquared() const
  {
    return *this * *this;
  }

  float SSEVector3::Length() const
  {
    float result[ 4 ];

    // Store in all floats, do not multiply fourth value: 0111 1111
    const int mask = 0x7F;
    _mm_store_ss( result, _mm_sqrt_ss( _mm_dp_ps( vec, vec, mask ) ) );
    return result[ 0 ];
  }

  void SSEVector3::Normalize()
  {
    // Store in all floats, do not multiply fourth value: 0111 1111
    const int mask = 0x7F;
    vec =  _mm_div_ps( vec, _mm_sqrt_ps( _mm_dp_ps( vec, vec, mask ) ) );
  }

  LinearMath::SSEVector3 SSEVector3::NormalizedCopy() const
  {
    SSEVector3 result( *this );
    result.Normalize();
    return result;
  }

  LinearMath::SSEVector3 SSEVector3::CrossProduct( const SSEVector3& v ) const
  {
    return *this ^ v;
  }

  float SSEVector3::DotProduct( const SSEVector3& v ) const
  {
    return *this * v;
  }

  float SSEVector3::GetX() const
  {
    float result[ 8 ];
    float *data = reinterpret_cast< float* >(
      reinterpret_cast< uintptr_t >( result ) +( 16 - ( reinterpret_cast< uintptr_t >( result ) % 16 ) ) );
    _mm_store_ps( data, vec );
    return data[ 0 ];
  }

  float SSEVector3::GetY() const
  {
    float result[ 8 ];
    float *data = reinterpret_cast< float* >(
      reinterpret_cast< uintptr_t >( result ) +( 16 - ( reinterpret_cast< uintptr_t >( result ) % 16 ) ) );
    _mm_store_ps( data, vec );
    return data[ 1 ];
  }

  float SSEVector3::GetZ() const
  {
    float result[ 8 ];
    float *data = reinterpret_cast< float* >(
      reinterpret_cast< uintptr_t >( result ) +( 16 - ( reinterpret_cast< uintptr_t >( result ) % 16 ) ) );
    _mm_store_ps( data, vec );
    return data[ 2 ];
  }

  void SSEVector3::SetX( float value )
  {
    SetElem(0, value );
  }

  void SSEVector3::SetY( float value )
  {
    SetElem( 1, value );
  }

  void SSEVector3::SetZ( float value )
  {
    SetElem( 2, value );
  }

  void SSEVector3::SetElem( Numerics::uint8 idx, float value )
  {
    __m128 val = _mm_set1_ps( value );
    switch( idx )
    {
    case 0:
      vec = _mm_insert_ps( vec, val, 0x00 );
      break;
    case 1:
      vec = _mm_insert_ps( vec, val, 0x10 );
      break;
    case 2:
      vec = _mm_insert_ps( vec, val, 0x20 );
      break;
    }
  }

  float SSEVector3::GetElem( Numerics::uint8 idx ) const
  {
    float result[ 4 ];
    _mm_storeu_ps( result, vec );
    return result[ idx ];
  }

  float SSEVector3::operator[]( Numerics::uint8 idx ) const
  {
    return GetElem( idx );
  }

}
