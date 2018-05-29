#pragma once
#ifndef Ray_h__
  #define Ray_h__

  #include "../../MathLibPCH.hpp"
  #include "../../LinearMath/Vector3.hpp"

namespace ClassicalMechanics
{
  namespace Algorithms
  {
    /**
    \brief Class to hold the results of a ClassicalMechanics::Algorithms::Ray3D_tpl

    In this class the collision information is held of a RayCast:
    - If a collision occurred
    - The point of the collision

    \param ScalarType the type of the numbers stored.
    
    \since 1.0

    */
    template< typename ScalarType >
    class RayResult_tpl
    {
    public:

      typedef ScalarType data_type;

      
      /**
      \brief Creates a new RayResult_tpl which does not collide. This state is not changeable (by now)

      \since 1.0
      
      */
      RayResult_tpl( void );

      /**
      \brief Creates a fully parameterized result. 
      
      By now you can only stored the point of the collision and no additional information.

      \param collisionPoint The point where the collision occurred
      \param collisionOccurred Whether the collision occurred or not (default = true)

      \since 1.0
      */
      RayResult_tpl( const LinearMath::Vector3_tpl< ScalarType >& collisionPoint, bool collisionOccurred = true );

      
      /**
      \brief Returns the collision point of the RayCast
      
      \return The point of the collision as LinearMath::Vector3_tpl. 
      If no collision occurred the defualt is (0,0,0).
      
      */
      const LinearMath::Vector3_tpl< ScalarType > CollisionPoint( void ) const;

      
      /**
      \brief Returns \c true if a collision has occurred or \c false if not
      
      
      */
      const bool CollisionOccurred( void ) const;

    protected:

      /**
      \brief Stores the information where the collision occurred.
      */
      LinearMath::Vector3_tpl< ScalarType > m_CollisionPoint;
      /**
      \brief Stores whether a collision occurred or not.
      */
      bool m_CollisionOccurred;
      
    private:

    };

    template< typename ScalarType >
    ClassicalMechanics::Algorithms::RayResult_tpl<ScalarType>::RayResult_tpl( void ) :
      m_CollisionOccurred( false ),
      m_CollisionPoint( LinearMath::Vector3_tpl< ScalarType >( 0 ) )
    {

    }

    template< typename ScalarType >
    class Ray3D_tpl
    {
    public:

      
      /**
      \brief Creates a new RayCast

      The ray starts at the origin and traverses in the direction of the direction parameter 
      the world about the length parameter.
      
      \remark This Constructor only creates a new RayCast but does not run any checks. For this use the 
      - ClassicalMechanics::Algorithms::Ray3D_tpl<T>::CheckCollisionTriangle
      methods

      \param origin The start of the RayCast
      \param direction The direction of the RayCast. The direction will be normalized upon this call.
      \param length The length of the RayCast
    
      */
      Ray3D_tpl( const LinearMath::Vector3_tpl< ScalarType >& origin,
        const LinearMath::Vector3_tpl< ScalarType >& direction,
        ScalarType length );

      
      /**
      \brief Checks the given RayCast with the given Triangle.
      
      \param triangle The triangle as LinearMath::Vector3_tpl in CCW order.
      Indices are as follows:
      <pre>
        2
       / \
      0 - 1
      </pre>
      
      \return A ClassicalMechanics::Algorithms::RayResult_tpl which holds the information 
      whether the RayCast collided with he triangle or not. Additionally the point of the collision is returned.
      
      */
      RayResult_tpl< ScalarType > CheckCollisionTriangle( const LinearMath::Vector3_tpl< ScalarType >* triangle );

    protected:

    private:

      /**
      \brief Stores the start point of the RayCast.
      */
      LinearMath::Vector3_tpl< ScalarType > m_Origin;

      /**
      \brief Stores the direction of the RayCast.
      */
      LinearMath::Vector3_tpl< ScalarType > m_Direction;

      /**
      \brief Stores the length of the RayCast.
      */
      ScalarType m_Length;
    };

    template< typename ScalarType >
    ClassicalMechanics::Algorithms::Ray3D_tpl< ScalarType >::Ray3D_tpl(
      const LinearMath::Vector3_tpl< ScalarType >& origin,
      const LinearMath::Vector3_tpl< ScalarType >& direction,
      ScalarType length ) :
      m_Origin( origin ),
      m_Direction( direction.NormalizedCopy() ),
      m_Length( length )
    {
    }

    template< typename ScalarType >
    RayResult_tpl< ScalarType > ClassicalMechanics::Algorithms::Ray3D_tpl< ScalarType >::CheckCollisionTriangle(
      const LinearMath::Vector3_tpl< ScalarType >* triangle )
    {
      using namespace LinearMath;

      Vector3_tpl< ScalarType > u = triangle[ 1 ] - triangle[ 0 ];
      Vector3_tpl< ScalarType > v = triangle[ 2 ] - triangle[ 0 ];
      Vector3_tpl< ScalarType > w;
      Vector3_tpl< ScalarType > n = ( u.CrossProduct( v ) );

      ScalarType denom = n * ( m_Direction * m_Length );

      if( denom == 0 )
      {
        return RayResult_tpl< ScalarType >( Vector3_tpl< ScalarType >( 0 ), false );
      }

      ScalarType r = (-( n * ( m_Origin - triangle[ 0 ] ) )) / denom;
      if( r < 0 || r > m_Length )
      {
        return RayResult_tpl< ScalarType >( Vector3_tpl< ScalarType >( 0 ), false );
      }

      w = ( m_Origin + m_Direction * m_Length * r ) - triangle[ 0 ];

      denom = ( u * v );
      denom *= denom;
      denom -= ( u * u ) * ( v * v );

      // May store dot products, because they are used more than once
      ScalarType si = ( ( u * v ) * ( w * v ) - ( v * v ) * ( w * u ) ) / denom;
      ScalarType ti = ( ( u * v ) * ( w * u ) - ( u * u ) * ( w * v ) ) / denom;

      bool result = ( si >= 0 ) && ( ti >= 0 ) && ( ( si + ti ) <= 1 );
      return RayResult_tpl< ScalarType >( result ? triangle[ 0 ] + si * u + ti * v : Vector3_tpl< ScalarType >(
        0 ), result );
    }

    template< typename ScalarType >
    const bool ClassicalMechanics::Algorithms::RayResult_tpl< ScalarType >::CollisionOccurred( void ) const
    {
      return m_CollisionOccurred;
    }

    template< typename ScalarType >
    const LinearMath::Vector3_tpl< ScalarType > ClassicalMechanics::Algorithms::RayResult_tpl< ScalarType >::
    CollisionPoint( void ) const
    {
      return m_CollisionPoint;
    }

    template< typename ScalarType >
    ClassicalMechanics::Algorithms::RayResult_tpl< ScalarType >::RayResult_tpl( const LinearMath::Vector3_tpl<
      ScalarType >& collisionPoint, bool collisionOccurred ) :
      m_CollisionOccurred( collisionOccurred ),
      m_CollisionPoint( collisionPoint )
    {
    }
  }
}

#endif  // Ray_h__
