#pragma once
#ifndef _MP_VECTOR_2_H_
  #define _MP_VECTOR_2_H_

  #include "MathHelper.hpp"

namespace LinearMath
{
  template< typename ScalarType >
  class Vector2_tpl
  {
  public:

    typedef ScalarType DataType;
    static const Numerics::uint32 size = 2U;

    Vector2_tpl( void );

    explicit Vector2_tpl( ScalarType val );

    Vector2_tpl( ScalarType x, ScalarType y );


    Vector2_tpl( const Vector2_tpl< ScalarType >& v );

    ~Vector2_tpl( void );

    /**
    Operators

    */

    Vector2_tpl< ScalarType >& operator =( const Vector2_tpl< ScalarType >& v );

    // + Operators
    Vector2_tpl< ScalarType > operator +( const Vector2_tpl< ScalarType >& v ) const;

    Vector2_tpl< ScalarType >& operator +=( const Vector2_tpl< ScalarType >& v );
    Vector2_tpl< ScalarType > operator +() const;

    // - Operators
    Vector2_tpl< ScalarType > operator -( const Vector2_tpl< ScalarType >& v ) const;

    Vector2_tpl< ScalarType > operator -() const;

    Vector2_tpl< ScalarType >& operator -=( const Vector2_tpl< ScalarType >& v );

    // * Operators
    Vector2_tpl< ScalarType > operator *( const ScalarType& scalar ) const;

    Vector2_tpl< ScalarType >& operator *=( const ScalarType& scalar );

    inline friend Vector2_tpl< ScalarType > operator *( 
      const ScalarType& scalar,
      const Vector2_tpl< ScalarType >& v )
    {
      return Vector2_tpl< ScalarType >( scalar * v.X, scalar * v.Y );
    }

    ScalarType operator *( const Vector2_tpl< ScalarType >& v ) const;

    // / Operators
    Vector2_tpl< ScalarType > operator /( const ScalarType& scalar ) const;

    Vector2_tpl< ScalarType >& operator /=( const ScalarType& scalar );

    // == Operators
    bool operator ==( const Vector2_tpl< ScalarType >& vec ) const;
    bool operator !=( const Vector2_tpl< ScalarType >& vec ) const;

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
        
      };
      
      ScalarType data[2];

    };



    // Methods
    ScalarType LengthSquared( void ) const;

    ScalarType Length( void ) const;

    void Normalize( void );

    Vector2_tpl< ScalarType > NormalizedCopy( void ) const;

    template< typename T >
    ScalarType PerpDotProduct( const Vector2_tpl< T >& v ) const;

    template< typename T >
    ScalarType DotProduct( const Vector2_tpl< T >& v ) const;

    Radian_tpl< ScalarType > GetRotation() const;

    Vector2_tpl< ScalarType > Rotate( const Radian_tpl< ScalarType >& rad,
      const bool relative = true );

    Vector2_tpl< ScalarType > MulPerElem( const Vector2_tpl< ScalarType >& rhs ) const;

  protected:

  private:
  };

  template< typename ScalarType >
  Vector2_tpl< ScalarType > LinearMath::Vector2_tpl<ScalarType>::MulPerElem( const Vector2_tpl< ScalarType >& rhs ) const
  {
    return Vector2_tpl< ScalarType >( x * rhs.x, y*rhs.y );
  }

  template< typename ScalarType >
  bool LinearMath::Vector2_tpl<ScalarType>::operator!=( const Vector2_tpl< ScalarType >& vec ) const
  {
    return ( X != vec.X || Y != vec.Y );
  }

  template< typename ScalarType >
  bool LinearMath::Vector2_tpl<ScalarType>::operator==( const Vector2_tpl< ScalarType >& vec ) const
  {
    return ( X == vec.X && Y == vec.Y );
  }

  template< typename ScalarType >
  Vector2_tpl< ScalarType >& LinearMath::Vector2_tpl<ScalarType>::operator=( const Vector2_tpl< ScalarType >& v )
  {
    X = ( ScalarType ) v.X;
    Y = ( ScalarType ) v.Y;
    return *this;
  }

  template< typename ScalarType >
  Vector2_tpl< ScalarType >::Vector2_tpl( void ) :
    X( 0 ),
    Y( 0 )
  {
  }

  template< typename ScalarType >
  Vector2_tpl< ScalarType >::Vector2_tpl( ScalarType val ) :
    X( val ),
    Y( val )
  {
  }

  template< typename ScalarType >
  Vector2_tpl< ScalarType >::Vector2_tpl( ScalarType x, ScalarType y ) :
    X( x ),
    Y( y )
  {
  }

  template< typename ScalarType >
  Vector2_tpl< ScalarType >::Vector2_tpl( const Vector2_tpl< ScalarType >& v ) :
    X( ( ScalarType ) v.X ),
    Y( ( ScalarType ) v.Y )
  {

  }

  template< typename ScalarType >
  Vector2_tpl< ScalarType >::~Vector2_tpl( void )
  {
  }

  template< typename ScalarType >
  Vector2_tpl< ScalarType > Vector2_tpl< ScalarType >::operator +( const Vector2_tpl<ScalarType >& v ) const
  {
    return Vector2_tpl< ScalarType >( this->X + ( ScalarType ) v.X, this->Y + ( ScalarType ) v.Y );
  }

  template< typename ScalarType >
  Vector2_tpl< ScalarType > Vector2_tpl< ScalarType >::operator +() const
  {
    return Vector2_tpl< ScalarType >( x, y );
  }


  template< typename ScalarType >
  Vector2_tpl< ScalarType > Vector2_tpl< ScalarType >::operator -() const
  {
    return Vector2_tpl< ScalarType >( -x, -y );
  }

  template< typename ScalarType >
  Vector2_tpl< ScalarType >& Vector2_tpl< ScalarType >::operator +=( const Vector2_tpl< ScalarType >& v )
  {
    X += ( ScalarType )v.X;
    Y += ( ScalarType )v.Y;
    return *this;
  }

  template< typename ScalarType >
  Vector2_tpl< ScalarType > Vector2_tpl< ScalarType >::operator -( const Vector2_tpl< ScalarType >& v ) const
  {
    return Vector2_tpl< ScalarType >( this->X - v.X, this->Y - v.Y );
  }

  template< typename ScalarType >
  Vector2_tpl< ScalarType >& Vector2_tpl< ScalarType >::operator -=( const Vector2_tpl< ScalarType >& v )
  {
    X -= v.X;
    Y -= v.Y;
    return *this;
  }

  template< typename ScalarType >
  Vector2_tpl< ScalarType > Vector2_tpl< ScalarType >::operator *( const ScalarType& scalar ) const
  {
    return Vector2_tpl< ScalarType >( X * scalar, Y * scalar );
  }

  template< typename ScalarType >
  ScalarType Vector2_tpl< ScalarType >::operator *( const Vector2_tpl<ScalarType >& v ) const
  {
    return ( X * ( ScalarType ) v.X ) + ( Y * ( ScalarType ) v.Y );
  }

  template< typename ScalarType >
  Vector2_tpl< ScalarType >& Vector2_tpl< ScalarType >::operator *=( const ScalarType& scalar )
  {
    X *= scalar;
    Y *= scalar;
    return *this;
  }

  template< typename ScalarType >
  Vector2_tpl< ScalarType > Vector2_tpl< ScalarType >::operator /( const ScalarType& scalar ) const
  {
    return Vector2_tpl< ScalarType >( X / scalar, Y / scalar );
  }

  template< typename ScalarType >
  Vector2_tpl< ScalarType >& Vector2_tpl< ScalarType >::operator /=( const ScalarType& scalar )
  {
    X /= scalar;
    Y /= scalar;
    return *this;
  }

  template< typename ScalarType >
  ScalarType Vector2_tpl< ScalarType >::LengthSquared( void ) const
  {
    return ( X * X ) + ( Y * Y );
  }

  template< typename ScalarType >
  ScalarType Vector2_tpl< ScalarType >::Length( void ) const
  {
    return MathHelper_tpl< ScalarType >::Sqrt( LengthSquared() );
  }

  template< typename ScalarType >
  void Vector2_tpl< ScalarType >::Normalize( void )
  {
    ScalarType length = Length();
    X /= length;
    Y /= length;
  }

  template< typename ScalarType >
  Vector2_tpl< ScalarType > Vector2_tpl< ScalarType >::NormalizedCopy( void ) const
  {
    ScalarType length = Length();

    return Vector2_tpl< ScalarType >( X / length, Y / length );
  }

  template< typename ScalarType >
  template< typename T >
  ScalarType Vector2_tpl< ScalarType >::PerpDotProduct( const Vector2_tpl< T >& v ) const
  {
    return Vector2_tpl< ScalarType >( -Y, X ) * v;
  }

  template< typename ScalarType >
  template< typename T >
  ScalarType Vector2_tpl< ScalarType >::DotProduct( const Vector2_tpl< T >& v ) const
  {
    return *this * v;
  }

  template< typename ScalarType >
  Radian_tpl< ScalarType > Vector2_tpl< ScalarType >::GetRotation() const
  {
    Radian_tpl< ScalarType > result = MathHelper_tpl< ScalarType >::ACos( X / Length() );

    return Y >= 0 ? result : -result;
  }

  template< typename ScalarType >
  Vector2_tpl< ScalarType > Vector2_tpl< ScalarType >::Rotate( const Radian_tpl< ScalarType >& rad,
    const bool relative  /*= true*/ )
  {
    Radian_tpl< ScalarType > amount = rad;

    if( !relative )
    {
      amount -= GetRotation();
    }

    ScalarType sin = MathHelper_tpl< ScalarType >::Sin( amount );
    ScalarType cos = MathHelper_tpl< ScalarType >::Cos( amount );

    return Vector2_tpl< ScalarType >( cos * X - sin * Y, sin * X + cos * Y );
  }
}
#endif  // ifndef _MP_VECTOR_2_H_
