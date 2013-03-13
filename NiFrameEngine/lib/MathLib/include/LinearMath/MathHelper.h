#pragma once
#include "MathLibPCH.h"
#include <vector>

namespace LinearMath
{
	template < typename ScalarType > class Degree_tpl;

	template < typename ScalarType >
	class Radian_tpl
	{

public:

		Radian_tpl( void );
		explicit Radian_tpl( const ScalarType& scalar );
		Radian_tpl( const Radian_tpl& rad );
		Radian_tpl( const Degree_tpl<ScalarType>& deg );
		~Radian_tpl( void );

		//Radian &operator =( const T& scalar );
		Radian_tpl &operator =( const Radian_tpl& rad );
		Radian_tpl &operator =( const Degree_tpl<ScalarType>& deg );

		Radian_tpl operator +( const Radian_tpl& rad ) const;
		Radian_tpl &operator +=( const Radian_tpl& rad );

		Radian_tpl operator -( const Radian_tpl& rad ) const;
		Radian_tpl &operator -=( const Radian_tpl& rad );

		Radian_tpl operator *( const ScalarType& scalar ) const;
		Radian_tpl &operator *=( const ScalarType& scalar );
		friend Radian_tpl operator *( const ScalarType& scalar, const Radian_tpl& rad );

		Radian_tpl operator /( const ScalarType& scalar ) const;
		Radian_tpl &operator /=( const ScalarType& scalar );

		bool operator ==( const Radian_tpl& rad ) const;
		bool operator !=( const Radian_tpl& rad ) const;
		bool operator >=( const Radian_tpl& rad ) const;
		bool operator <=( const Radian_tpl& rad ) const;
		bool operator >( const Radian_tpl& rad ) const;
		bool operator <( const Radian_tpl& rad ) const;

		operator Degree_tpl<ScalarType>( void ) const;

		ScalarType AsRadianValue( void ) const;
		Degree_tpl<ScalarType> ToDegree( void ) const;
		ScalarType AsDegreeValue( void ) const;

private:

		ScalarType m_Rad;
	};

	template < typename ScalarType >
	class Degree_tpl
	{

public:

		Degree_tpl( void );
		explicit Degree_tpl<ScalarType>( const ScalarType& scalar );
		Degree_tpl( const Radian_tpl<ScalarType>& rad );
		Degree_tpl( const Degree_tpl& deg );
		~ Degree_tpl( void );

		//Degree &operator =( const T& scalar );
		Degree_tpl<ScalarType> &operator =( const Radian_tpl<ScalarType>& rad );
		Degree_tpl<ScalarType> &operator =( const Degree_tpl<ScalarType>& deg );

		Degree_tpl<ScalarType> operator +( const Degree_tpl<ScalarType>& rad ) const;
		Degree_tpl<ScalarType> &operator +=( const Degree_tpl<ScalarType>& rad );

		Degree_tpl<ScalarType> operator -( const Degree_tpl<ScalarType>& rad ) const;
		Degree_tpl<ScalarType> &operator -=( const Degree_tpl<ScalarType>& rad );

		Degree_tpl<ScalarType> operator *( const ScalarType& scalar ) const;
		Degree_tpl<ScalarType> &operator *=( const ScalarType& scalar );

		Degree_tpl<ScalarType> operator /( const ScalarType& scalar ) const;
		Degree_tpl<ScalarType> &operator /=( const ScalarType& scalar );

		bool operator ==( const Degree_tpl<ScalarType>& rad ) const;
		bool operator !=( const Degree_tpl<ScalarType>& rad ) const;
		bool operator >=( const Degree_tpl<ScalarType>& rad ) const;
		bool operator <=( const Degree_tpl<ScalarType>& rad ) const;
		bool operator >( const Degree_tpl<ScalarType>& rad ) const;
		bool operator < ( const Degree_tpl<ScalarType>&rad ) const;

		operator Radian_tpl<ScalarType>( void ) const;

		//operator T( void );
		ScalarType AsRadianValue( void ) const;
		Radian_tpl<ScalarType> ToRad( void ) const;
		ScalarType AsDegreeValue( void ) const;

private:

		ScalarType m_Degree;
	};
	template < typename ScalarType >
	class MathHelper_tpl
	{

public:

		static const ScalarType PI;

		static const ScalarType GetPI( void );

		static Radian_tpl<ScalarType> DegreeToRad( const Degree_tpl<ScalarType>& deg );
		static Degree_tpl<ScalarType> RadToDegree( const Radian_tpl<ScalarType>& rad );

		static ScalarType Sin( const ScalarType& scalar );
		static ScalarType ASin( const ScalarType& scalar );

		static ScalarType Cos( const ScalarType& scalar );
		static ScalarType ACos( const ScalarType& scalar );

		static ScalarType Tan( const ScalarType& scalar );
		static ScalarType ATan( const ScalarType& scalar );

		static ScalarType Sqrt( const ScalarType& scalar );

		static ScalarType Max( const ScalarType& scalar1, const ScalarType& scalar2 );
		static ScalarType Max( const std::vector<ScalarType>& values );

		static ScalarType Min( const ScalarType& scalar1, const ScalarType& scalar2 );
		static ScalarType Min( const std::vector<ScalarType>& values );

		static ScalarType Abs( const ScalarType& scalar );

		static ScalarType Lerp( const ScalarType& p1, const ScalarType& p2, const ScalarType& lerpVal );

private:

		MathHelper_tpl<ScalarType>( void );
		MathHelper_tpl<ScalarType>( const MathHelper_tpl<ScalarType>&  );
		~ MathHelper_tpl( void );
	};

	template < typename ScalarType > Radian_tpl<ScalarType>::Radian_tpl( void ) :
		m_Rad( 0 )
	{
	}

	template < typename ScalarType > Radian_tpl<ScalarType>::Radian_tpl( const ScalarType& scalar ) :
		m_Rad( scalar )
	{
	}

	template < typename ScalarType > Radian_tpl<ScalarType>::Radian_tpl( const Radian_tpl& rad ) :
		m_Rad( rad.m_Rad )
	{
	}

	template < typename ScalarType > Radian_tpl<ScalarType>::Radian_tpl( const Degree_tpl<ScalarType>& deg ) :
		m_Rad( MathHelper_tpl<ScalarType>::DegreeToRad<ScalarType>( deg ).AsRadianValue() )
	{
	}

	template < typename ScalarType > Radian_tpl<ScalarType>::~Radian_tpl( void )
	{
	}

	//Radian &Radian::operator=( const T& scalar )
	//{
	//	m_Rad = scalar;
	//	return *this;
	//}

	template < typename ScalarType > Radian_tpl<ScalarType> &Radian_tpl<ScalarType>::operator=( const Radian_tpl& rad )
	{
		m_Rad = rad.m_Rad;
		return *this;
	}

	template < typename ScalarType > 
	Radian_tpl<ScalarType> &Radian_tpl<ScalarType>::operator=( const Degree_tpl<ScalarType>& deg )
	{
		m_Rad = MathHelper_tpl<ScalarType>::DegreeToRad( deg ).AsRadianValue();

		return *this;
	}

	template < typename ScalarType > 
	Radian_tpl<ScalarType> Radian_tpl<ScalarType>::operator+( const Radian_tpl& rad ) const
	{
		return Radian_tpl( m_Rad + rad.m_Rad );
	}

	template < typename ScalarType > 
	Radian_tpl<ScalarType> &Radian_tpl<ScalarType>::operator+=( const Radian_tpl& rad )
	{
		m_Rad += rad.m_Rad;
		return *this;
	}

	template < typename ScalarType >
	Radian_tpl<ScalarType>::operator Degree_tpl<ScalarType>( void ) const
	{
		return MathHelper_tpl<ScalarType>::RadToDegree( *this );
	}

	template < typename ScalarType >
	ScalarType Radian_tpl<ScalarType>::AsRadianValue( void ) const
	{
		return m_Rad;
	}

	template < typename ScalarType >
	Degree_tpl<ScalarType> Radian_tpl<ScalarType>::ToDegree( void ) const
	{
		return MathHelper_tpl<ScalarType>::RadToDegree( *this );
	}

	template < typename ScalarType > ScalarType Radian_tpl<ScalarType>::AsDegreeValue( void ) const
	{
		return MathHelper_tpl<ScalarType>::RadToDegree( *this ).AsDegreeValue();
	}

	template < typename ScalarType >
	Radian_tpl<ScalarType> Radian_tpl<ScalarType>::operator-( const Radian_tpl& rad ) const
	{
		return Radian_tpl<ScalarType>( m_Rad - rad.m_Rad );
	}

	template < typename ScalarType > Radian_tpl<ScalarType> &Radian_tpl<ScalarType>::operator-=( const Radian_tpl& rad )
	{
		m_Rad -= rad.m_Rad;

		return *this;
	}

	template < typename ScalarType >
	Radian_tpl<ScalarType> Radian_tpl<ScalarType>::operator*( const ScalarType& scalar ) const
	{
		return Radian_tpl( m_Rad * scalar );
	}

	template < typename ScalarType > 
	Radian_tpl<ScalarType> operator*( const ScalarType& scalar, const Radian_tpl<ScalarType>& rad )
	{
		return Radian_tpl<ScalarType>( scalar * rad.m_Rad );
	}

	template < typename ScalarType > 
	Radian_tpl<ScalarType> &Radian_tpl<ScalarType>::operator*=( const ScalarType& scalar )
	{
		m_Rad *= scalar;
		return *this;
	}

	template < typename ScalarType > 
	Radian_tpl<ScalarType> Radian_tpl<ScalarType>::operator/( const ScalarType& scalar ) const
	{
		return Radian_tpl( m_Rad / scalar );
	}

	template < typename ScalarType > 
	Radian_tpl<ScalarType> &Radian_tpl<ScalarType>::operator/=( const ScalarType& scalar )
	{
		m_Rad /= scalar;

		return *this;
	}

	template < typename ScalarType > bool Radian_tpl<ScalarType>::operator==( const Radian_tpl<ScalarType>& rad ) const
	{
		return m_Rad == rad.m_Rad;
	}

	template < typename ScalarType > bool Radian_tpl<ScalarType>::operator!=( const Radian_tpl<ScalarType>& rad ) const
	{
		return m_Rad != rad.m_Rad;
	}

	template < typename ScalarType > bool Radian_tpl<ScalarType>::operator>=( const Radian_tpl<ScalarType>& rad ) const
	{
		return m_Rad >= rad.m_Rad;
	}

	template < typename ScalarType > bool Radian_tpl<ScalarType>::operator<=( const Radian_tpl<ScalarType>& rad ) const
	{
		return m_Rad <= rad.m_Rad;
	}

	template < typename ScalarType > bool Radian_tpl<ScalarType>::operator>( const Radian_tpl<ScalarType>& rad ) const
	{
		return m_Rad > rad.m_Rad;
	}

	template < typename ScalarType > bool Radian_tpl<ScalarType>::operator<( const Radian_tpl<ScalarType>& rad ) const
	{
		return m_Rad < rad.m_Rad;
	}




	template < typename ScalarType > const ScalarType MathHelper_tpl<ScalarType>:: PI = 3.14159265358979323846f;

	template < typename ScalarType > 
	Radian_tpl<ScalarType> MathHelper_tpl<ScalarType>::DegreeToRad( const Degree_tpl<ScalarType>& deg )
	{
		// r/(2*PI) = alpha/(360°)
		// <=> r = alpha * (PI/180°)
		// <=> alpha = r * (180/pi)
		return Radian_tpl<ScalarType>( deg.AsDegreeValue() * ( PI / 180.0f ) );
	}

	template < typename ScalarType > 
	Degree_tpl<ScalarType> MathHelper_tpl<ScalarType>::RadToDegree( const Radian_tpl<ScalarType>& rad )
	{
		// r/(2*PI) = alpha/(360°)
		// <=> r = alpha * (PI/180°)
		// <=> alpha = r * 180/pi
		return Degree_tpl( rad.AsRadianValue() * ( 180.0f / PI ) );
	}

	template < typename ScalarType > 
	MathHelper_tpl<ScalarType>::MathHelper_tpl( void )
	{
	}

	template < typename ScalarType > MathHelper_tpl<ScalarType>::~MathHelper_tpl( void )
	{
	}

	template < typename ScalarType > ScalarType MathHelper_tpl<ScalarType>::Sin( const ScalarType& scalar )
	{
		return sin( scalar );
	}

	template < typename ScalarType > ScalarType MathHelper_tpl<ScalarType>::ASin( const ScalarType& scalar )
	{
		return asin( scalar );
	}

	template < typename ScalarType > ScalarType MathHelper_tpl<ScalarType>::Cos( const ScalarType& scalar )
	{
		return cos( scalar );
	}

	template < typename ScalarType > ScalarType MathHelper_tpl<ScalarType>::ACos( const ScalarType& scalar )
	{
		return acos( scalar );
	}

	template < typename ScalarType > ScalarType MathHelper_tpl<ScalarType>::Tan( const ScalarType& scalar )
	{
		return tan( scalar );
	}

	template < typename ScalarType > ScalarType MathHelper_tpl<ScalarType>::ATan( const ScalarType& scalar )
	{
		return atan( scalar );
	}

	template < typename ScalarType > ScalarType MathHelper_tpl<ScalarType>::Sqrt( const ScalarType& scalar )
	{
		return sqrt( scalar );
	}

	template < typename ScalarType > ScalarType 
		MathHelper_tpl<ScalarType>::Max( const ScalarType& scalar1, const ScalarType& scalar2 )
	{
		return scalar1 > scalar2 ? scalar1 : scalar2;
	}

	template < typename ScalarType > ScalarType MathHelper_tpl<ScalarType>::Max( const std::vector<ScalarType>& values )
	{
		if( values.size() > 0 )
		{
			ScalarType max = values[0];
			for( 
				std::vector<ScalarType>::const_iterator iterator = values.cbegin(); 
				iterator != values.cend(); 
				++iterator 
				)
			{
				if( *iterator > max )
				{
					max = *iterator;
				}
			}

			return max;
		}
		else
		{
			return 0.0f;
		}
	}

	template < typename ScalarType > 
	ScalarType MathHelper_tpl<ScalarType>::Min( const ScalarType& scalar1, const ScalarType& scalar2 )
	{
		return scalar1 < scalar2 ? scalar1 : scalar2;
	}

	template < typename ScalarType > 
	ScalarType MathHelper_tpl<ScalarType>::Min( const std::vector<ScalarType>& values )
	{
		if( values.size() > 0 )
		{
			ScalarType min = values[0];
			for( 
				std::vector<ScalarType>::const_iterator iterator = values.cbegin(); 
				iterator != values.cend(); 
			++iterator 
				)
			{
				if( *iterator < min )
				{
					min = *iterator;
				}
			}

			return min;
		}
		else
		{
			return 0.0f;
		}
	}

	template < typename ScalarType > ScalarType MathHelper_tpl<ScalarType>::Abs( const ScalarType& scalar )
	{
		return scalar < 0 ? -scalar : scalar;
	}

	template < typename ScalarType > 
	ScalarType MathHelper_tpl<ScalarType>::Lerp( const ScalarType& p1, const ScalarType& p2, const ScalarType& lerpVal )
	{
		return p1 + ( ( p2 - p1 ) * lerpVal );
	}

	template < typename ScalarType > const ScalarType MathHelper_tpl<ScalarType>::GetPI()
	{
		return PI;
	}

	template < typename ScalarType > Degree_tpl<ScalarType>::Degree_tpl( void ) :
		m_Degree( 0.0f )
	{
	}

	template < typename ScalarType > Degree_tpl<ScalarType>::Degree_tpl( const ScalarType& scalar ) :
		m_Degree( scalar )
	{
	}

	template < typename ScalarType > Degree_tpl<ScalarType>::Degree_tpl( const Radian_tpl<ScalarType>& rad ) :
		m_Degree( MathHelper_tpl<ScalarType>::RadToDegree( rad ).m_Degree )
	{
	}

	template < typename ScalarType > Degree_tpl<ScalarType>::Degree_tpl( const Degree_tpl<ScalarType>& deg ) :
		m_Degree( deg.m_Degree )
	{
	}

	template < typename ScalarType > Degree_tpl<ScalarType>::~Degree_tpl( void )
	{
	}

	template < typename ScalarType > 
	Degree_tpl<ScalarType> &Degree_tpl<ScalarType>::operator=( const Radian_tpl<ScalarType>& rad )
	{
		m_Degree = MathHelper_tpl<ScalarType>::RadToDegree( rad ).AsDegreeValue();
		return *this;
	}

	template < typename ScalarType > 
	Degree_tpl<ScalarType> &Degree_tpl<ScalarType>::operator=( const Degree_tpl<ScalarType>& deg )
	{
		m_Degree = deg.AsDegreeValue();

		return *this;
	}

	template < typename ScalarType > Degree_tpl<ScalarType>::operator Radian_tpl<ScalarType>( void ) const
	{
		return MathHelper_tpl<ScalarType>::DegreeToRad( *this );
	}

	template < typename ScalarType > ScalarType Degree_tpl<ScalarType>::AsRadianValue( void ) const
	{
		return MathHelper_tpl<ScalarType>::DegreeToRad( *this ).AsRadianValue();
	}

	template < typename ScalarType > Radian_tpl<ScalarType> Degree_tpl<ScalarType>::ToRad( void ) const
	{
		return MathHelper_tpl<ScalarType>::DegreeToRad( *this );
	}

	template < typename ScalarType > ScalarType Degree_tpl<ScalarType>::AsDegreeValue( void ) const
	{
		return m_Degree;
	}

	template < typename ScalarType > 
	Degree_tpl<ScalarType> Degree_tpl<ScalarType>::operator+( const Degree_tpl<ScalarType>& deg ) const
	{
		return Degree_tpl<ScalarType>( m_Degree + deg.m_Degree );
	}

	template < typename ScalarType > 
	Degree_tpl<ScalarType> &Degree_tpl<ScalarType>::operator+=( const Degree_tpl<ScalarType>& deg )
	{
		m_Degree += deg.m_Degree;

		return *this;
	}

	template < typename ScalarType > 
	Degree_tpl<ScalarType> Degree_tpl<ScalarType>::operator-( const Degree_tpl<ScalarType>& deg ) const
	{
		return Degree_tpl<ScalarType>( m_Degree - deg.m_Degree );
	}

	template < typename ScalarType > 
	Degree_tpl<ScalarType> &Degree_tpl<ScalarType>::operator-=( const Degree_tpl<ScalarType>& deg )
	{
		m_Degree -= deg.m_Degree;

		return *this;
	}

	template < typename ScalarType > 
	Degree_tpl<ScalarType> Degree_tpl<ScalarType>::operator*( const ScalarType& scalar ) const
	{
		return Degree_tpl<ScalarType>( m_Degree * scalar );
	}

	template < typename ScalarType > 
	Degree_tpl<ScalarType> &Degree_tpl<ScalarType>::operator*=( const ScalarType& scalar )
	{
		m_Degree *= scalar;

		return *this;
	}

	template < typename ScalarType > 
	Degree_tpl<ScalarType> Degree_tpl<ScalarType>::operator/( const ScalarType& scalar ) const
	{
		return Degree_tpl<ScalarType>( m_Degree / scalar );
	}

	template < typename ScalarType >
	Degree_tpl<ScalarType> &Degree_tpl<ScalarType>::operator/=( const ScalarType& scalar )
	{
		m_Degree /= scalar;

		return *this;
	}

	template < typename ScalarType > bool Degree_tpl<ScalarType>::operator==( const Degree_tpl<ScalarType>& deg ) const
	{
		return m_Degree == deg.m_Degree;
	}

	template < typename ScalarType > bool Degree_tpl<ScalarType>::operator!=( const Degree_tpl<ScalarType>& deg ) const
	{

		return m_Degree != deg.m_Degree;
	}

	template < typename ScalarType > bool Degree_tpl<ScalarType>::operator>=( const Degree_tpl<ScalarType>& deg ) const
	{

		return m_Degree >= deg.m_Degree;
	}

	template < typename ScalarType > bool Degree_tpl<ScalarType>::operator<=( const Degree_tpl<ScalarType>& deg ) const
	{

		return m_Degree <= deg.m_Degree;
	}

	template < typename ScalarType > bool Degree_tpl<ScalarType>::operator>( const Degree_tpl<ScalarType>& deg ) const
	{

		return m_Degree > deg.m_Degree;
	}

	template < typename ScalarType > bool Degree_tpl<ScalarType>::operator<( const Degree_tpl<ScalarType>& deg ) const
	{

		return m_Degree < deg.m_Degree;
	}

}
