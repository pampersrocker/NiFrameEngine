#pragma once
#ifndef _MP_MATRIX_4_4_H_
	#define _MP_MATRIX_4_4_H_

	#include "MathLibPCH.h"
	#include "Vector3.h"
	#include "Vector2.h"
	#include "MathHelper.h"

namespace LinearMath
{
	/**
	\brief Describes a 4 times 4 Matrix with column-major order
	*/
	template< typename ScalarType >
	class Matrix4x4_tpl
	{
	public:

		/**
		\brief Creates an Identity Matrix

		| 1 | 0 | 0 | 0 |
		| 0 | 1 | 0 | 0 |
		| 0 | 0 | 1 | 0 |
		| 0 | 0 | 0 | 1 |

		*/
		static const Matrix4x4_tpl< ScalarType > IDENTITY;

		static const Matrix4x4_tpl< ScalarType > ZERO;

		static const Matrix4x4_tpl< ScalarType > ZERO_AFFINE;

		/**
		\brief Creates an uninitialized Matrix

		*/
		Matrix4x4_tpl();

		/**
		\brief Creates an User Defined Matrix

		Layout:
		| 1_1 | 1_2 | 1_3 | 1_4 |
		| 2_1 | 2_2 | 2_3 | 2_4 |
		| 3_1 | 3_2 | 3_3 | 3_4 |
		| 4_1 | 4_2 | 4_3 | 4_4 |

		*/
		Matrix4x4_tpl(
			const ScalarType& m_1_1, const ScalarType& m_1_2, const ScalarType& m_1_3, const ScalarType& m_1_4,
			const ScalarType& m_2_1, const ScalarType& m_2_2, const ScalarType& m_2_3, const ScalarType& m_2_4,
			const ScalarType& m_3_1, const ScalarType& m_3_2, const ScalarType& m_3_3, const ScalarType& m_3_4,
			const ScalarType& m_4_1, const ScalarType& m_4_2, const ScalarType& m_4_3, const ScalarType& m_4_4
		);

		Matrix4x4_tpl operator +( const Matrix4x4_tpl& mat ) const;

		Matrix4x4_tpl& operator +=( const Matrix4x4_tpl& mat );

		Matrix4x4_tpl operator -( const Matrix4x4_tpl& mat ) const;

		Matrix4x4_tpl& operator -=( const Matrix4x4_tpl& mat );

		Matrix4x4_tpl operator *( const ScalarType& op ) const;

		inline friend Matrix4x4_tpl< ScalarType >
		operator *( const ScalarType& scalar, const Matrix4x4_tpl< ScalarType >& mat )
		{
			return mat * scalar;
		}
		Matrix4x4_tpl operator *( const Matrix4x4_tpl< ScalarType >& matrix ) const;

		Vector3_tpl< ScalarType > operator *( const Vector3_tpl< ScalarType >& vec ) const;

		/**
		\brief Multiplies a Vector2 with the matrix.

		\param vec The vector which will be transformed by the matrix.
		The Vector will be treated as a Vector4 with (X,Y,0,1)

		\return Vector2_tpl< ScalarType > The transformed Vector
		 */
		Vector2_tpl< ScalarType > operator *( const Vector2_tpl< ScalarType >& vec ) const;

		Matrix4x4_tpl& operator *=( const Matrix4x4_tpl< ScalarType >& matrix );

		static Matrix4x4_tpl CreateScaleMatrix(
			const ScalarType& scaleX, const ScalarType& scaleY, const ScalarType& scaleZ );

		static Matrix4x4_tpl CreateScaleMatrix(
			const Vector3_tpl< ScalarType >& scale );

		static Matrix4x4_tpl CreateTranslationMatrix( const ScalarType& X, const ScalarType& Y, const ScalarType& Z );

		static Matrix4x4_tpl CreateTranslationMatrix( const Vector3_tpl< ScalarType >& translation );

		static Matrix4x4_tpl CreateRotationXAxisMatrix( const Radian_tpl< ScalarType >& rad );

		static Matrix4x4_tpl CreateRotationXAxisMatrix( const Degree_tpl< ScalarType >& deg );

		static Matrix4x4_tpl CreateRotationYAxisMatrix( const Radian_tpl< ScalarType >& rad );

		static Matrix4x4_tpl CreateRotationYAxisMatrix( const Degree_tpl< ScalarType >& deg );

		static Matrix4x4_tpl CreateRotationZAxisMatrix( const Radian_tpl< ScalarType >& rad );

		static Matrix4x4_tpl CreateRotationZAxisMatrix( const Degree_tpl< ScalarType >& deg );

		Matrix4x4_tpl< ScalarType > InvertedCopy();

		~Matrix4x4_tpl();

		// Fields

		/*
		Indexed as follows
		| 1_1 | 1_2 | 1_3 | 1_4 |
		| 2_1 | 2_2 | 2_3 | 2_4 |
		| 3_1 | 3_2 | 3_3 | 3_4 |
		| 4_1 | 4_2 | 4_3 | 4_4 |
		*/
		ScalarType M_1_1, M_1_2, M_1_3, M_1_4;
		ScalarType M_2_1, M_2_2, M_2_3, M_2_4;
		ScalarType M_3_1, M_3_2, M_3_3, M_3_4;
		ScalarType M_4_1, M_4_2, M_4_3, M_4_4;

	private:
	};

	template< typename ScalarType >
	Matrix4x4_tpl< ScalarType >
	LinearMath::Matrix4x4_tpl< ScalarType >::CreateRotationXAxisMatrix( const Degree_tpl< ScalarType >& deg )
	{
		return CreateRotationXAxisMatrix( deg.ToRad() );
	}

	template< typename ScalarType >
	Matrix4x4_tpl< ScalarType >
	LinearMath::Matrix4x4_tpl< ScalarType >::CreateRotationXAxisMatrix( const Radian_tpl< ScalarType >& rad )
	{
		ScalarType sin = MathHelper_tpl< ScalarType >::Sin( rad.AsRadianValue() );
		ScalarType cos = MathHelper_tpl< ScalarType >::Cos( rad.AsRadianValue() );

		return Matrix4x4_tpl< ScalarType >
			   (
			1, 0, 0, 0,
			0, cos, -sin, 0,
			0, sin, cos, 0,
			0, 0, 0, 1
			   );
	}

	template< typename ScalarType >
	Matrix4x4_tpl< ScalarType >
	LinearMath::Matrix4x4_tpl< ScalarType >::CreateRotationYAxisMatrix( const Degree_tpl< ScalarType >& deg )
	{
		return CreateRotationYAxisMatrix( deg.ToRad() );
	}

	template< typename ScalarType >
	Matrix4x4_tpl< ScalarType >
	LinearMath::Matrix4x4_tpl< ScalarType >::CreateRotationYAxisMatrix( const Radian_tpl< ScalarType >& rad )
	{
		ScalarType sin = MathHelper_tpl< ScalarType >::Sin( rad.AsRadianValue() );
		ScalarType cos = MathHelper_tpl< ScalarType >::Cos( rad.AsRadianValue() );

		return Matrix4x4_tpl< ScalarType >
			   (
			cos, 0, sin, 0,
			0, 1, 0, 0,
			-sin, 0, cos, 0,
			0, 0, 0, 1
			   );
	}

	template< typename ScalarType >
	Matrix4x4_tpl< ScalarType >
	LinearMath::Matrix4x4_tpl< ScalarType >::CreateRotationZAxisMatrix( const Degree_tpl< ScalarType >& deg )
	{
		return CreateRotationZAxisMatrix( deg.ToRad() );
	}

	template< typename ScalarType >
	Matrix4x4_tpl< ScalarType >
	LinearMath::Matrix4x4_tpl< ScalarType >::CreateRotationZAxisMatrix( const Radian_tpl< ScalarType >& rad )
	{
		ScalarType sin = MathHelper_tpl< ScalarType >::Sin( rad.AsRadianValue() );
		ScalarType cos = MathHelper_tpl< ScalarType >::Cos( rad.AsRadianValue() );

		return Matrix4x4_tpl< ScalarType >
			   (
			cos, -sin, 0, 0,
			sin, cos, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1
			   );
	}

	template< typename ScalarType >
	Matrix4x4_tpl< ScalarType >& LinearMath::Matrix4x4_tpl< ScalarType >::operator +=( const Matrix4x4_tpl& mat )
	{
		M_1_1 += mat.M_1_1;
		M_1_2 += mat.M_1_2;
		M_1_3 += mat.M_1_3;
		M_1_4 += mat.M_1_4;

		M_2_1 += mat.M_2_1;
		M_2_2 += mat.M_2_2;
		M_2_3 += mat.M_2_3;
		M_2_4 += mat.M_2_4;

		M_3_1 += mat.M_3_1;
		M_3_2 += mat.M_3_2;
		M_3_3 += mat.M_3_3;
		M_3_4 += mat.M_3_4;

		M_4_1 += mat.M_4_1;
		M_4_2 += mat.M_4_2;
		M_4_3 += mat.M_4_3;
		M_4_4 += mat.M_4_4;

		return *this;
	}

	template< typename ScalarType >
	Matrix4x4_tpl< ScalarType > LinearMath::Matrix4x4_tpl< ScalarType >::operator +( const Matrix4x4_tpl& mat ) const
	{
		return Matrix4x4_tpl< ScalarType >( *this ) += mat;
	}

	template< typename ScalarType >
	Matrix4x4_tpl< ScalarType >& LinearMath::Matrix4x4_tpl< ScalarType >::operator -=( const Matrix4x4_tpl& mat )
	{
		M_1_1 -= mat.M_1_1;
		M_1_2 -= mat.M_1_2;
		M_1_3 -= mat.M_1_3;
		M_1_4 -= mat.M_1_4;

		M_2_1 -= mat.M_2_1;
		M_2_2 -= mat.M_2_2;
		M_2_3 -= mat.M_2_3;
		M_2_4 -= mat.M_2_4;

		M_3_1 -= mat.M_3_1;
		M_3_2 -= mat.M_3_2;
		M_3_3 -= mat.M_3_3;
		M_3_4 -= mat.M_3_4;

		M_4_1 -= mat.M_4_1;
		M_4_2 -= mat.M_4_2;
		M_4_3 -= mat.M_4_3;
		M_4_4 -= mat.M_4_4;

		return *this;
	}

	template< typename ScalarType >
	Matrix4x4_tpl< ScalarType > LinearMath::Matrix4x4_tpl< ScalarType >::operator -( const Matrix4x4_tpl& mat ) const
	{
		return Matrix4x4_tpl< ScalarType >( *this ) -= mat;
	}

	template< typename ScalarType >
	const Matrix4x4_tpl< ScalarType > LinearMath::Matrix4x4_tpl< ScalarType >::ZERO_AFFINE
	(
	0, 0, 0, 0,
	0, 0, 0, 0,
	0, 0, 0, 0,
	0, 0, 0, 1
	);

	template< typename ScalarType >
	const Matrix4x4_tpl< ScalarType > LinearMath::Matrix4x4_tpl< ScalarType >::ZERO
	(
	0, 0, 0, 0,
	0, 0, 0, 0,
	0, 0, 0, 0,
	0, 0, 0, 0
	);

	template< typename ScalarType >
	const Matrix4x4_tpl< ScalarType > LinearMath::Matrix4x4_tpl< ScalarType >::IDENTITY
	(
	1, 0, 0, 0,
	0, 1, 0, 0,
	0, 0, 1, 0,
	0, 0, 0, 1
	);

	template< typename ScalarType >
	Vector2_tpl< ScalarType > Matrix4x4_tpl< ScalarType >::operator *( const Vector2_tpl< ScalarType >& vec ) const
	{
		return Vector2_tpl< ScalarType >
			   (
			vec.X * M_1_1 + vec.Y * M_1_2 + M_1_4,
			vec.Y * M_2_1 + vec.Y * M_2_2 + M_2_4
			   );
	}

	template< typename ScalarType >
	Vector3_tpl< ScalarType > Matrix4x4_tpl< ScalarType >::operator *( const Vector3_tpl< ScalarType >& vec ) const
	{
		return Vector3_tpl< ScalarType >
			   (
			vec.X * M_1_1 + vec.Y * M_1_2 * vec.Z * M_1_3 + M_1_4,
			vec.X * M_2_1 + vec.Y * M_2_2 * vec.Z * M_2_3 + M_2_4,
			vec.X * M_3_1 + vec.Y * M_3_2 * vec.Z * M_3_3 + M_3_4
			   );
	}

	template< typename ScalarType >
	Matrix4x4_tpl< ScalarType > Matrix4x4_tpl< ScalarType >::operator *( const ScalarType& op ) const
	{
		return Matrix4x4_tpl< ScalarType >
			   (
			op * M_1_1, op * M_1_2, op * M_1_3, op * M_1_4,
			op * M_2_1, op * M_2_2, op * M_2_3, op * M_2_4,
			op * M_3_1, op * M_3_2, op * M_3_3, op * M_3_4,
			op * M_4_1, op * M_4_2, op * M_4_3, op * M_4_4
			   );
	}

	template< typename ScalarType >
	Matrix4x4_tpl< ScalarType > Matrix4x4_tpl< ScalarType >::InvertedCopy()
	{
		ScalarType
			tmpM_1_1 = M_1_1, tmpM_1_2 = M_1_2, tmpM_1_3 = M_1_3, tmpM_1_4 = M_1_4,
			tmpM_2_1 = M_2_1, tmpM_2_2 = M_2_2, tmpM_2_3 = M_2_3, tmpM_2_4 = M_2_4,
			tmpM_3_1 = M_3_1, tmpM_3_2 = M_3_2, tmpM_3_3 = M_3_3, tmpM_3_4 = M_3_4,
			tmpM_4_1 = M_4_1, tmpM_4_2 = M_4_2, tmpM_4_3 = M_4_3, tmpM_4_4 = M_4_4;

		ScalarType
			tmp1 = tmpM_3_1 * tmpM_4_2 - tmpM_3_2 * tmpM_4_1,
			tmp2 = tmpM_3_1 * tmpM_4_3 - tmpM_3_3 * tmpM_4_1,
			tmp3 = tmpM_3_1 * tmpM_4_4 - tmpM_3_4 * tmpM_4_1,
			tmp4 = tmpM_3_2 * tmpM_4_3 - tmpM_3_3 * tmpM_4_2,
			tmp5 = tmpM_3_2 * tmpM_4_4 - tmpM_3_4 * tmpM_4_2,
			tmp6 = tmpM_3_3 * tmpM_4_4 - tmpM_3_4 * tmpM_4_3;

		ScalarType
			t_1_1 = +( tmp6 * tmpM_2_2 - tmp5 * tmpM_2_3 + tmp4 * tmpM_2_4 ),
			t_2_1 = -( tmp6 * tmpM_2_1 - tmp3 * tmpM_2_3 + tmp2 * tmpM_2_4 ),
			t_3_1 = +( tmp5 * tmpM_2_1 - tmp3 * tmpM_2_2 + tmp1 * tmpM_2_4 ),
			t_4_1 = -( tmp4 * tmpM_2_1 - tmp2 * tmpM_2_2 + tmp1 * tmpM_2_3 );

		ScalarType inverseDet = 1 / ( t_1_1 * tmpM_1_1 + t_2_1 * tmpM_1_2 + t_3_1 * tmpM_1_3 + t_4_1 * tmpM_1_4 );

		ScalarType
			d_1_1 = t_1_1 * inverseDet,
			d_2_1 = t_2_1 * inverseDet,
			d_3_1 = t_3_1 * inverseDet,
			d_4_1 = t_4_1 * inverseDet;

		ScalarType
			d_1_2 = -( tmp6 * tmpM_1_2 - tmp5 * tmpM_1_3 + tmp4 * tmpM_1_4 ) * inverseDet,
			d_2_2 = +( tmp6 * tmpM_1_1 - tmp3 * tmpM_1_3 + tmp2 * tmpM_1_4 ) * inverseDet,
			d_3_2 = -( tmp5 * tmpM_1_1 - tmp3 * tmpM_1_2 + tmp1 * tmpM_1_4 ) * inverseDet,
			d_4_2 = +( tmp4 * tmpM_1_1 - tmp2 * tmpM_1_2 + tmp1 * tmpM_1_3 ) * inverseDet;

		tmp1 = tmpM_2_1 * tmpM_4_2 - tmpM_2_2 * tmpM_4_1;
		tmp2 = tmpM_2_1 * tmpM_4_3 - tmpM_2_3 * tmpM_4_1;
		tmp3 = tmpM_2_1 * tmpM_4_4 - tmpM_2_4 * tmpM_4_1;
		tmp4 = tmpM_2_2 * tmpM_4_3 - tmpM_2_3 * tmpM_4_2;
		tmp5 = tmpM_2_2 * tmpM_4_4 - tmpM_2_4 * tmpM_4_2;
		tmp6 = tmpM_2_3 * tmpM_4_4 - tmpM_2_4 * tmpM_4_3;

		ScalarType
			d_1_3 = +( tmp6 * tmpM_1_2 - tmp5 * tmpM_1_3 + tmp4 * tmpM_1_4 ) * inverseDet,
			d_2_3 = -( tmp6 * tmpM_1_1 - tmp3 * tmpM_1_3 + tmp2 * tmpM_1_4 ) * inverseDet,
			d_3_3 = +( tmp5 * tmpM_1_1 - tmp3 * tmpM_1_2 + tmp1 * tmpM_1_4 ) * inverseDet,
			d_4_3 = -( tmp4 * tmpM_1_1 - tmp2 * tmpM_1_2 + tmp1 * tmpM_1_3 ) * inverseDet;

		tmp1 = tmpM_3_2 * tmpM_2_1 - tmpM_3_1 * tmpM_2_2;
		tmp2 = tmpM_3_3 * tmpM_2_1 - tmpM_3_1 * tmpM_2_3;
		tmp3 = tmpM_3_4 * tmpM_2_1 - tmpM_3_1 * tmpM_2_4;
		tmp4 = tmpM_3_3 * tmpM_2_2 - tmpM_3_2 * tmpM_2_3;
		tmp5 = tmpM_3_4 * tmpM_2_2 - tmpM_3_2 * tmpM_2_4;
		tmp6 = tmpM_3_4 * tmpM_2_3 - tmpM_3_3 * tmpM_2_4;

		ScalarType
			d_1_4 = -( tmp6 * tmpM_1_2 - tmp5 * tmpM_1_3 + tmp4 * tmpM_1_4 ) * inverseDet,
			d_2_4 = +( tmp6 * tmpM_1_1 - tmp3 * tmpM_1_3 + tmp2 * tmpM_1_4 ) * inverseDet,
			d_3_4 = -( tmp5 * tmpM_1_1 - tmp3 * tmpM_1_2 + tmp1 * tmpM_1_4 ) * inverseDet,
			d_4_4 = +( tmp4 * tmpM_1_1 - tmp2 * tmpM_1_2 + tmp1 * tmpM_1_3 ) * inverseDet;

		return Matrix4x4_tpl< ScalarType >(
			d_1_1, d_1_2, d_1_3, d_1_4,
			d_2_1, d_2_2, d_2_3, d_2_4,
			d_3_1, d_3_2, d_3_3, d_3_4,
			d_4_1, d_4_2, d_4_3, d_4_4
		);
	}

	template< typename ScalarType >
	Matrix4x4_tpl< ScalarType >& Matrix4x4_tpl< ScalarType >::operator *=( const Matrix4x4_tpl< ScalarType >& op )
	{
		// Need temp Values because otherwise the calculations are going to be incorrect
		ScalarType
			tmpM_1_1, tmpM_1_2, tmpM_1_3, tmpM_1_4,
			tmpM_2_1, tmpM_2_2, tmpM_2_3, tmpM_2_4,
			tmpM_3_1, tmpM_3_2, tmpM_3_3, tmpM_3_4,
			tmpM_4_1, tmpM_4_2, tmpM_4_3, tmpM_4_4;

		tmpM_1_1 = ( ( M_1_1 * op.M_1_1 ) + ( M_1_2 * op.M_2_1 ) + ( M_1_3 * op.M_3_1 ) + ( M_1_4 * op.M_4_1 ) );
		tmpM_1_2 = ( ( M_1_1 * op.M_1_2 ) + ( M_1_2 * op.M_2_2 ) + ( M_1_3 * op.M_3_2 ) + ( M_1_4 * op.M_4_2 ) );
		tmpM_1_3 = ( ( M_1_1 * op.M_1_3 ) + ( M_1_2 * op.M_2_3 ) + ( M_1_3 * op.M_3_3 ) + ( M_1_4 * op.M_4_3 ) );
		tmpM_1_4 = ( ( M_1_1 * op.M_1_4 ) + ( M_1_2 * op.M_2_4 ) + ( M_1_3 * op.M_3_4 ) + ( M_1_4 * op.M_4_4 ) );

		tmpM_2_1 = ( ( M_2_1 * op.M_1_1 ) + ( M_2_2 * op.M_2_1 ) + ( M_2_3 * op.M_3_1 ) + ( M_2_4 * op.M_4_1 ) );
		tmpM_2_2 = ( ( M_2_1 * op.M_1_2 ) + ( M_2_2 * op.M_2_2 ) + ( M_2_3 * op.M_3_2 ) + ( M_2_4 * op.M_4_2 ) );
		tmpM_2_3 = ( ( M_2_1 * op.M_1_3 ) + ( M_2_2 * op.M_2_3 ) + ( M_2_3 * op.M_3_3 ) + ( M_2_4 * op.M_4_3 ) );
		tmpM_2_4 = ( ( M_2_1 * op.M_1_4 ) + ( M_2_2 * op.M_2_4 ) + ( M_2_3 * op.M_3_4 ) + ( M_2_4 * op.M_4_4 ) );

		tmpM_3_1 = ( ( M_3_1 * op.M_1_1 ) + ( M_3_2 * op.M_2_1 ) + ( M_3_3 * op.M_3_1 ) + ( M_3_4 * op.M_4_1 ) );
		tmpM_3_2 = ( ( M_3_1 * op.M_1_2 ) + ( M_3_2 * op.M_2_2 ) + ( M_3_3 * op.M_3_2 ) + ( M_3_4 * op.M_4_2 ) );
		tmpM_3_3 = ( ( M_3_1 * op.M_1_3 ) + ( M_3_2 * op.M_2_3 ) + ( M_3_3 * op.M_3_3 ) + ( M_3_4 * op.M_4_3 ) );
		tmpM_3_4 = ( ( M_3_1 * op.M_1_4 ) + ( M_3_2 * op.M_2_4 ) + ( M_3_3 * op.M_3_4 ) + ( M_3_4 * op.M_4_4 ) );

		tmpM_4_1 = ( ( M_4_1 * op.M_1_1 ) + ( M_4_2 * op.M_2_1 ) + ( M_4_3 * op.M_3_1 ) + ( M_4_4 * op.M_4_1 ) );
		tmpM_4_2 = ( ( M_4_1 * op.M_1_2 ) + ( M_4_2 * op.M_2_2 ) + ( M_4_3 * op.M_3_2 ) + ( M_4_4 * op.M_4_2 ) );
		tmpM_4_3 = ( ( M_4_1 * op.M_1_3 ) + ( M_4_2 * op.M_2_3 ) + ( M_4_3 * op.M_3_3 ) + ( M_4_4 * op.M_4_3 ) );
		tmpM_4_4 = ( ( M_4_1 * op.M_1_4 ) + ( M_4_2 * op.M_2_4 ) + ( M_4_3 * op.M_3_4 ) + ( M_4_4 * op.M_4_4 ) );

		M_1_1 = tmpM_1_1;
		M_1_2 = tmpM_1_2;
		M_1_3 = tmpM_1_3;
		M_1_4 = tmpM_1_4;

		M_2_1 = tmpM_2_1;
		M_2_2 = tmpM_2_2;
		M_2_3 = tmpM_2_3;
		M_2_4 = tmpM_2_4;

		M_3_1 = tmpM_3_1;
		M_3_2 = tmpM_3_2;
		M_3_3 = tmpM_3_3;
		M_3_4 = tmpM_3_4;

		M_4_1 = tmpM_4_1;
		M_4_2 = tmpM_4_2;
		M_4_3 = tmpM_4_3;
		M_4_4 = tmpM_4_4;

		return *this;
	}

	template< typename ScalarType >
	Matrix4x4_tpl< ScalarType > Matrix4x4_tpl< ScalarType >::operator *( const Matrix4x4_tpl& op ) const
	{
		return Matrix4x4_tpl< ScalarType >
			   (
			( ( M_1_1 * op.M_1_1 ) + ( M_1_2 * op.M_2_1 ) + ( M_1_3 * op.M_3_1 ) + ( M_1_4 * op.M_4_1 ) ),
			( ( M_1_1 * op.M_1_2 ) + ( M_1_2 * op.M_2_2 ) + ( M_1_3 * op.M_3_2 ) + ( M_1_4 * op.M_4_2 ) ),
			( ( M_1_1 * op.M_1_3 ) + ( M_1_2 * op.M_2_3 ) + ( M_1_3 * op.M_3_3 ) + ( M_1_4 * op.M_4_3 ) ),
			( ( M_1_1 * op.M_1_4 ) + ( M_1_2 * op.M_2_4 ) + ( M_1_3 * op.M_3_4 ) + ( M_1_4 * op.M_4_4 ) ),

			( ( M_2_1 * op.M_1_1 ) + ( M_2_2 * op.M_2_1 ) + ( M_2_3 * op.M_3_1 ) + ( M_2_4 * op.M_4_1 ) ),
			( ( M_2_1 * op.M_1_2 ) + ( M_2_2 * op.M_2_2 ) + ( M_2_3 * op.M_3_2 ) + ( M_2_4 * op.M_4_2 ) ),
			( ( M_2_1 * op.M_1_3 ) + ( M_2_2 * op.M_2_3 ) + ( M_2_3 * op.M_3_3 ) + ( M_2_4 * op.M_4_3 ) ),
			( ( M_2_1 * op.M_1_4 ) + ( M_2_2 * op.M_2_4 ) + ( M_2_3 * op.M_3_4 ) + ( M_2_4 * op.M_4_4 ) ),

			( ( M_3_1 * op.M_1_1 ) + ( M_3_2 * op.M_2_1 ) + ( M_3_3 * op.M_3_1 ) + ( M_3_4 * op.M_4_1 ) ),
			( ( M_3_1 * op.M_1_2 ) + ( M_3_2 * op.M_2_2 ) + ( M_3_3 * op.M_3_2 ) + ( M_3_4 * op.M_4_2 ) ),
			( ( M_3_1 * op.M_1_3 ) + ( M_3_2 * op.M_2_3 ) + ( M_3_3 * op.M_3_3 ) + ( M_3_4 * op.M_4_3 ) ),
			( ( M_3_1 * op.M_1_4 ) + ( M_3_2 * op.M_2_4 ) + ( M_3_3 * op.M_3_4 ) + ( M_3_4 * op.M_4_4 ) ),

			( ( M_4_1 * op.M_1_1 ) + ( M_4_2 * op.M_2_1 ) + ( M_4_3 * op.M_3_1 ) + ( M_4_4 * op.M_4_1 ) ),
			( ( M_4_1 * op.M_1_2 ) + ( M_4_2 * op.M_2_2 ) + ( M_4_3 * op.M_3_2 ) + ( M_4_4 * op.M_4_2 ) ),
			( ( M_4_1 * op.M_1_3 ) + ( M_4_2 * op.M_2_3 ) + ( M_4_3 * op.M_3_3 ) + ( M_4_4 * op.M_4_3 ) ),
			( ( M_4_1 * op.M_1_4 ) + ( M_4_2 * op.M_2_4 ) + ( M_4_3 * op.M_3_4 ) + ( M_4_4 * op.M_4_4 ) )
			   );
	}

	template< typename ScalarType >
	Matrix4x4_tpl< ScalarType > Matrix4x4_tpl< ScalarType >::CreateTranslationMatrix(
		const ScalarType& X, const ScalarType& Y, const ScalarType& Z )
	{
		return Matrix4x4_tpl(
			1, 0, 0, X,
			0, 1, 0, Y,
			0, 0, 1, Z,
			0, 0, 0, 1
		);
	}

	template< typename ScalarType >
	Matrix4x4_tpl< ScalarType > LinearMath::Matrix4x4_tpl< ScalarType >::CreateTranslationMatrix(
		const Vector3_tpl< ScalarType >& translation )
	{
		return CreateTranslationMatrix( translation.GetX(), translation.GetY(), translation.GetZ() );
	}

	template< typename ScalarType >
	Matrix4x4_tpl< ScalarType >::Matrix4x4_tpl(
		const ScalarType& m_1_1, const ScalarType& m_1_2, const ScalarType& m_1_3, const ScalarType& m_1_4,
		const ScalarType& m_2_1, const ScalarType& m_2_2, const ScalarType& m_2_3, const ScalarType& m_2_4,
		const ScalarType& m_3_1, const ScalarType& m_3_2, const ScalarType& m_3_3, const ScalarType& m_3_4,
		const ScalarType& m_4_1, const ScalarType& m_4_2, const ScalarType& m_4_3, const ScalarType& m_4_4
	) :
		M_1_1( m_1_1 ),
		M_1_2( m_1_2 ),
		M_1_3( m_1_3 ),
		M_1_4( m_1_4 ),
		M_2_1( m_2_1 ),
		M_2_2( m_2_2 ),
		M_2_3( m_2_3 ),
		M_2_4( m_2_4 ),
		M_3_1( m_3_1 ),
		M_3_2( m_3_2 ),
		M_3_3( m_3_3 ),
		M_3_4( m_3_4 ),
		M_4_1( m_4_1 ),
		M_4_2( m_4_2 ),
		M_4_3( m_4_3 ),
		M_4_4( m_4_4 )
	{
	}

	template< typename ScalarType >
	Matrix4x4_tpl< ScalarType >::~Matrix4x4_tpl()
	{
	}

	template< typename ScalarType >
	Matrix4x4_tpl< ScalarType >::Matrix4x4_tpl()
	{
	}

	template< typename ScalarType >
	Matrix4x4_tpl< ScalarType > Matrix4x4_tpl< ScalarType >::CreateScaleMatrix(
		const ScalarType& sX, const ScalarType& sY, const ScalarType& sZ )
	{
		return Matrix4x4_tpl(
			sX, 0, 0, 0,
			0, sY, 0, 0,
			0, 0, sZ, 0,
			0, 0, 0, 1
		);
	}

	template< typename ScalarType >
	Matrix4x4_tpl< ScalarType > Matrix4x4_tpl< ScalarType >::CreateScaleMatrix( const Vector3_tpl< ScalarType >& scale )
	{
		return CreateScaleMatrix( scale.X, scale.Y, scale.Z );
	}
}

#endif // ifndef _MP_MATRIX_4_4_H_
