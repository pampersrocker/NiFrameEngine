#pragma once
#ifndef Quaternion_h__
  #define Quaternion_h__

  #include "../MathLibPCH.hpp"
  #include "MathHelper.hpp"
  #include "Vector3.hpp"
  #include "Matrix4x4.hpp"

namespace LinearMath
{
  template< typename ScalarType >
  class Quaternion_tpl
  {
  public:

    typedef ScalarType data_type;  

    Quaternion_tpl( void );

    Quaternion_tpl( const ScalarType w, const ScalarType x, const ScalarType y, const ScalarType z );

    Quaternion_tpl( const Vector3_tpl< ScalarType >& axis, const Radian_tpl< ScalarType >& angle );

    ~Quaternion_tpl();

    Matrix4x4_tpl< ScalarType > ToRotationMatrix( void ) const;

    static Quaternion_tpl< ScalarType > FromAngleAxis(
      Vector3_tpl< ScalarType >& axis, const Radian_tpl< ScalarType >& angle );

    Quaternion_tpl< ScalarType > operator *( const Quaternion_tpl< ScalarType >& quat ) const;

    Radian_tpl< ScalarType > GetAngle( void ) const;

    ScalarType W, X, Y, Z;

  protected:

  private:
  };

  template< typename ScalarType >
  LinearMath::Quaternion_tpl< ScalarType >::Quaternion_tpl( void ) :
    W( 1 ),
    X( 0 ),
    Y( 0 ),
    Z( 0 )
  {
  }

  template< typename ScalarType >
  Quaternion_tpl< ScalarType > LinearMath::Quaternion_tpl< ScalarType >::FromAngleAxis(
    Vector3_tpl< ScalarType >& axis,
    const Radian_tpl< ScalarType >& angle )
  {
    return Quaternion_tpl< ScalarType >( axis, angle );
  }

  template< typename ScalarType >
  LinearMath::Quaternion_tpl< ScalarType >::Quaternion_tpl(
    const Vector3_tpl< ScalarType >& axis,
    const Radian_tpl< ScalarType >& angle )
  {
    Radian_tpl< ScalarType > halfAngle = (ScalarType)0.5 * angle;

    W = MathHelper_tpl< ScalarType >::Cos( halfAngle );

    ScalarType sin = MathHelper_tpl< ScalarType >::Sin( halfAngle );
    X = sin * axis.X;
    Y = sin * axis.Y;
    Z = sin * axis.Z;
  }

  template< typename ScalarType >
  LinearMath::Quaternion_tpl< ScalarType >::Quaternion_tpl(
    const ScalarType w,
    const ScalarType x,
    const ScalarType y,
    const ScalarType z ) :
    W( w ),
    X( x ),
    Y( y ),
    Z( z )
  {
  }

  template< typename ScalarType >
  Quaternion_tpl< ScalarType > LinearMath::Quaternion_tpl< ScalarType >::operator *(
    const Quaternion_tpl< ScalarType >& quat ) const
  {
    return Quaternion_tpl< ScalarType >(
      ( ( W * quat.W ) - ( ( X * quat.X ) + ( Y * quat.Y )  + ( Z * quat.Z ) ) ),
      ( ( W * quat.X ) + ( quat.W * X ) + ( Y * quat.Z ) - ( Z * quat.Y ) ),
      ( ( W * quat.Y ) + ( quat.W * Y ) + ( Z * quat.X ) - ( X * quat.Z ) ),
      ( ( W * quat.Z ) + ( quat.W * Z ) + ( X * quat.Y ) - ( Y * quat.X ) )
    );
  }

  template< typename ScalarType >
  Matrix4x4_tpl< ScalarType > LinearMath::Quaternion_tpl< ScalarType >::ToRotationMatrix( void ) const
  {
    ScalarType xx = X * X;
    ScalarType yy = Y * Y;
    ScalarType zz = Z * Z;
    ScalarType ww = W * W;
    ScalarType xy = 2 * X * Y;
    ScalarType xz = 2 * X * Z;
    ScalarType xw = 2 * X * W;
    ScalarType yz = 2 * Y * Z;
    ScalarType yw = 2 * Y * W;
    ScalarType zw = 2 * Z * W;

    return Matrix4x4_tpl< ScalarType >
         (
      ww + xx - yy - zz, xy + zw, xz - yw, 0,
      xy - zw, ww - xx + yy - zz, yz + xw, 0,
      xz + yw, yz - xw, ww - xx - yy + zz, 0,
      0, 0, 0, 1
         );
  }

  template< typename ScalarType >
  LinearMath::Quaternion_tpl< ScalarType >::~Quaternion_tpl()
  {
  }

  template< typename ScalarType >
  Radian_tpl< ScalarType > LinearMath::Quaternion_tpl< ScalarType >::GetAngle( void ) const
  {
    return Radian_tpl< ScalarType >( MathHelper_tpl< ScalarType >::ACos( W ) * 2 );
  }
}

#endif  // Quaternion_h__
