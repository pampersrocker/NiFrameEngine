#pragma once
#ifndef AABB3D_h__
  #define AABB3D_h__

  #include "../../MathLibPCH.hpp"
  #include "../../LinearMath/MathHelper.hpp"
  #include "../../LinearMath/Vector3.hpp"

namespace ClassicalMechanics
{
  namespace Volumes
  {
    /**
    \brief Template which stores an Axis Aligned Bounding Box (AABB) in 3D.

    \since 1.0
    */
    template< typename ScalarType >
    class AABB3D_tpl
    {
    public:

      typedef ScalarType data_type;

      
      /**
      \brief Creates a new AABB3D_tpl spanning from min to max
      
      \param min The minimum position of the Bounding Box
      \param max The maximum position of the Bounding Box
      
      \remark The minimum and maximum may be interchangeable. 
      The bounding box itself checks if the minimum is the absolute minimum and vice versa.

      \since 1.0
      */
      AABB3D_tpl(
        const LinearMath::Vector3_tpl< ScalarType >& min,
        const LinearMath::Vector3_tpl< ScalarType >& max );


      AABB3D_tpl();

      
      /**
      \brief Copy constructor for the AABB3D_tpl. Copies the minimum and maximum vectors.
      
      \param aabb The AABB which will be copied.

      \since 1.0
      */
      AABB3D_tpl( const AABB3D_tpl& aabb );

      
      /**
      \brief Sets the new minimum of the AABB.

      
      \param min The AABB checks if the new minimum is still smaller than the current maximum 
      and switches the components of the vectors accordingly.

      \since 1.0
      */
      void Min( const LinearMath::Vector3_tpl< ScalarType >& min );

      /**
      \brief Sets the new maximum of the AABB.

      
      \param min The AABB checks if the new maximum is still bigger than the current minimum 
      and switches the components of the vectors accordingly.

      \since 1.0
      */
      void Max( const LinearMath::Vector3_tpl< ScalarType >& max );

      
      /**
      \brief Returns the current minimum of the AABB.

      \return The current minimum of the AABB as Vector3 

      \since 1.0
      */
      const LinearMath::Vector3_tpl< ScalarType >& Min( void ) const;

      /**
      \brief Returns the current maximum of the AABB.

      \return The current maximum of the AABB as Vector3 
      
      \since 1.0
      */
      const LinearMath::Vector3_tpl< ScalarType >& Max( void ) const;

      
      /**
      \brief Stores the Bounding vertices of te AABB into the given array.
      
      \param data A Vector3_tpl pointer which needs to have a size of at least 8.
      
      \remark The data pointer needs to have a size of at least 8 from the passed address.

      \since 1.0
      */
      void FillBounds( LinearMath::Vector3_tpl< ScalarType >* data ) const;

      /**
      \brief Checks if the given AABB intersects with the passed AABB.
      
      \param other The other AABB with which the check will be done.
      
      \return \c true if both AABBs share a common volume or \false if not.
      
      */
      bool Intersects( const AABB3D_tpl< ScalarType >& other ) const;

      
      /**
      \brief Checks if the passed AABB is completely contained in the own AABB.
      
      \param other The AABB which will be checked if it is inside this AABB.
      
      \return \c true if the other AABB is contained inside this AABB or \false if not.
      \c true If the AABBs are the same.
      
      */
      bool Contains( const AABB3D_tpl< ScalarType >& other ) const;

      
      /**
      \brief Checks if the given point is inside the AABB.
      
      \param point The point to test if its inside the AABB.
      
      \return \c true if the Point is on an Edge or inside the AABB or \c false if the point is outside.
      
      */
      bool Contains( const LinearMath::Vector3_tpl< ScalarType >& point );

      
      /**
      \brief Returns the centre of the AABB.
      
      */
      LinearMath::Vector3_tpl< ScalarType > Centre( void ) const;

      
      /**
      \brief Sets the new centre for the AABB.
      
      \param vec The new centre of the AABB.
      
      */
      void Centre( LinearMath::Vector3_tpl< ScalarType >& vec ) const;

      
      /**
      \brief Moves the AABB about the given offset.
      
      \param offset The offset to move thr AABB.

      */
      void Move( const LinearMath::Vector3_tpl< ScalarType >& offset );

      
      /**
      \brief Returns the current size of the AABB.
      
      \return 
      
      */
      const LinearMath::Vector3_tpl< ScalarType > Size( void ) const;

      
      /**
      \brief Sets the new size for the AABB. The AABB will be scaled accordingly from the centre.
      
      \param size The new size for the AABB.

      */
      void Size( LinearMath::Vector3_tpl< ScalarType >& size ) const;

    protected:

    private:

      /**
      \brief Checks the AABB if the minimum and maximum are still valid and not mixed up.

      */
      void CheckBounds( void );

      /**
      \brief Stores the minimum of the AABB.
      
      */
      LinearMath::Vector3_tpl< ScalarType > m_Minimum;

      /**
      \brief Stores the maximum of the AABB.
      
      */
      LinearMath::Vector3_tpl< ScalarType > m_Maximum;
    };

    template< typename ScalarType >
    ClassicalMechanics::Volumes::AABB3D_tpl<ScalarType>::AABB3D_tpl() :
      m_Minimum(),
      m_Maximum()
    {

    }

    template< typename ScalarType >
    void ClassicalMechanics::Volumes::AABB3D_tpl< ScalarType >::Centre( LinearMath::Vector3_tpl< ScalarType >& vec )
    const
    {
      vec = m_Minimum + 0.5f * m_Maximum;
    }

    template< typename ScalarType >
    LinearMath::Vector3_tpl< ScalarType > ClassicalMechanics::Volumes::AABB3D_tpl< ScalarType >::Centre( void )
    const
    {
      return m_Minimum + 0.5f * m_Maximum;
    }

    template< typename ScalarType >
    bool ClassicalMechanics::Volumes::AABB3D_tpl< ScalarType >::Contains(
      const LinearMath::Vector3_tpl< ScalarType >& point )
    {
      using namespace LinearMath;

      Vector3_tpl< ScalarType > diff = Centre() - point;
      Vector3_tpl< ScalarType > size = Size();

      return ( MathHelper_tpl< ScalarType >::Abs( diff.X ) <= size.X )
           && ( MathHelper_tpl< ScalarType >::Abs( diff.Y ) <= size.Y )
           && ( MathHelper_tpl< ScalarType >::Abs( diff.Z ) <= size.Z );
    }

    template< typename ScalarType >
    bool ClassicalMechanics::Volumes::AABB3D_tpl< ScalarType >::Contains( const AABB3D_tpl< ScalarType >& other )
    const
    {
      return ( ( m_Maximum.X >= other.m_Maximum.X ) && ( m_Minimum.X <= other.m_Minimum.X ) )
           && ( ( m_Maximum.Y >= other.m_Maximum.Y ) && ( m_Minimum.Y <= other.m_Minimum.Y ) )
           && ( ( m_Maximum.Z >= other.m_Maximum.Z ) && ( m_Minimum.Z <= other.m_Minimum.Z ) );
    }

    template< typename ScalarType >
    bool ClassicalMechanics::Volumes::AABB3D_tpl< ScalarType >::Intersects( const AABB3D_tpl< ScalarType >& other )
    const
    {
      return ( ( m_Maximum.X >= other.m_Minimum.X ) && ( other.m_Maximum.X >= m_Minimum.X ) )
           && ( ( m_Maximum.Y >= other.m_Minimum.Y ) && ( other.m_Maximum.Y >= m_Minimum.Y ) )
           && ( ( m_Maximum.Z >= other.m_Minimum.Z ) && ( other.m_Maximum.Z >= m_Minimum.Z ) );
    }

    template< typename ScalarType >
    void ClassicalMechanics::Volumes::AABB3D_tpl< ScalarType >::CheckBounds( void )
    {
      ScalarType tmp;

      if( m_Minimum.X > m_Maximum.X )
      {
        tmp = m_Maximum.X;
        m_Maximum.X = m_Minimum.X;
        m_Minimum.X = tmp;
      }

      if( m_Minimum.Y > m_Maximum.Y )
      {
        tmp = m_Maximum.Y;
        m_Maximum.Y = m_Minimum.Y;
        m_Minimum.Y = tmp;
      }

      if( m_Minimum.Z > m_Maximum.Z )
      {
        tmp = m_Maximum.Z;
        m_Maximum.Z = m_Minimum.Z;
        m_Minimum.Z = tmp;
      }
    }

    template< typename ScalarType >
    const LinearMath::Vector3_tpl< ScalarType > ClassicalMechanics::Volumes::AABB3D_tpl< ScalarType >::Size( void )
    const
    {
      return m_Maximum - m_Minimum;
    }

    template< typename ScalarType >
    void ClassicalMechanics::Volumes::AABB3D_tpl< ScalarType >::Size( LinearMath::Vector3_tpl< ScalarType >& size )
    const
    {
      size = m_Maximum - m_Minimum;
    }

    template< typename ScalarType >
    void ClassicalMechanics::Volumes::AABB3D_tpl< ScalarType >::Move(
      const LinearMath::Vector3_tpl< ScalarType >& offset )
    {
      m_Minimum += offset;
      m_Maximum += offset;
    }

    template< typename ScalarType >
    void ClassicalMechanics::Volumes::AABB3D_tpl< ScalarType >::FillBounds(
      LinearMath::Vector3_tpl< ScalarType >* data ) const
    {
      using namespace Numerics;

      for( uint8 i = 0U; i < 8U; ++i )
      {
        data[ i ] = LinearMath::Vector3_tpl< ScalarType >(
          ( 1U & i ) ? m_Maximum.X : m_Minimum.X,
          ( 2U & i ) ? m_Maximum.Y : m_Minimum.Y,
          ( 4U & i ) ? m_Maximum.Z : m_Minimum.Z );
      }
    }

    template< typename ScalarType >
    const LinearMath::Vector3_tpl< ScalarType >& ClassicalMechanics::Volumes::AABB3D_tpl< ScalarType >::Max( void )
    const
    {
      return m_Maximum;
    }

    template< typename ScalarType >
    const LinearMath::Vector3_tpl< ScalarType >& ClassicalMechanics::Volumes::AABB3D_tpl< ScalarType >::Min( void )
    const
    {
      return m_Minimum;
    }

    template< typename ScalarType >
    void ClassicalMechanics::Volumes::AABB3D_tpl< ScalarType >::Max(
      const LinearMath::Vector3_tpl< ScalarType >& max )
    {
      m_Maximum = max;
      CheckBounds();
    }

    template< typename ScalarType >
    void ClassicalMechanics::Volumes::AABB3D_tpl< ScalarType >::Min(
      const LinearMath::Vector3_tpl< ScalarType >& min )
    {
      m_Minimum = min;
      CheckBounds();
    }

    template< typename ScalarType >
    ClassicalMechanics::Volumes::AABB3D_tpl< ScalarType >::AABB3D_tpl( const AABB3D_tpl& aabb ) :
      m_Minimum( aabb.m_Minimum ),
      m_Maximum( aabb.m_Maximum )
    {
    }

    template< typename ScalarType >
    ClassicalMechanics::Volumes::AABB3D_tpl< ScalarType >::AABB3D_tpl(
      const LinearMath::Vector3_tpl< ScalarType >& min,
      const LinearMath::Vector3_tpl< ScalarType >& max ) :
      m_Minimum( min ),
      m_Maximum( max )
    {
      CheckBounds();
    }
  }
}

#endif  // AABB3D_h__
