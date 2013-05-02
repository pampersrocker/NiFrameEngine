#pragma once
#ifndef _MP_VECTOR_3_H_
#define _MP_VECTOR_3_H_
#include "MathLibPCH.h"

namespace LinearMath
{
	template < typename ScalarType >
	class Vector3_tpl
	{

public:

		Vector3_tpl( void );

		Vector3_tpl( ScalarType val );

		Vector3_tpl( ScalarType x, ScalarType y , ScalarType z);

		~Vector3_tpl( void );

		/**
		Operators
		
		*/

		// + Operators
		Vector3_tpl< ScalarType > operator +( const Vector3_tpl< ScalarType >& v ) const;
		Vector3_tpl< ScalarType > &operator +=( const Vector3_tpl< ScalarType >& v );

		// - Operators
		Vector3_tpl< ScalarType > operator -( const Vector3_tpl< ScalarType >& v ) const;
		Vector3_tpl< ScalarType > &operator -=( const Vector3_tpl< ScalarType >& v );

		// * Operators
		Vector3_tpl< ScalarType > operator *( const ScalarType& scalar ) const;
		Vector3_tpl< ScalarType > &operator *=( const ScalarType& scalar );
		inline friend Vector3_tpl< ScalarType > operator *(const ScalarType& scalar, const Vector3_tpl< ScalarType >& v)
		{
			return Vector3_tpl< ScalarType > ( v.X * scalar, v.Y * scalar , v.Z * scalar );
		}

		ScalarType operator *( const Vector3_tpl< ScalarType >& v ) const;

		// / Operators
		Vector3_tpl< ScalarType > operator /( const ScalarType& scalar ) const;
		Vector3_tpl< ScalarType > &operator /=( const ScalarType& scalar );

		//^ Operators
		Vector3_tpl< ScalarType > operator ^( const Vector3_tpl< ScalarType >& v) const;

		ScalarType X;
		ScalarType Y;
		ScalarType Z;

		// Methods

		ScalarType GetX( void ) const;
		ScalarType GetY( void ) const;
		ScalarType GetZ( void ) const;

		ScalarType LengthSquared() const;
		ScalarType Length() const;
		void Normalize();
		Vector3_tpl< ScalarType > NormalizedCopy() const;
		Vector3_tpl< ScalarType > CrossProduct( const Vector3_tpl< ScalarType >& v ) const;
		ScalarType DotProduct (const Vector3_tpl< ScalarType >& v) const;

protected:

private:

	};

	template < typename ScalarType >
	ScalarType LinearMath::Vector3_tpl<ScalarType>::GetZ( void ) const
	{
		return Z;
	}

	template < typename ScalarType >
	ScalarType LinearMath::Vector3_tpl<ScalarType>::GetY( void ) const
	{
		return Y;
	}

	template < typename ScalarType >
	ScalarType LinearMath::Vector3_tpl<ScalarType>::GetX( void ) const
	{
		return X;
	}


	template < typename ScalarType > Vector3_tpl< ScalarType >::Vector3_tpl( void ) :
		X( 0 ),
		Y( 0 ),
		Z( 0 )
	{
	}

	template < typename ScalarType > Vector3_tpl< ScalarType >::Vector3_tpl( ScalarType val ) :
		X( val ),
		Y( val ),
		Z( val )
	{
	}

	template < typename ScalarType > 
	Vector3_tpl< ScalarType >::Vector3_tpl( ScalarType x, ScalarType y, ScalarType z ) :
		X( x ),
		Y( y ),
		Z( z )
	{
	}

	template < typename ScalarType > Vector3_tpl< ScalarType >::~Vector3_tpl( void )
	{
	}

	template < typename ScalarType > 
	Vector3_tpl< ScalarType > Vector3_tpl< ScalarType >::operator+( const Vector3_tpl< ScalarType >& v ) const
	{
		return Vector3_tpl< ScalarType >( X + v.X, Y + v.Y, Z + v.Z );
	}

	template < typename ScalarType > 
	Vector3_tpl< ScalarType > &Vector3_tpl< ScalarType >::operator+=( const Vector3_tpl< ScalarType >& v )
	{
		X += v.X;
		Y += v.Y;
		Z += v.Z;
		return *this;
	}

	template < typename ScalarType > 
	LinearMath::Vector3_tpl< ScalarType > 
		Vector3_tpl< ScalarType >::operator-( const Vector3_tpl< ScalarType >& v ) const
	{
		return Vector3_tpl< ScalarType >( X - v.X, Y - v.Y, Z - v.Z );
	}

	template < typename ScalarType > 
	Vector3_tpl< ScalarType > &Vector3_tpl< ScalarType >::operator-=( const Vector3_tpl< ScalarType >& v )
	{
		X -= v.X;
		Y -= v.Y;
		Z -= v.Z;
		return *this;
	}

	template < typename ScalarType > 
	LinearMath::Vector3_tpl< ScalarType > Vector3_tpl< ScalarType >::operator*( const ScalarType& scalar ) const
	{
		return Vector3_tpl< ScalarType >( X * scalar, Y * scalar, Z * scalar );
	}

	template < typename ScalarType > 
	ScalarType Vector3_tpl< ScalarType >::operator*( const Vector3_tpl< ScalarType >& v ) const
	{
		return ( X * v.X ) + ( Y * v.Y ) + ( Z * v.Z );
	}

	template < typename ScalarType > 
	Vector3_tpl< ScalarType > &Vector3_tpl< ScalarType >::operator*=( const ScalarType& scalar )
	{
		X *= scalar;
		Y *= scalar;
		Z *= scalar;
		return *this;
	}

	template < typename ScalarType > 
	LinearMath::Vector3_tpl< ScalarType > Vector3_tpl< ScalarType >::operator/( const ScalarType& scalar ) const
	{
		return Vector3_tpl< ScalarType >( X / scalar, Y / scalar, Z / scalar );
	}

	template < typename ScalarType > 
	Vector3_tpl< ScalarType > &Vector3_tpl< ScalarType >::operator/=( const ScalarType& scalar )
	{
		X /= scalar;
		Y /= scalar;
		Z /= scalar;
		return *this;
	}

	template < typename ScalarType > ScalarType Vector3_tpl< ScalarType >::LengthSquared( void ) const
	{
		return ( X * X ) + ( Y * Y ) + ( Z * Z );
	}

	template < typename ScalarType > ScalarType Vector3_tpl< ScalarType >::Length( void ) const
	{
		return sqrt( LengthSquared() );
	}

	template < typename ScalarType > void Vector3_tpl< ScalarType >::Normalize( void )
	{
		ScalarType length = Length();
		X /= length;
		Y /= length;
		Z /= length;
	}

	template < typename ScalarType > 
	LinearMath::Vector3_tpl< ScalarType > Vector3_tpl< ScalarType >::NormalizedCopy( void ) const
	{
		ScalarType length = Length();
		return Vector3_tpl< ScalarType >( X / length, Y / length, Z / length );
	}

	template < typename ScalarType > 
	LinearMath::Vector3_tpl< ScalarType > 
		Vector3_tpl< ScalarType >::operator^( const Vector3_tpl< ScalarType >& v ) const
	{
		return Vector3_tpl< ScalarType >( 
			Y * v.Z - Z * v.Y, 
			Z * v.X - X * v.Z, 
			X * v.Y - Y * v.X 
			);
	}

	template < typename ScalarType > 
	LinearMath::Vector3_tpl< ScalarType > 
		Vector3_tpl< ScalarType >::CrossProduct( const Vector3_tpl< ScalarType >& v ) const
	{
		return *this ^ v;
	}

	template < typename ScalarType >
	ScalarType Vector3_tpl< ScalarType>::DotProduct(const Vector3_tpl< ScalarType >& v) const
	{
		return ( ( X * v.X ) + ( Y * v.Y ) + ( Z * v.Z ) );
	}
}
#endif
