#pragma once
#ifndef Interpolator_h__
  #define Interpolator_h__

  #include "../../LinearMath/MathHelper.hpp"

namespace Analysis
{
  /**
  \brief The Interpolator offers some simple interpolation where no additional Data than
  the start and endpoint and the position of the interpolation is required.

  */
  template< typename T, typename ScalarType >
  class Interpolator_tpl
  {
  public:

    /**
    \brief Performs a Linear Interpolation between start and end
    and returns the value at point x

    If \c x is between 0.0 and 1.0 the returning value will be in between start and end

    \param start The start value for the interpolation
    \param end The endpoint for the interpolation
    \param x The interpolation value

    \return The interpolated value
    */
    static T Lerp( const T& start, const T& end, const ScalarType& x );

    /**
    \brief Performs a "Smooth" Interpolation between start and end and returns the interpolated position at x

    This interpolation is intended to work at values in between 0.0 and 1.0
    It will start at start value when \c x is 0.0 and then slowly go towards end at increasing speed
    For this interpolation a transformed cosine is used.

    \param start The start value for the interpolation
    \param end The end value for the interpolation
    \param x The interpolation value

    \return The interpolated value
    */
    static T SmoothInterpolation( const T& start, const T& end, const ScalarType& x );

    /**
    \brief This is a modified version of the SmoothInterpolation.
    The modification is that it will start fast and decrease speed as it reaches 1.0

    \param start The start value for the interpolation
    \param end The end value for the interpolation
    \param x The interpolation value

    \return The interpolated value
    */
    static T SmoothStopInterpolation( const T& start, const T& end, const ScalarType& x );

  protected:

  private:

    Interpolator_tpl()
    {
    }
    Interpolator_tpl& operator =( const Interpolator_tpl& )
    {
      return *this;
    }
  };

  template< typename T, typename ScalarType >
  T Analysis::Interpolator_tpl< T, ScalarType >::SmoothStopInterpolation( const T& start,
    const T& end,
    const ScalarType& x )
  {
    return start
         + ( ( end - start )
         * ( ( ( ScalarType ) - 1.0 )
         * LinearMath::MathHelper_tpl< ScalarType >::Cos( LinearMath::Radian_tpl< ScalarType >(
         ( LinearMath::MathHelper_tpl< ScalarType >::PI / ( ScalarType )2.0 ) * x
         + ( ( ScalarType )0.5 * LinearMath::MathHelper_tpl< ScalarType >::PI ) ) ) ) );
  }

  template< typename T, typename ScalarType >
  T Analysis::Interpolator_tpl< T, ScalarType >::SmoothInterpolation( const T& start, const T& end,
    const ScalarType& x )
  {
    return start
         + ( ( end - start )
         * ( ( ( ScalarType ) - 0.5 )
         * LinearMath::MathHelper_tpl< ScalarType >::Cos( LinearMath::Radian_tpl< ScalarType >( LinearMath::
         MathHelper_tpl< ScalarType >::PI * x ) )
         + ( ScalarType )0.5 ) );
  }

  template< typename T, typename ScalarType >
  T Analysis::Interpolator_tpl< T, ScalarType >::Lerp( const T& start, const T& end, const ScalarType& x )
  {
    return start + ( end - start ) * x;
  }
}

#endif  // Interpolator_h__
