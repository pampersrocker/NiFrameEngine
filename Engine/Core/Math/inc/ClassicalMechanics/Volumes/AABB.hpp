#pragma once
#ifndef AABB_h__
  #define AABB_h__

  #include "../../LinearMath/MathHelper.hpp"

namespace ClassicalMechanics
{
  namespace Volumes
  {
    /**
    \brief Template which stores an Axis Aligned Bounding Box (AABB) in Arbitrary dimension.

    \remark the Template Parameter Vec must have following attributes:
    - An array named \c data where the Scalars are stored
    - A static const Numerics::uint32 \c size definition with the dimension of Vector
    - A typedef \c DataType with the type of the Scalar

    The LinearMath::Vector3_tpl and LinearMath::Vector2_tpl matches those specifications

    \since 1.0
    */
    template< typename Vec >
    class AABB_tpl
    {
    public:

      typedef Vec DataType;
      typedef typename Vec::DataType Scalar;
      static const Numerics::uint32 vec_size = Vec::size;

      /**
      \brief Creates a new AABB_tpl spanning from min to max

      \param min The minimum position of the Bounding Box
      \param max The maximum position of the Bounding Box

      \remark The minimum and maximum may be interchangeable.
      The bounding box itself checks if the minimum is the absolute minimum and vice versa.

      \since 1.0
      */
      AABB_tpl(
        const Vec& min,
        const Vec& max );

      AABB_tpl();

      /**
      \brief Copy constructor for the AABB_tpl. Copies the minimum and maximum vectors.

      \param aabb The AABB which will be copied.

      \since 1.0
      */
      AABB_tpl( const AABB_tpl& aabb );

      /**
      \brief Sets the new minimum of the AABB.


      \param min The AABB checks if the new minimum is still smaller than the current maximum
      and switches the components of the vectors accordingly.

      \since 1.0
      */
      void Min( const Vec& min );

      /**
      \brief Sets the new maximum of the AABB.


      \param min The AABB checks if the new maximum is still bigger than the current minimum
      and switches the components of the vectors accordingly.

      \since 1.0
      */
      void Max( const Vec& max );

      /**
      \brief Returns the current minimum of the AABB.

      \return The current minimum of the AABB as Vector3

      \since 1.0
      */
      const Vec& Min( void ) const;

      /**
      \brief Returns the current maximum of the AABB.

      \return The current maximum of the AABB as Vec

      \since 1.0
      */
      const Vec& Max( void ) const;

      /**
      \brief Stores the Bounding vertices of te AABB into the given array.

      \param data A Vec pointer which needs to have a size of at least 2^(Dimension Of Vector).

      \remark The data pointer needs to have a size of at least 2^(Dimension Of Vector) from the passed address.

      \since 1.0
      */

      void FillBounds( Vec* data ) const;

      /**
      \brief Checks if the given AABB intersects with the passed AABB.

      \param other The other AABB with which the check will be done.

      \return \c true if both AABBs share a common volume or \false if not.

      */
      bool Intersects( const AABB_tpl< Vec >& other ) const;

      /**
      \brief Checks if the passed AABB is completely contained in the own AABB.

      \param other The AABB which will be checked if it is inside this AABB.

      \return \c true if the other AABB is contained inside this AABB or \false if not.
      \c true If the AABBs are the same.

      */
      bool Contains( const AABB_tpl< Vec >& other ) const;

      /**
      \brief Checks if the given point is inside the AABB.

      \param point The point to test if its inside the AABB.

      \return \c true if the Point is on an Edge or inside the AABB or \c false if the point is outside.

      */
      bool Contains( const Vec& point ) const;

      /**
      \brief Returns the centre of the AABB.

      */
      Vec Centre( void ) const;

      /**
      \brief Sets the new centre for the AABB.

      \param vec The new centre of the AABB.

      */
      void Centre( Vec& vec ) const;

      /**
      \brief Moves the AABB about the given offset.

      \param offset The offset to move thr AABB.

      */
      void Move( const Vec& offset );

      /**
      \brief Returns the current size of the AABB.

      \return

      */
      const Vec Size( void ) const;

      /**
      \brief Sets the new size for the AABB. The AABB will be scaled accordingly from the centre.

      \param size The new size for the AABB.

      */
      void Size( Vec& size ) const;

    protected:

    private:

      /**
      \brief Checks the AABB if the minimum and maximum are still valid and not mixed up.

      */
      void CheckBounds( void );

      /**
      \brief Stores the minimum of the AABB.

      */
      Vec m_Minimum;

      /**
      \brief Stores the maximum of the AABB.

      */
      Vec m_Maximum;
    };

    template< typename Vec >
    ClassicalMechanics::Volumes::AABB_tpl< Vec >::AABB_tpl() :
      m_Minimum(),
      m_Maximum()
    {
    }

    template< typename Vec >
    void ClassicalMechanics::Volumes::AABB_tpl< Vec >::Centre( Vec& vec )
    const
    {
      vec = m_Minimum + ( ( m_Maximum - m_Minimum ) / ( Scalar ) 2 );
    }

    template< typename Vec >
    Vec ClassicalMechanics::Volumes::AABB_tpl< Vec >::Centre( void )
    const
    {
      return m_Minimum + ( ( m_Maximum - m_Minimum ) / ( Scalar ) 2 );
    }

    template< typename Vec >
    bool ClassicalMechanics::Volumes::AABB_tpl< Vec >::Contains(
      const Vec& point ) const
    {
      using namespace LinearMath;

      Vec diff = Centre() - point;
      Vec size = Size() / ( Scalar ) 2;

      for( int i = 0; i < vec_size; ++i )
      {
        if( !( MathHelper_tpl< Scalar >::Abs( diff.data[ i ] ) <= size.data[ i ] ) )
        {
          return false;
        }
      }

      return true;
    }

    template< typename Vec >
    bool ClassicalMechanics::Volumes::AABB_tpl< Vec >::Contains( const AABB_tpl< Vec >& other )
    const
    {
      for( int i = 0; i < vec_size; ++i )
      {
        if( !( m_Maximum.data[ i ] >= other.m_Maximum.data[ i ] )
          && ( m_Minimum.data[ i ] <= other.m_Minimum.data[ i ] ) )
        {
          return false;
        }
      }

      return true;
    }

    template< typename Vec >
    bool ClassicalMechanics::Volumes::AABB_tpl< Vec >::Intersects( const AABB_tpl< Vec >& other )
    const
    {
      for( int i = 0; i < vec_size; ++i )
      {
        if( !( ( m_Maximum.data[ i ] >= other.m_Minimum.data[ i ] )
          && ( other.m_Maximum.data[ i ] >= m_Minimum.data[ i ] ) ) )
        {
          return false;
        }
      }

      return true;
    }

    template< typename Vec >
    void ClassicalMechanics::Volumes::AABB_tpl< Vec >::CheckBounds( void )
    {
      Scalar tmp;

      for( int i = 0; i < vec_size; ++i )
      {
        if( m_Minimum.data[ i ] > m_Maximum.data[ i ] )
        {
          tmp = m_Maximum.data[ i ];
          m_Maximum.data[ i ] = m_Minimum.data[ i ];
          m_Minimum.data[ i ] = tmp;
        }
      }
    }

    template< typename Vec >
    const Vec ClassicalMechanics::Volumes::AABB_tpl< Vec >::Size( void )
    const
    {
      return m_Maximum - m_Minimum;
    }

    template< typename Vec >
    void ClassicalMechanics::Volumes::AABB_tpl< Vec >::Size( Vec& size )
    const
    {
      size = m_Maximum - m_Minimum;
    }

    template< typename Vec >
    void ClassicalMechanics::Volumes::AABB_tpl< Vec >::Move(
      const Vec& offset )
    {
      m_Minimum += offset;
      m_Maximum += offset;
    }

    template< typename Vec >
    void ClassicalMechanics::Volumes::AABB_tpl< Vec >::FillBounds(
      Vec* data ) const
    {
      using namespace Numerics;
      Numerics::uint32 size = 1U << vec_size;
      Vec tmp;

      for( Numerics::uint32 i = 0U; i < size; ++i )
      {
        tmp = Vec();

        for( Numerics::uint32 k = 0; k < vec_size; ++k )
        {
          tmp.data[ k ] = ( ( 1U << k ) & i ) ? m_Maximum.data[ k ] : m_Minimum.data[ k ];
        }

        data[ i ] = tmp;
      }
    }

    template< typename Vec >
    const Vec& ClassicalMechanics::Volumes::AABB_tpl< Vec >::Max( void )
    const
    {
      return m_Maximum;
    }

    template< typename Vec >
    const Vec& ClassicalMechanics::Volumes::AABB_tpl< Vec >::Min( void )
    const
    {
      return m_Minimum;
    }

    template< typename Vec >
    void ClassicalMechanics::Volumes::AABB_tpl< Vec >::Max(
      const Vec& max )
    {
      m_Maximum = max;
      CheckBounds();
    }

    template< typename Vec >
    void ClassicalMechanics::Volumes::AABB_tpl< Vec >::Min(
      const Vec& min )
    {
      m_Minimum = min;
      CheckBounds();
    }

    template< typename Vec >
    ClassicalMechanics::Volumes::AABB_tpl< Vec >::AABB_tpl( const AABB_tpl& aabb ) :
      m_Minimum( aabb.m_Minimum ),
      m_Maximum( aabb.m_Maximum )
    {
    }

    template< typename Vec >
    ClassicalMechanics::Volumes::AABB_tpl< Vec >::AABB_tpl(
      const Vec& min,
      const Vec& max ) :
      m_Minimum( min ),
      m_Maximum( max )
    {
      CheckBounds();
    }
  }
}

#endif  // AABB_h__
