#pragma once
#ifndef _MP_VECTOR_2_H_
#define _MP_VECTOR_2_H_

#include "MathLibPCH.h"
#include "MathHelper.h"

namespace LinearMath
{
	template < typename ScalarType > 
	class Vector2_tpl
	{

public:

		Vector2_tpl( void );

		Vector2_tpl( ScalarType val );

		Vector2_tpl( ScalarType x, ScalarType y );

		~ Vector2_tpl( void );

		/**
		Operators
		
		*/

		// + Operators
		Vector2_tpl<ScalarType> operator +( const Vector2_tpl<ScalarType>& v ) const;
		Vector2_tpl<ScalarType> &operator +=( const Vector2_tpl<ScalarType>& v );

		// - Operators
		Vector2_tpl<ScalarType> operator -( const Vector2_tpl<ScalarType>& v ) const;
		Vector2_tpl<ScalarType> &operator -=( const Vector2_tpl<ScalarType>& v );

		// * Operators
		Vector2_tpl<ScalarType> operator *( const ScalarType& scalar ) const;
		Vector2_tpl<ScalarType> &operator *=( const ScalarType& scalar );
		inline friend Vector2_tpl<ScalarType> operator*( const ScalarType& scalar, const Vector2_tpl<ScalarType>& v )
		{
			return Vector2_tpl<ScalarType>( scalar * v.X, scalar * v.Y );
		}

		ScalarType operator *( const Vector2_tpl<ScalarType>& v ) const;

		// / Operators
		Vector2_tpl<ScalarType> operator /( const ScalarType& scalar ) const;
		Vector2_tpl<ScalarType> &operator /=( const ScalarType& scalar );

		ScalarType X;
		ScalarType Y;

		// Methods
		ScalarType LengthSquared( void ) const;
		ScalarType Length( void ) const;
		void Normalize( void );
		Vector2_tpl<ScalarType> NormalizedCopy( void ) const;
		ScalarType PerpDotProduct( const Vector2_tpl<ScalarType>& v ) const;
		ScalarType DotProduct( const Vector2_tpl<ScalarType>& v ) const;
		ScalarType Vector2_tpl<ScalarType>::GetRotation() const;
		Vector2_tpl<ScalarType> Vector2_tpl<ScalarType>::Rotate(const Radian_tpl<ScalarType>& rad, const bool relative = true);
protected:

private:

	};

	template < typename ScalarType > Vector2_tpl<ScalarType>::Vector2_tpl( void ) :
		X( 0 ),
		Y( 0 )
	{
	}

	template < typename ScalarType > Vector2_tpl<ScalarType>::Vector2_tpl( ScalarType val ) :
		X( val ),
		Y( val )
	{
	}

	template < typename ScalarType > Vector2_tpl<ScalarType>::Vector2_tpl( ScalarType x, ScalarType y ) :
		X( x ),
		Y( y )
	{
	}

	template < typename ScalarType > Vector2_tpl<ScalarType>::~Vector2_tpl( void )
	{
	}

	template < typename ScalarType > Vector2_tpl<ScalarType> Vector2_tpl<ScalarType>::operator+( const Vector2_tpl<ScalarType>& v ) const
	{

		return Vector2_tpl<ScalarType>( this->X + v.X, this->Y + v.Y );
	}

	template < typename ScalarType > Vector2_tpl<ScalarType> &Vector2_tpl<ScalarType>::operator+=( const Vector2_tpl<ScalarType>& v )
	{
		X += v.X;
		Y += v.Y;
		return *this;
	}

	template < typename ScalarType > Vector2_tpl<ScalarType> Vector2_tpl<ScalarType>::operator-( const Vector2_tpl<ScalarType>& v ) const
	{
		return Vector2_tpl<ScalarType>( this->X - v.X, this->Y - v.Y );
	}

	template < typename ScalarType > Vector2_tpl<ScalarType> &Vector2_tpl<ScalarType>::operator-=( const Vector2_tpl<ScalarType>& v )
	{
		X -= v.X;
		Y -= v.Y;
		return *this;
	}

	template < typename ScalarType > Vector2_tpl<ScalarType> Vector2_tpl<ScalarType>::operator*( const ScalarType& scalar ) const
	{
		return Vector2_tpl<ScalarType>( X * scalar, Y * scalar );
	}

	template < typename ScalarType > ScalarType Vector2_tpl<ScalarType>::operator*( const Vector2_tpl<ScalarType>& v ) const
	{
		return ( X * v.X ) + ( Y * v.Y );
	}

	template < typename ScalarType > Vector2_tpl<ScalarType> &Vector2_tpl<ScalarType>::operator*=( const ScalarType& scalar )
	{
		X *= scalar;
		Y *= scalar;
		return *this;
	}

	template < typename ScalarType > Vector2_tpl<ScalarType> Vector2_tpl<ScalarType>::operator/( const ScalarType& scalar ) const
	{
		return Vector2_tpl<ScalarType>( X / scalar, Y / scalar );
	}

	template < typename ScalarType > Vector2_tpl<ScalarType> &Vector2_tpl<ScalarType>::operator/=( const ScalarType& scalar )
	{
		X /= scalar;
		Y /= scalar;
		return *this;
	}

	template < typename ScalarType > ScalarType Vector2_tpl<ScalarType>::LengthSquared( void ) const
	{
		return ( X * X ) + ( Y * Y );
	}

	template < typename ScalarType > ScalarType Vector2_tpl<ScalarType>::Length( void ) const
	{
		return sqrt( LengthSquared() );
	}

	template < typename ScalarType > void Vector2_tpl<ScalarType>::Normalize( void )
	{
		ScalarType length = Length();
		X /= length;
		Y /= length;
	}

	template < typename ScalarType > Vector2_tpl<ScalarType> Vector2_tpl<ScalarType>::NormalizedCopy( void ) const
	{
		ScalarType length = Length();

		return Vector2_tpl<ScalarType>( X / length, Y / length );
	}

	template < typename ScalarType > ScalarType Vector2_tpl<ScalarType>::PerpDotProduct( const Vector2_tpl<ScalarType>& v ) const
	{
		return Vector2_tpl<ScalarType>(-Y, X) * v;
	}

	template < typename ScalarType > ScalarType Vector2_tpl<ScalarType>::DotProduct( const Vector2_tpl<ScalarType>& v ) const
	{
		return *this * v;
	}

	template < typename ScalarType > ScalarType Vector2_tpl<ScalarType>::GetRotation() const
	{
		ScalarType result = MathHelper_tpl<ScalarType>::ACos(X / Length());

		return Y >= 0 ? result : -result;
	}

	template < typename ScalarType > Vector2_tpl<ScalarType> Vector2_tpl<ScalarType>::Rotate( const Radian_tpl<ScalarType>& rad, const bool relative /*= true*/ )
	{
		ScalarType amount = rad.AsRadianValue();
		if ( ! relative )
		{
			amount -= GetRotation();
		}

		ScalarType sin = MathHelper_tpl<ScalarType>::Sin(amount);
		ScalarType cos = MathHelper_tpl<ScalarType>::Cos(amount);

		return Vector2_tpl<ScalarType>(cos * X - sin * Y, sin * X + cos * Y);
	}
}
#endif