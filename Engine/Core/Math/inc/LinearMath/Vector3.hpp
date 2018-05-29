#pragma once
#ifndef _MP_VECTOR_3_H_
  #define _MP_VECTOR_3_H_

namespace LinearMath
{

  template< typename ScalarType >
  class Vector3_tpl
  {
  public:

    typedef ScalarType DataType;
    static const Numerics::uint32 size = 3U;

    Vector3_tpl( void );

    explicit Vector3_tpl( ScalarType val );

    Vector3_tpl( ScalarType x, ScalarType y, ScalarType z );

    template< typename T >
    explicit Vector3_tpl( const Vector3_tpl< T >& vec );

    ~Vector3_tpl( void );

    /**
    Operators

    */

    Vector3_tpl< ScalarType >& operator =( const Vector3_tpl< ScalarType >& v );

    // + Operators
    Vector3_tpl< ScalarType > operator +( const Vector3_tpl< ScalarType >& v ) const;

    Vector3_tpl< ScalarType > operator +( void ) const;

    Vector3_tpl< ScalarType >& operator +=( const Vector3_tpl< ScalarType >& v );

    // - Operators

    template< typename T >
    Vector3_tpl< ScalarType > operator -( const Vector3_tpl< T >& v ) const;

    Vector3_tpl< ScalarType > operator -( void ) const;

    template< typename T >
    Vector3_tpl< ScalarType >& operator -=( const Vector3_tpl< T >& v );

    // * Operators
    Vector3_tpl< ScalarType > operator *( const ScalarType& scalar ) const;

    Vector3_tpl< ScalarType >& operator *=( const ScalarType& scalar );

    inline friend Vector3_tpl< ScalarType > operator *( const ScalarType& scalar,
      const Vector3_tpl< ScalarType >& v )
    {
      return Vector3_tpl< ScalarType >( v.X * scalar, v.Y * scalar, v.Z * scalar );
    }
    template< typename T >
    ScalarType operator *( const Vector3_tpl< T >& v ) const;

    // / Operators
    template< typename T >
    Vector3_tpl< ScalarType > operator /( const T& scalar ) const;

    template< typename T >
    Vector3_tpl< ScalarType >& operator /=( const T& scalar );

    // == Operators
    bool operator ==( const Vector3_tpl< ScalarType >& v ) const;

    bool operator !=( const Vector3_tpl< ScalarType >& v ) const;

    // ^ Operators
    template< typename T >
    Vector3_tpl< ScalarType > operator ^( const Vector3_tpl< T >& v ) const;

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
      };

      ScalarType data[ 3 ];
    };

    // Methods

    ScalarType GetX( void ) const;

    ScalarType GetY( void ) const;

    ScalarType GetZ( void ) const;

    ScalarType LengthSquared() const;

    ScalarType Length() const;

    void Normalize();

    Vector3_tpl< ScalarType > NormalizedCopy() const;

    template< typename T >
    Vector3_tpl< ScalarType > CrossProduct( const Vector3_tpl< T >& v ) const;

    template< typename T >
    ScalarType DotProduct( const Vector3_tpl< T >& v ) const;

  protected:

  private:
  };

  template< typename ScalarType >
  Vector3_tpl< ScalarType > LinearMath::Vector3_tpl< ScalarType >::operator +( void ) const
  {
    return Vector3_tpl< ScalarType >( x, y, z );
  }

  template< typename ScalarType >
  Vector3_tpl< ScalarType > LinearMath::Vector3_tpl< ScalarType >::operator -( void ) const
  {
    return Vector3_tpl< ScalarType >( -x, -y, -z );
  }

  template< typename ScalarType >
  template< typename T >
  LinearMath::Vector3_tpl< ScalarType >::Vector3_tpl( const Vector3_tpl< T >& vec ) :
    X( ( ScalarType )vec.X ),
    Y( ( ScalarType )vec.Y ),
    Z( ( ScalarType )vec.Z )
  {
  }

  template< typename ScalarType >
  Vector3_tpl< ScalarType >& LinearMath::Vector3_tpl< ScalarType >::operator =( const Vector3_tpl< ScalarType >& v )
  {
    X = v.X;
    Y = v.Y;
    Z = v.Z;

    return *this;
  }

  template< typename ScalarType >
  ScalarType LinearMath::Vector3_tpl< ScalarType >::GetZ( void ) const
  {
    return Z;
  }

  template< typename ScalarType >
  ScalarType LinearMath::Vector3_tpl< ScalarType >::GetY( void ) const
  {
    return Y;
  }

  template< typename ScalarType >
  ScalarType LinearMath::Vector3_tpl< ScalarType >::GetX( void ) const
  {
    return X;
  }

  template< typename ScalarType >
  Vector3_tpl< ScalarType >::Vector3_tpl( void ) :
    X( 0 ),
    Y( 0 ),
    Z( 0 )
  {
  }

  template< typename ScalarType >
  Vector3_tpl< ScalarType >::Vector3_tpl( ScalarType val ) :
    X( val ),
    Y( val ),
    Z( val )
  {
  }

  template< typename ScalarType >
  Vector3_tpl< ScalarType >::Vector3_tpl( ScalarType x, ScalarType y, ScalarType z ) :
    X( x ),
    Y( y ),
    Z( z )
  {
  }

  template< typename ScalarType >
  Vector3_tpl< ScalarType >::~Vector3_tpl( void )
  {
  }

  template< typename ScalarType >
  Vector3_tpl< ScalarType > Vector3_tpl< ScalarType >::operator +( const Vector3_tpl< ScalarType >& v ) const
  {
    return Vector3_tpl< ScalarType >( X + ( ScalarType )v.X, Y + ( ScalarType )v.Y, Z + ( ScalarType )v.Z );
  }

  template< typename ScalarType >
  Vector3_tpl< ScalarType >& Vector3_tpl< ScalarType >::operator +=( const Vector3_tpl< ScalarType >& v )
  {
    X += ( ScalarType )v.X;
    Y += ( ScalarType )v.Y;
    Z += ( ScalarType )v.Z;
    return *this;
  }

  template< typename ScalarType >
  template< typename T >
  LinearMath::Vector3_tpl< ScalarType >
  Vector3_tpl< ScalarType >::operator -( const Vector3_tpl< T >& v ) const
  {
    return Vector3_tpl< ScalarType >(
      X - ( ScalarType )v.X,
      Y - ( ScalarType )v.Y,
      Z - ( ScalarType )v.Z );
  }

  template< typename ScalarType >
  template< typename T >
  Vector3_tpl< ScalarType >& Vector3_tpl< ScalarType >::operator -=( const Vector3_tpl< T >& v )
  {
    X -= ( ScalarType )v.X;
    Y -= ( ScalarType )v.Y;
    Z -= ( ScalarType )v.Z;
    return *this;
  }

  template< typename ScalarType >
  LinearMath::Vector3_tpl< ScalarType > Vector3_tpl< ScalarType >::operator *( const ScalarType& scalar ) const
  {
    return Vector3_tpl< ScalarType >( X * scalar, Y * scalar, Z * scalar );
  }

  template< typename ScalarType >
  template< typename T >
  ScalarType Vector3_tpl< ScalarType >::operator *( const Vector3_tpl< T >& v ) const
  {
    return ( X * ( ScalarType )v.X )
         + ( Y * ( ScalarType )v.Y )
         + ( Z * ( ScalarType )v.Z );
  }

  template< typename ScalarType >
  Vector3_tpl< ScalarType >& Vector3_tpl< ScalarType >::operator *=( const ScalarType& scalar )
  {
    X *= scalar;
    Y *= scalar;
    Z *= scalar;
    return *this;
  }

  template< typename ScalarType >
  template< typename T >
  LinearMath::Vector3_tpl< ScalarType > Vector3_tpl< ScalarType >::operator /( const T& scalar ) const
  {
    return Vector3_tpl< ScalarType >( X / scalar, Y / scalar, Z / scalar );
  }

  template< typename ScalarType >
  template< typename T >
  Vector3_tpl< ScalarType >& Vector3_tpl< ScalarType >::operator /=( const T& scalar )
  {
    X /= scalar;
    Y /= scalar;
    Z /= scalar;
    return *this;
  }

  template< typename ScalarType >
  bool LinearMath::Vector3_tpl< ScalarType >::operator !=( const Vector3_tpl< ScalarType >& vec ) const
  {
    return X != vec.X || Y != vec.Y || Z != vec.Z;
  }

  template< typename ScalarType >
  bool LinearMath::Vector3_tpl< ScalarType >::operator ==( const Vector3_tpl< ScalarType >& vec ) const
  {
    return X == vec.X && Y == vec.Y && Z == vec.Z;
  }

  template< typename ScalarType >
  ScalarType Vector3_tpl< ScalarType >::LengthSquared( void ) const
  {
    return ( X * X ) + ( Y * Y ) + ( Z * Z );
  }

  template< typename ScalarType >
  ScalarType Vector3_tpl< ScalarType >::Length( void ) const
  {
    return (ScalarType)sqrt( (ScalarType) LengthSquared() );
  }

  template< typename ScalarType >
  void Vector3_tpl< ScalarType >::Normalize( void )
  {
    ScalarType length = Length();
    X /= length;
    Y /= length;
    Z /= length;
  }

  template< typename ScalarType >
  LinearMath::Vector3_tpl< ScalarType > Vector3_tpl< ScalarType >::NormalizedCopy( void ) const
  {
    ScalarType length = Length();
    return Vector3_tpl< ScalarType >( X / length, Y / length, Z / length );
  }

  template< typename ScalarType >
  template< typename T >
  LinearMath::Vector3_tpl< ScalarType >
  Vector3_tpl< ScalarType >::operator ^( const Vector3_tpl< T >& v ) const
  {
    return Vector3_tpl< ScalarType >(
      Y * ( ScalarType )v.Z - Z * ( ScalarType )v.Y,
      Z * ( ScalarType )v.X - X * ( ScalarType )v.Z,
      X * ( ScalarType )v.Y - Y * ( ScalarType )v.X
    );
  }

  template< typename ScalarType >
  template< typename T >
  LinearMath::Vector3_tpl< ScalarType >
  Vector3_tpl< ScalarType >::CrossProduct( const Vector3_tpl< T >& v ) const
  {
    return *this ^  v;
  }

  template< typename ScalarType >
  template< typename T >
  ScalarType Vector3_tpl< ScalarType >::DotProduct( const Vector3_tpl< T >& v ) const
  {
    return ( X * ( ScalarType )v.X )
         + ( Y * ( ScalarType )v.Y )
         + ( Z * ( ScalarType )v.Z );
  }
}
#endif  // ifndef _MP_VECTOR_3_H_
