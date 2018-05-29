#pragma once

#include <xmmintrin.h>
#include "MathHelper.hpp"
#include "SSEVector4.hpp"

#ifndef SSEMatrix4x4_h__
  #define SSEMatrix4x4_h__

namespace LinearMath
{
  class SSEVector3;

  class SSEMatrix4x4
  {
  public:

    SSEMatrix4x4();
    SSEMatrix4x4( const SSEVector4& col0, const SSEVector4& col1, const SSEVector4& col2, const SSEVector4& col3 );
    SSEMatrix4x4(
      float M11, float M12, float M13, float M14,
      float M21, float M22, float M23, float M24,
      float M31, float M32, float M33, float M34,
      float M41, float M42, float M43, float M44
    );
    SSEMatrix4x4( const SSEMatrix4x4& matrix );

    SSEMatrix4x4 operator +( const SSEMatrix4x4& matrix ) const;

    SSEMatrix4x4& operator +=( const SSEMatrix4x4& matrix );

    SSEMatrix4x4 operator -( const SSEMatrix4x4& matrix ) const;

    SSEMatrix4x4 operator -=( const SSEMatrix4x4& matrix );

    SSEMatrix4x4 operator *( const SSEMatrix4x4& matrix ) const;
    SSEVector4 operator *( const SSEVector4& vec ) const;

    SSEMatrix4x4& operator *=( const SSEMatrix4x4& matrix );

    static const SSEMatrix4x4 ZERO;
    static const SSEMatrix4x4 ZERO_AFFINE;
    static const SSEMatrix4x4 IDENTITY;

    static SSEMatrix4x4 CreateLookAt( const SSEVector3& from, const SSEVector3& to, const SSEVector3& up );

    static SSEMatrix4x4 CreateLookDir( const SSEVector3& dir, const SSEVector3& up );

    static SSEMatrix4x4 CreateFrustumMatrix( float left,
      float right,
      float bottom,
      float top,
      float nearPlane,
      float farPlane );

    static SSEMatrix4x4 CreateProjectionMatrix( Radian_tpl<float> viewAngle, float width, float height, float nearPlane, float farPlane );

    static SSEMatrix4x4 CreateRotationX( const Radian_tpl< float >& angle );

    static SSEMatrix4x4 CreateRotationY( const Radian_tpl< float >& angle );

    static SSEMatrix4x4 CreateRotationZ( const Radian_tpl< float >& angle );

    static SSEMatrix4x4 CreateTranslation( const SSEVector3& translation );

    static SSEMatrix4x4 CreateScale( const SSEVector3& scale );

    void Invert();

    SSEMatrix4x4 InvertedCopy() const;

    SSEMatrix4x4 TransposedCopy() const;

    void Transpose();

    void GetAsFloatArray( float* arr ) const;

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

    const SSEVector4& GetCol0() const;
    const SSEVector4& GetCol1() const;
    const SSEVector4& GetCol2() const;
    const SSEVector4& GetCol3() const;


    SSEVector4 GetRow0() const;
    SSEVector4 GetRow1() const;
    SSEVector4 GetRow2() const;
    SSEVector4 GetRow3() const;

    void SetCol0(const SSEVector4& vec);
    void SetCol1(const SSEVector4& vec);
    void SetCol2(const SSEVector4& vec);
    void SetCol3( const SSEVector4& vec );
    void SetCol(Numerics::uint8 idx, const SSEVector4& vec );


    void SetRow0(const SSEVector4& vec);
    void SetRow1(const SSEVector4& vec);
    void SetRow2(const SSEVector4& vec);
    void SetRow3( const SSEVector4& vec );
    void SetRow(Numerics::uint8 idx, const SSEVector4& vec );

    ~SSEMatrix4x4();

  private:

    SSEVector4 m_col0, m_col1, m_col2, m_col3;
  };
}

#endif  // SSEMatrix4x4_h__
