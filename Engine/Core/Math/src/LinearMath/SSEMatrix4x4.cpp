#include "NFMathPCH.hpp"
#include "LinearMath/SSEMatrix4x4.hpp"
#include <smmintrin.h>
#include "LinearMath/SSEVector3.hpp"
#include "LinearMath/MathHelper.hpp"

namespace LinearMath
{
  const SSEMatrix4x4 SSEMatrix4x4::ZERO
    (
    0.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 0.0f
    );

  const SSEMatrix4x4 SSEMatrix4x4::ZERO_AFFINE
    (
    0.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f
    );

  const SSEMatrix4x4 SSEMatrix4x4::IDENTITY
    (
    1.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f
    );

  SSEMatrix4x4::SSEMatrix4x4()
  {
    m_col0 = SSEVector4( 0 );
    m_col1 = SSEVector4( 0 );
    m_col2 = SSEVector4( 0 );
    m_col3 = SSEVector4( 0 );
  }

  SSEMatrix4x4::SSEMatrix4x4( const SSEVector4& col0, const SSEVector4& col1, const SSEVector4& col2, const SSEVector4& col3 ) :
    m_col0( col0 ),
    m_col1( col1 ),
    m_col2( col2 ),
    m_col3( col3 )
  {
  }

  SSEMatrix4x4::SSEMatrix4x4(
    float M11, float M12, float M13, float M14,
    float M21, float M22, float M23, float M24,
    float M31, float M32, float M33, float M34,
    float M41, float M42, float M43, float M44 )
  {
    m_col0 = SSEVector4( M11, M21, M31, M41 );
    m_col1 = SSEVector4( M12, M22, M32, M42 );
    m_col2 = SSEVector4( M13, M23, M33, M43 );
    m_col3 = SSEVector4( M14, M24, M34, M44 );
  }

  SSEMatrix4x4::SSEMatrix4x4( const SSEMatrix4x4& matrix )
  {
    m_col0 = matrix.m_col0;
    m_col1 = matrix.m_col1;
    m_col2 = matrix.m_col2;
    m_col3 = matrix.m_col3;
  }

  SSEMatrix4x4::~SSEMatrix4x4()
  {
  }

  LinearMath::SSEMatrix4x4 SSEMatrix4x4::operator +( const SSEMatrix4x4& matrix ) const
  {
    SSEMatrix4x4 result( *this );
    result += matrix;
    return result;
  }

  SSEMatrix4x4& SSEMatrix4x4::operator +=( const SSEMatrix4x4& matrix )
  {
    m_col0 = m_col0 + matrix.m_col0;
    m_col1 = m_col1 + matrix.m_col1;
    m_col2 = m_col2 + matrix.m_col2;
    m_col3 = m_col3 + matrix.m_col3;
    return *this;
  }

  LinearMath::SSEMatrix4x4 SSEMatrix4x4::operator -( const SSEMatrix4x4& matrix ) const
  {
    SSEMatrix4x4 result( *this );
    result -= matrix;
    return result;
  }

  LinearMath::SSEMatrix4x4 SSEMatrix4x4::operator -=( const SSEMatrix4x4& matrix )
  {
    m_col0 = m_col0 - matrix.m_col0;
    m_col1 = m_col1 - matrix.m_col1;
    m_col2 = m_col2 - matrix.m_col2;
    m_col3 = m_col3 - matrix.m_col3;
    return *this;
  }

  LinearMath::SSEMatrix4x4 SSEMatrix4x4::operator *( const SSEMatrix4x4& matrix ) const
  {
    return SSEMatrix4x4( *this ) *= matrix;
  }

  LinearMath::SSEVector4 SSEMatrix4x4::operator*( const SSEVector4& vec ) const
  {
    SSEMatrix4x4 transposed = TransposedCopy();
    __m128 result = _mm_set_ps( 0, 0, 0, 0 );
    result = _mm_add_ps( _mm_dp_ps( transposed.m_col0.vec, vec.vec, 0xF1 ), result );
    result = _mm_add_ps( _mm_dp_ps( transposed.m_col1.vec, vec.vec, 0xF2 ), result );
    result = _mm_add_ps( _mm_dp_ps( transposed.m_col2.vec, vec.vec, 0xF4 ), result );
    result = _mm_add_ps( _mm_dp_ps( transposed.m_col3.vec, vec.vec, 0xF8 ), result );
    return SSEVector4( result );
  }

  SSEMatrix4x4& SSEMatrix4x4::operator *=( const SSEMatrix4x4& mat )
  {
    SSEMatrix4x4 matrix( mat );
    matrix.Transpose();

    __m128 zero = _mm_set_ps( 0, 0, 0, 0 );

    __m128 tmp_col0( zero );
    __m128 tmp_col1( zero );
    __m128 tmp_col2( zero );
    __m128 tmp_col3( zero );

    tmp_col0 = _mm_add_ps( _mm_dp_ps( matrix.m_col0.vec, m_col0.vec, 0xF1 ), tmp_col0 );
    tmp_col0 = _mm_add_ps( _mm_dp_ps( matrix.m_col0.vec, m_col1.vec, 0xF2 ), tmp_col0 );
    tmp_col0 = _mm_add_ps( _mm_dp_ps( matrix.m_col0.vec, m_col2.vec, 0xF4 ), tmp_col0 );
    tmp_col0 = _mm_add_ps( _mm_dp_ps( matrix.m_col0.vec, m_col3.vec, 0xF8 ), tmp_col0 );

    tmp_col1 = _mm_add_ps( _mm_dp_ps( matrix.m_col1.vec, m_col0.vec, 0xF1 ), tmp_col1 );
    tmp_col1 = _mm_add_ps( _mm_dp_ps( matrix.m_col1.vec, m_col1.vec, 0xF2 ), tmp_col1 );
    tmp_col1 = _mm_add_ps( _mm_dp_ps( matrix.m_col1.vec, m_col2.vec, 0xF4 ), tmp_col1 );
    tmp_col1 = _mm_add_ps( _mm_dp_ps( matrix.m_col1.vec, m_col3.vec, 0xF8 ), tmp_col1 );

    tmp_col2 = _mm_add_ps( _mm_dp_ps( matrix.m_col2.vec, m_col0.vec, 0xF1 ), tmp_col2 );
    tmp_col2 = _mm_add_ps( _mm_dp_ps( matrix.m_col2.vec, m_col1.vec, 0xF2 ), tmp_col2 );
    tmp_col2 = _mm_add_ps( _mm_dp_ps( matrix.m_col2.vec, m_col2.vec, 0xF4 ), tmp_col2 );
    tmp_col2 = _mm_add_ps( _mm_dp_ps( matrix.m_col2.vec, m_col3.vec, 0xF8 ), tmp_col2 );

    tmp_col3 = _mm_add_ps( _mm_dp_ps( matrix.m_col3.vec, m_col0.vec, 0xF1 ), tmp_col3 );
    tmp_col3 = _mm_add_ps( _mm_dp_ps( matrix.m_col3.vec, m_col1.vec, 0xF2 ), tmp_col3 );
    tmp_col3 = _mm_add_ps( _mm_dp_ps( matrix.m_col3.vec, m_col2.vec, 0xF4 ), tmp_col3 );
    tmp_col3 = _mm_add_ps( _mm_dp_ps( matrix.m_col3.vec, m_col3.vec, 0xF8 ), tmp_col3 );

    m_col0 = SSEVector4( tmp_col0 );
    m_col1 = SSEVector4( tmp_col1 );
    m_col2 = SSEVector4( tmp_col2 );
    m_col3 = SSEVector4( tmp_col3 );

    return *this;
  }

  void SSEMatrix4x4::Invert()
  {
    /***************************************/
    /* Based on http://download.intel.com/design/PentiumIII/sml/24504301.pdf */
    /***************************************/
    __m128 zero = _mm_set_ps( 0, 0, 0, 0 );

    __m128 minor0 = zero, minor1 = zero, minor2 = zero, minor3 = zero;
    __m128 row0 = zero, row1 = zero, row2 = zero, row3 = zero;
    __m128 det = zero, tmp1 = zero;

    tmp1 = _mm_loadh_pi( _mm_loadl_pi( tmp1, ( __m64* )( &m_col0 ) ), ( __m64* )( &m_col1 ) );
    row1 = _mm_loadh_pi( _mm_loadl_pi( row1, ( __m64* )( &m_col2 ) ), ( __m64* )( &m_col3 ) );
    row0 = _mm_shuffle_ps( tmp1, row1, 0x88 );
    row1 = _mm_shuffle_ps( row1, tmp1, 0xDD );
    tmp1
      = _mm_loadh_pi( _mm_loadl_pi( tmp1,
      ( __m64* )( ( ( float* ) &m_col0 ) + 2 ) ), ( __m64* )( ( ( float* ) &m_col1 ) + 2 ) );
    row3
      = _mm_loadh_pi( _mm_loadl_pi( row3,
      ( __m64* )( ( ( float* ) &m_col2 ) + 2 ) ), ( __m64* )( ( ( float* ) &m_col3 ) + 2 ) );
    row2 = _mm_shuffle_ps( tmp1, row3, 0x88 );
    row3 = _mm_shuffle_ps( row3, tmp1, 0xDD );

    // -----------------------------------------------
    tmp1 = _mm_mul_ps( row2, row3 );
    tmp1 = _mm_shuffle_ps( tmp1, tmp1, 0xB1 );
    minor0 = _mm_mul_ps( row1, tmp1 );
    minor1 = _mm_mul_ps( row0, tmp1 );
    tmp1 = _mm_shuffle_ps( tmp1, tmp1, 0x4E );
    minor0 = _mm_sub_ps( _mm_mul_ps( row1, tmp1 ), minor0 );
    minor1 = _mm_sub_ps( _mm_mul_ps( row0, tmp1 ), minor1 );
    minor1 = _mm_shuffle_ps( minor1, minor1, 0x4E );

    // -----------------------------------------------
    tmp1 = _mm_mul_ps( row1, row2 );
    tmp1 = _mm_shuffle_ps( tmp1, tmp1, 0xB1 );
    minor0 = _mm_add_ps( _mm_mul_ps( row3, tmp1 ), minor0 );
    minor3 = _mm_mul_ps( row0, tmp1 );
    tmp1 = _mm_shuffle_ps( tmp1, tmp1, 0x4E );
    minor0 = _mm_sub_ps( minor0, _mm_mul_ps( row3, tmp1 ) );
    minor3 = _mm_sub_ps( _mm_mul_ps( row0, tmp1 ), minor3 );
    minor3 = _mm_shuffle_ps( minor3, minor3, 0x4E );

    // -----------------------------------------------
    tmp1 = _mm_mul_ps( _mm_shuffle_ps( row1, row1, 0x4E ), row3 );
    tmp1 = _mm_shuffle_ps( tmp1, tmp1, 0xB1 );
    row2 = _mm_shuffle_ps( row2, row2, 0x4E );
    minor0 = _mm_add_ps( _mm_mul_ps( row2, tmp1 ), minor0 );
    minor2 = _mm_mul_ps( row0, tmp1 );
    tmp1 = _mm_shuffle_ps( tmp1, tmp1, 0x4E );
    minor0 = _mm_sub_ps( minor0, _mm_mul_ps( row2, tmp1 ) );
    minor2 = _mm_sub_ps( _mm_mul_ps( row0, tmp1 ), minor2 );
    minor2 = _mm_shuffle_ps( minor2, minor2, 0x4E );

    // -----------------------------------------------
    tmp1 = _mm_mul_ps( row0, row1 );// Streaming SIMD Extensions - Inverse of 4x4 Matrix

    tmp1 = _mm_shuffle_ps( tmp1, tmp1, 0xB1 );
    minor2 = _mm_add_ps( _mm_mul_ps( row3, tmp1 ), minor2 );
    minor3 = _mm_sub_ps( _mm_mul_ps( row2, tmp1 ), minor3 );
    tmp1 = _mm_shuffle_ps( tmp1, tmp1, 0x4E );
    minor2 = _mm_sub_ps( _mm_mul_ps( row3, tmp1 ), minor2 );
    minor3 = _mm_sub_ps( minor3, _mm_mul_ps( row2, tmp1 ) );

    // -----------------------------------------------
    tmp1 = _mm_mul_ps( row0, row3 );
    tmp1 = _mm_shuffle_ps( tmp1, tmp1, 0xB1 );
    minor1 = _mm_sub_ps( minor1, _mm_mul_ps( row2, tmp1 ) );
    minor2 = _mm_add_ps( _mm_mul_ps( row1, tmp1 ), minor2 );
    tmp1 = _mm_shuffle_ps( tmp1, tmp1, 0x4E );
    minor1 = _mm_add_ps( _mm_mul_ps( row2, tmp1 ), minor1 );
    minor2 = _mm_sub_ps( minor2, _mm_mul_ps( row1, tmp1 ) );

    // -----------------------------------------------
    tmp1 = _mm_mul_ps( row0, row2 );
    tmp1 = _mm_shuffle_ps( tmp1, tmp1, 0xB1 );
    minor1 = _mm_add_ps( _mm_mul_ps( row3, tmp1 ), minor1 );
    minor3 = _mm_sub_ps( minor3, _mm_mul_ps( row1, tmp1 ) );
    tmp1 = _mm_shuffle_ps( tmp1, tmp1, 0x4E );
    minor1 = _mm_sub_ps( minor1, _mm_mul_ps( row3, tmp1 ) );
    minor3 = _mm_add_ps( _mm_mul_ps( row1, tmp1 ), minor3 );

    // -----------------------------------------------
    det = _mm_mul_ps( row0, minor0 );
    det = _mm_add_ps( _mm_shuffle_ps( det, det, 0x4E ), det );
    det = _mm_add_ss( _mm_shuffle_ps( det, det, 0xB1 ), det );
    tmp1 = _mm_rcp_ss( det );
    det = _mm_sub_ss( _mm_add_ss( tmp1, tmp1 ), _mm_mul_ss( det, _mm_mul_ss( tmp1, tmp1 ) ) );
    det = _mm_shuffle_ps( det, det, 0x00 );
    minor0 = _mm_mul_ps( det, minor0 );

    // _mm_storel_pi((__m64*)(src), minor0);
    // _mm_storeh_pi((__m64*)(src+2), minor0);
    m_col0.vec = minor0;
    minor1 = _mm_mul_ps( det, minor1 );

    // _mm_storel_pi((__m64*)(src+4), minor1);
    // _mm_storeh_pi((__m64*)(src+6), minor1);
    m_col1.vec = minor1;
    minor2 = _mm_mul_ps( det, minor2 );

    // _mm_storel_pi((__m64*)(src+ 8), minor2);
    // _mm_storeh_pi((__m64*)(src+10), minor2);
    m_col2.vec = minor2;
    minor3 = _mm_mul_ps( det, minor3 );

    // _mm_storel_pi((__m64*)(src+12), minor3);
    // _mm_storeh_pi((__m64*)(src+14), minor3);
    m_col3.vec = minor3;
  }

  LinearMath::SSEMatrix4x4 SSEMatrix4x4::InvertedCopy() const
  {
    SSEMatrix4x4 matrix( *this );
    matrix.Invert();
    return matrix;
  }

  LinearMath::SSEMatrix4x4 SSEMatrix4x4::TransposedCopy() const
  {
    SSEMatrix4x4 result( *this );
    result.Transpose();
    return result;
  }

  void SSEMatrix4x4::Transpose()
  {
    _MM_TRANSPOSE4_PS( m_col0.vec, m_col1.vec, m_col2.vec, m_col3.vec );

    // __m128 T3 = _mm_unpacklo_ps(m_col0, m_col1);
    // __m128 T2 = _mm_unpacklo_ps(m_col2, m_col3);
    // __m128 T1 = _mm_unpackhi_ps(m_col0, m_col1);
    // __m128 T0 = _mm_unpackhi_ps(m_col2, m_col3);
    //
    // m_col0 = _mm_unpacklo_ps(T0, T1);
    // m_col1 = _mm_unpackhi_ps(T0, T1);
    // m_col2 = _mm_unpacklo_ps(T2, T3);
    // m_col3 = _mm_unpackhi_ps(T2, T3);
  }

  float SSEMatrix4x4::GetM_1_1() const
  {
    return m_col0.GetX();
  }

  float SSEMatrix4x4::GetM_1_2() const
  {
    return m_col0.GetY();

  }

  float SSEMatrix4x4::GetM_1_3() const
  {
    return m_col0.GetZ();

  }

  float SSEMatrix4x4::GetM_1_4() const
  {
    return m_col0.GetW();

  }

  float SSEMatrix4x4::GetM_2_1() const
  {
    return m_col1.GetX();
  }

  float SSEMatrix4x4::GetM_2_2() const
  {
    return m_col1.GetY();

  }

  float SSEMatrix4x4::GetM_2_3() const
  {
    return m_col1.GetZ();

  }

  float SSEMatrix4x4::GetM_2_4() const
  {
    return m_col1.GetW();

  }

  float SSEMatrix4x4::GetM_3_1() const
  {
    return m_col2.GetX();
  }

  float SSEMatrix4x4::GetM_3_2() const
  {
    return m_col2.GetY();

  }

  float SSEMatrix4x4::GetM_3_3() const
  {
    return m_col2.GetZ();

  }

  float SSEMatrix4x4::GetM_3_4() const
  {
    return m_col2.GetW();

  }

  float SSEMatrix4x4::GetM_4_1() const
  {
    return m_col3.GetX();
  }

  float SSEMatrix4x4::GetM_4_2() const
  {
    return m_col3.GetY();

  }

  float SSEMatrix4x4::GetM_4_3() const
  {
    return m_col3.GetZ();

  }

  float SSEMatrix4x4::GetM_4_4() const
  {
    return m_col3.GetW();

  }

  LinearMath::SSEMatrix4x4 SSEMatrix4x4::CreateLookAt( const SSEVector3& from,
    const SSEVector3& to,
    const SSEVector3& up )
  {
    SSEVector3 x, y, z;

    z = ( to - from ).NormalizedCopy();
    x = z.CrossProduct( up.NormalizedCopy() ).NormalizedCopy();
    y = x.CrossProduct( z );
    z *= -1;

    return SSEMatrix4x4(
      x.GetX(), x.GetY(), x.GetZ(), -x.DotProduct( from ),
      y.GetX(), y.GetY(), y.GetZ(), -y.DotProduct( from ),
      z.GetX(), z.GetY(), z.GetZ(), -z.DotProduct( from ),
      0, 0, 0, 1
      );
  }

  LinearMath::SSEMatrix4x4 SSEMatrix4x4::CreateLookDir( const SSEVector3& dir, const SSEVector3& up )
  {
    SSEVector3 x, y, z;

    z = dir.NormalizedCopy();
    x = z.CrossProduct( up.NormalizedCopy() ).NormalizedCopy();
    y = x.CrossProduct( z );
    z *= -1;

    return SSEMatrix4x4(
      x.GetX(), x.GetY(), x.GetZ(), 0,
      y.GetX(), y.GetY(), y.GetZ(), 0,
      z.GetX(), z.GetY(), z.GetZ(), 0,
      0, 0, 0, 1
      );
  }

  void SSEMatrix4x4::GetAsFloatArray( float* arr ) const
  {
    _mm_storeu_ps( arr, m_col0.vec );
    _mm_storeu_ps( arr + 4, m_col1.vec );
    _mm_storeu_ps( arr + 8, m_col2.vec );
    _mm_storeu_ps( arr + 12, m_col3.vec );
  }

  LinearMath::SSEMatrix4x4 SSEMatrix4x4::CreateFrustumMatrix(
    float left,
    float right,
    float bottom,
    float top,
    float nearPlane,
    float farPlane )
  {

    return SSEMatrix4x4(
      ( 2.0f*nearPlane ) / ( right - left ), 0, ( right + left ) / ( right - left ), 0,
      0, ( 2.0f*nearPlane ) / ( top - bottom ), ( top + bottom ) / ( top - bottom ), 0,
      0, 0, -( farPlane + nearPlane ) / ( farPlane - nearPlane ), -2 * ( farPlane * nearPlane ) / ( farPlane - nearPlane ),
      0, 0, -1, 0
      );
  }

  LinearMath::SSEMatrix4x4 SSEMatrix4x4::CreateRotationX( const Radian_tpl< float >& rad )
  {
    float sin = MathHelper_tpl< float >::Sin( rad );
    float cos = MathHelper_tpl< float >::Cos( rad );

    return SSEMatrix4x4
      (
      1, 0, 0, 0,
      0, cos, -sin, 0,
      0, sin, cos, 0,
      0, 0, 0, 1
      );
  }

  LinearMath::SSEMatrix4x4 SSEMatrix4x4::CreateRotationY( const Radian_tpl< float >& rad )
  {
    float sin = MathHelper_tpl< float >::Sin( rad );
    float cos = MathHelper_tpl< float >::Cos( rad );

    return SSEMatrix4x4
      (
      cos, 0, sin, 0,
      0, 1, 0, 0,
      -sin, 0, cos, 0,
      0, 0, 0, 1
      );
  }

  LinearMath::SSEMatrix4x4 SSEMatrix4x4::CreateRotationZ( const Radian_tpl< float >& rad )
  {
    float sin = MathHelper_tpl< float >::Sin( rad );
    float cos = MathHelper_tpl< float >::Cos( rad );

    return SSEMatrix4x4
      (
      cos, -sin, 0, 0,
      sin, cos, 0, 0,
      0, 0, 1, 0,
      0, 0, 0, 1
      );
  }

  LinearMath::SSEMatrix4x4 SSEMatrix4x4::CreateTranslation( const SSEVector3& translation )
  {
    float values[ 4 ];
    _mm_storeu_ps( values, translation.vec );

    return SSEMatrix4x4(
      1, 0, 0, values[ 0 ],
      0, 1, 0, values[ 1 ],
      0, 0, 1, values[ 2 ],
      0, 0, 0, 1
      );
  }

  LinearMath::SSEMatrix4x4 SSEMatrix4x4::CreateScale( const SSEVector3& scale )
  {
    float values[ 4 ];
    _mm_storeu_ps( values, scale.vec );

    return SSEMatrix4x4(
      values[ 1 ], 0, 0, 0,
      0, values[ 2 ], 0, 0,
      0, 0, values[ 3 ], 0,
      0, 0, 0, 1
      );
  }

  const SSEVector4& SSEMatrix4x4::GetCol0() const
  {
    return m_col0;
  }

  const SSEVector4& SSEMatrix4x4::GetCol1() const
  {
    return m_col1;
  }

  const SSEVector4& SSEMatrix4x4::GetCol2() const
  {
    return m_col2;
  }

  const SSEVector4& SSEMatrix4x4::GetCol3() const
  {
    return m_col3;
  }

  void SSEMatrix4x4::SetRow0( const SSEVector4& vec )
  {
    SetRow( 0, vec );
  }

  void SSEMatrix4x4::SetRow1( const SSEVector4& vec )
  {
    SetRow( 1, vec );
  }

  void SSEMatrix4x4::SetRow2( const SSEVector4& vec )
  {
    SetRow( 2, vec );
  }

  void SSEMatrix4x4::SetRow3( const SSEVector4& vec )
  {
    SetRow( 3, vec );
  }

  void SSEMatrix4x4::SetRow( Numerics::uint8 idx, const SSEVector4& vec )
  {
    float tmp[ 4 ];
    vec.GetFloatArray( tmp );
    m_col0.SetElem( idx, tmp[ 0 ] );
    m_col1.SetElem( idx, tmp[ 1 ] );
    m_col2.SetElem( idx, tmp[ 2 ] );
    m_col3.SetElem( idx, tmp[ 3 ] );
  }

  void SSEMatrix4x4::SetCol0( const SSEVector4& vec )
  {
    m_col0 = vec;
  }

  void SSEMatrix4x4::SetCol1( const SSEVector4& vec )
  {
    m_col1 = vec;
  }

  void SSEMatrix4x4::SetCol2( const SSEVector4& vec )
  {
    m_col2 = vec;
  }

  void SSEMatrix4x4::SetCol3( const SSEVector4& vec )
  {
    m_col3 = vec;
  }

  void SSEMatrix4x4::SetCol( Numerics::uint8 idx, const SSEVector4& vec )
  {
    switch( idx )
    {
    case 0:
      SetCol0( vec );
      break;
    case 1:
      SetCol1( vec );
      break;
    case 2:
      SetCol2( vec );
      break;
    case 3:
      SetCol3( vec );
      break;
    }
  }

  LinearMath::SSEMatrix4x4 SSEMatrix4x4::CreateProjectionMatrix( Radian_tpl<float> viewAngle, float width, float height, float nearPlane, float farPlane )
  {
    float halfHeight = ( MathHelper_tpl<float>::Tan( viewAngle / 2.0f )*nearPlane );

    float halfScaledAspectRatio = halfHeight*( width / height );

    return CreateFrustumMatrix( -halfScaledAspectRatio, halfScaledAspectRatio, -halfHeight, halfHeight, nearPlane, farPlane );
  }

  SSEVector4 SSEMatrix4x4::GetRow0() const
  {
    return SSEVector4( m_col0.GetX(), m_col1.GetX(), m_col2.GetX(), m_col3.GetX() );
  }

  SSEVector4 SSEMatrix4x4::GetRow1() const
  {
    return SSEVector4( m_col0.GetY(), m_col1.GetY(), m_col2.GetY(), m_col3.GetY() );

  }

  SSEVector4 SSEMatrix4x4::GetRow2() const
  {
    return SSEVector4( m_col0.GetZ(), m_col1.GetZ(), m_col2.GetZ(), m_col3.GetZ() );

  }

  SSEVector4 SSEMatrix4x4::GetRow3() const
  {
    return SSEVector4( m_col0.GetW(), m_col1.GetW(), m_col2.GetW(), m_col3.GetW() );

  }

}
