#pragma once
#ifndef _MP_VECTOR_4_H_
#define _MP_VECTOR_4_H_

namespace LinearMath
{
  template< typename ScalarType >
  class Vector4_tpl
  {
  public:

    typedef ScalarType DataType;
    static const Numerics::uint32 size = 4U;

    Vector4_tpl( void );

    explicit Vector4_tpl( ScalarType val );

    Vector4_tpl( ScalarType x, ScalarType y, ScalarType z, ScalarType w );

    template< typename T >
    explicit Vector4_tpl( const Vector4_tpl< T >& vec );

    ~Vector4_tpl( void );

    /**
    Operators

    */

    Vector4_tpl< ScalarType >& operator =( const Vector4_tpl< ScalarType >& v );

    // + Operators
    template< typename T >
    Vector4_tpl< ScalarType > operator +( const Vector4_tpl< T >& v ) const;

    Vector4_tpl< ScalarType > operator +( void ) const;

    template< typename T >
    Vector4_tpl< ScalarType >& operator +=( const Vector4_tpl< T >& v );

    // - Operators

    template< typename T >
    Vector4_tpl< ScalarType > operator -( const Vector4_tpl< T >& v ) const;

    Vector4_tpl< ScalarType > operator -( void ) const;

    template< typename T >
    Vector4_tpl< ScalarType >& operator -=( const Vector4_tpl< T >& v );

    // * Operators
    Vector4_tpl< ScalarType > operator *( const ScalarType& scalar ) const;

    Vector4_tpl< ScalarType >& operator *=( const ScalarType& scalar );

    inline friend Vector4_tpl< ScalarType > operator *( const ScalarType& scalar,
      const Vector4_tpl< ScalarType >& v )
    {
      return Vector4_tpl< ScalarType >( v.X * scalar, v.Y * scalar, v.Z * scalar, v.W * scalar );
    }
    template< typename T >
    ScalarType operator *( const Vector4_tpl< T >& v ) const;

    // / Operators
    template< typename T >
    Vector4_tpl< ScalarType > operator /( const T& scalar ) const;

    template< typename T >
    Vector4_tpl< ScalarType >& operator /=( const T& scalar );

    // == Operators
    bool operator ==( const Vector4_tpl< ScalarType >& v ) const;

    bool operator !=( const Vector4_tpl< ScalarType >& v ) const;

    // ^ Operators
    template< typename T >
    Vector4_tpl< ScalarType > operator ^( const Vector4_tpl< T >& v ) const;

    union
    {
      struct
      {
        union
        {
          ScalarType X;
          ScalarType x;
        };

        union
        {
          ScalarType Y;
          ScalarType y;
        };

        union
        {
          ScalarType Z;
          ScalarType z;
        };

        union
        {
          ScalarType W;
          ScalarType w;
        };
      };

      ScalarType data[ 4 ];
    };

    // Methods

    ScalarType GetX( void ) const;

    ScalarType GetY( void ) const;

    ScalarType GetZ( void ) const;

    ScalarType GetW( void ) const;

    ScalarType LengthSquared() const;

    ScalarType Length() const;

    void Normalize();

    Vector3_tpl< ScalarType > ToVec3() const;

    Vector4_tpl< ScalarType > NormalizedCopy() const;

    template< typename T >
    Vector4_tpl< ScalarType > CrossProduct( const Vector4_tpl< T >& v ) const;

    template< typename T >
    ScalarType DotProduct( const Vector4_tpl< T >& v ) const;

  protected:

  private:
  };

  template< typename ScalarType >
  inline
  Vector3_tpl< ScalarType > LinearMath::Vector4_tpl<ScalarType>::ToVec3() const
  {
    return Vector3_tpl< ScalarType >( x, y, z );
  }

  template< typename ScalarType >
  Vector4_tpl< ScalarType > LinearMath::Vector4_tpl< ScalarType >::operator +( void ) const
  {
    return Vector4_tpl< ScalarType >( x, y, z, w );
  }

  template< typename ScalarType >
  Vector4_tpl< ScalarType > LinearMath::Vector4_tpl< ScalarType >::operator -( void ) const
  {
    return Vector4_tpl< ScalarType >( -x, -y, -z, -w );
  }

  template< typename ScalarType >
  template< typename T >
  LinearMath::Vector4_tpl< ScalarType >::Vector4_tpl( const Vector4_tpl< T >& vec ) :
    X( ( ScalarType ) vec.X ),
    Y( ( ScalarType ) vec.Y ),
    Z( ( ScalarType ) vec.Z ),
    W( ( ScalarType ) vec.W )

  {
  }

  template< typename ScalarType >
  Vector4_tpl< ScalarType >& LinearMath::Vector4_tpl< ScalarType >::operator =( const Vector4_tpl< ScalarType >& v )
  {
    X = v.X;
    Y = v.Y;
    Z = v.Z;
    W = v.W;

    return *this;
  }

  template< typename ScalarType >
  ScalarType LinearMath::Vector4_tpl< ScalarType >::GetW( void ) const
  {
    return W;
  }

  template< typename ScalarType >
  ScalarType LinearMath::Vector4_tpl< ScalarType >::GetZ( void ) const
  {
    return Z;
  }

  template< typename ScalarType >
  ScalarType LinearMath::Vector4_tpl< ScalarType >::GetY( void ) const
  {
    return Y;
  }

  template< typename ScalarType >
  ScalarType LinearMath::Vector4_tpl< ScalarType >::GetX( void ) const
  {
    return X;
  }

  template< typename ScalarType >
  Vector4_tpl< ScalarType >::Vector4_tpl( void ) :
    X( 0 ),
    Y( 0 ),
    Z( 0 ),
    W( 0 )
  {
  }

  template< typename ScalarType >
  Vector4_tpl< ScalarType >::Vector4_tpl( ScalarType val ) :
    X( val ),
    Y( val ),
    Z( val ),
    W( val )
  {
  }

  template< typename ScalarType >
  Vector4_tpl< ScalarType >::Vector4_tpl( ScalarType x, ScalarType y, ScalarType z, ScalarType w ) :
    X( x ),
    Y( y ),
    Z( z ),
    W( w )
  {
  }

  template< typename ScalarType >
  Vector4_tpl< ScalarType >::~Vector4_tpl( void )
  {
  }

  template< typename ScalarType >
  template< typename T >
  Vector4_tpl< ScalarType > Vector4_tpl< ScalarType >::operator +( const Vector4_tpl< T >& v ) const
  {
    return Vector4_tpl< ScalarType >( X + ( ScalarType ) v.X, Y + ( ScalarType ) v.Y, Z + ( ScalarType ) v.Z, W + ( ScalarType ) v.W );
  }

  template< typename ScalarType >
  template< typename T >
  Vector4_tpl< ScalarType >& Vector4_tpl< ScalarType >::operator +=( const Vector4_tpl< T >& v )
  {
    X += ( ScalarType ) v.X;
    Y += ( ScalarType ) v.Y;
    Z += ( ScalarType ) v.Z;
    W += ( ScalarType ) v.W;
    return *this;
  }

  template< typename ScalarType >
  template< typename T >
  LinearMath::Vector4_tpl< ScalarType >
    Vector4_tpl< ScalarType >::operator -( const Vector4_tpl< T >& v ) const
  {
    return Vector4_tpl< ScalarType >(
      X - ( ScalarType ) v.X,
      Y - ( ScalarType ) v.Y,
      Z - ( ScalarType ) v.Z,
      W - ( ScalarType ) v.W );
  }

  template< typename ScalarType >
  template< typename T >
  Vector4_tpl< ScalarType >& Vector4_tpl< ScalarType >::operator -=( const Vector4_tpl< T >& v )
  {
    X -= ( ScalarType ) v.X;
    Y -= ( ScalarType ) v.Y;
    Z -= ( ScalarType ) v.Z;
    W -= ( ScalarType ) v.W;
    return *this;
  }

  template< typename ScalarType >
  LinearMath::Vector4_tpl< ScalarType > Vector4_tpl< ScalarType >::operator *( const ScalarType& scalar ) const
  {
    return Vector4_tpl< ScalarType >( X * scalar, Y * scalar, Z * scalar, W * scalar );
  }

  template< typename ScalarType >
  template< typename T >
  ScalarType Vector4_tpl< ScalarType >::operator *( const Vector4_tpl< T >& v ) const
  {
    return ( X * ( ScalarType ) v.X )
      + ( Y * ( ScalarType ) v.Y )
      + ( Z * ( ScalarType ) v.Z )
      + ( W * ( ScalarType ) v.W );
  }

  template< typename ScalarType >
  Vector4_tpl< ScalarType >& Vector4_tpl< ScalarType >::operator *=( const ScalarType& scalar )
  {
    X *= scalar;
    Y *= scalar;
    Z *= scalar;
    W *= scalar;
    return *this;
  }

  template< typename ScalarType >
  template< typename T >
  LinearMath::Vector4_tpl< ScalarType > Vector4_tpl< ScalarType >::operator /( const T& scalar ) const
  {
    return Vector4_tpl< ScalarType >( X / scalar, Y / scalar, Z / scalar, W / scalar );
  }

  template< typename ScalarType >
  template< typename T >
  Vector4_tpl< ScalarType >& Vector4_tpl< ScalarType >::operator /=( const T& scalar )
  {
    X /= scalar;
    Y /= scalar;
    Z /= scalar;
    W /= scalar;
    return *this;
  }

  template< typename ScalarType >
  bool LinearMath::Vector4_tpl< ScalarType >::operator !=( const Vector4_tpl< ScalarType >& vec ) const
  {
    return X != vec.X || Y != vec.Y || Z != vec.Z || W != vec.W;
  }

  template< typename ScalarType >
  bool LinearMath::Vector4_tpl< ScalarType >::operator ==( const Vector4_tpl< ScalarType >& vec ) const
  {
    return X == vec.X && Y == vec.Y && Z == vec.Z&& W == vec.W;
  }

  template< typename ScalarType >
  ScalarType Vector4_tpl< ScalarType >::LengthSquared( void ) const
  {
    return ( X * X ) + ( Y * Y ) + ( Z * Z ) + ( W * W );
  }

  template< typename ScalarType >
  ScalarType Vector4_tpl< ScalarType >::Length( void ) const
  {
    return sqrt( LengthSquared() );
  }

  template< typename ScalarType >
  void Vector4_tpl< ScalarType >::Normalize( void )
  {
    ScalarType length = Length();
    X /= length;
    Y /= length;
    Z /= length;
    W /= length;
  }

  template< typename ScalarType >
  LinearMath::Vector4_tpl< ScalarType > Vector4_tpl< ScalarType >::NormalizedCopy( void ) const
  {
    ScalarType length = Length();
    return Vector4_tpl< ScalarType >( X / length, Y / length, Z / length, W / length );
  }

  template< typename ScalarType >
  template< typename T >
  LinearMath::Vector4_tpl< ScalarType >
    Vector4_tpl< ScalarType >::operator ^( const Vector4_tpl< T >& v ) const
  {
    return Vector4_tpl< ScalarType >(
      Y * ( ScalarType ) v.Z - Z * ( ScalarType ) v.Y,
      Z * ( ScalarType ) v.X - X * ( ScalarType ) v.Z,
      X * ( ScalarType ) v.Y - Y * ( ScalarType ) v.X
      // No w, this is a vec3 operation
      );
  }

  template< typename ScalarType >
  template< typename T >
  LinearMath::Vector4_tpl< ScalarType >
    Vector4_tpl< ScalarType >::CrossProduct( const Vector4_tpl< T >& v ) const
  {
    return *this ^  v;
  }

  template< typename ScalarType >
  template< typename T >
  ScalarType Vector4_tpl< ScalarType >::DotProduct( const Vector4_tpl< T >& v ) const
  {
    return ( X * ( ScalarType ) v.X )
      + ( Y * ( ScalarType ) v.Y )
      + ( Z * ( ScalarType ) v.Z ),
      + ( W * ( ScalarType ) v.W );
  }
}
#endif  // ifndef _MP_VECTOR_4_H_
