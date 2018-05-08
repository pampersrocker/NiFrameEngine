#pragma once

#include "NFSTL/NFVector.hpp"
#include "NFTraits.hpp"
#include "Platform/NFGenericPlatform.hpp"

namespace nfe
{

  template< typename T, typename ThreadingPolicy >
  inline
    nfe::Vector<T, ThreadingPolicy>::Vector( Vector<T, ThreadingPolicy>&& rhs ) :
    m_Data( rhs.m_Data ),
    m_Size( rhs.m_Size ),
    m_ReservedSize( rhs.m_ReservedSize ),
    m_Allocator( rhs.m_Allocator ),
    m_ThreadingPolicy()
  {
    rhs.m_Size = 0U;
    rhs.m_ReservedSize = 0U;
    rhs.m_Data = nullptr;
    rhs.m_Allocator = nullptr;
  }

  template< typename T, typename ThreadingPolicy >
  inline
    nfe::Vector<T, ThreadingPolicy>::Vector( const Vector<T, ThreadingPolicy>& rhs ) :
    m_Size( rhs.m_Size ),
    m_ReservedSize( rhs.m_ReservedSize ),
    m_Allocator( rhs.m_Allocator ),
    m_ThreadingPolicy()
  {
    if( m_Allocator == nullptr )
    {
      m_Allocator = GetDefaultAllocator();
    }
    m_Data = static_cast< T* >( m_Allocator->Allocate( static_cast<NFSize>(m_ReservedSize * sizeof( T )) ) );
    for( NFSize idx = 0; idx < m_Size; idx++ )
    {
      m_Data[ idx ] = rhs.m_Data[ idx ];
    }
  }


  template< typename T, typename ThreadingPolicy >
  inline
  IAllocator* nfe::Vector<T, ThreadingPolicy>::Allocator() const
  {
    return m_Allocator;
  }

  template< typename T, typename ThreadingPolicy >
  inline
    T* nfe::Vector<T, ThreadingPolicy>::Data() const
  {
    return m_Data;
  }

  template< typename T, typename ThreadingPolicy >
  VectorIterator< Vector<T, ThreadingPolicy> > nfe::Vector<T, ThreadingPolicy>::end() const
  {
    return VectorIterator< Vector<T, ThreadingPolicy> >( *this, m_Size );

  }

  template< typename T, typename ThreadingPolicy >
  VectorIterator< Vector<T, ThreadingPolicy> > nfe::Vector<T, ThreadingPolicy>::begin() const
  {
    return VectorIterator< Vector<T, ThreadingPolicy> >( *this, 0 );

  }


  template< typename T, typename ThreadingPolicy >
  inline
    void nfe::Vector<T, ThreadingPolicy>::Resize( NFSize newSize )
  {
    m_ThreadingPolicy.Lock();
    if( newSize != m_Size )
    {
      // Destruct the entries which are going to be deleted
      if( newSize < m_Size )
      {
        for( NFSize i = newSize; i < m_Size; i++ )
        {
          m_Data[ i ].~T();
        }
      }
      if( newSize > m_ReservedSize )
      {
        // Create new Memory Block
        T* newData = static_cast< T* >( m_Allocator->Allocate( newSize * sizeof( T ) ) );
        NF_ASSERT( newData, "Failed to allocate memory for resizing" );
        // Copy over data to new Block
        for( NFSize i = 0; i < newSize && i < m_Size; i++ )
        {
          newData[ i ] = m_Data[ i ];
        }
        // Free the old memory block
        m_Allocator->Deallocate( m_Data );
        m_Data = newData;
        m_ReservedSize = newSize;
      }
      // If we increased the size, default construct the new members
      if( newSize > m_Size )
      {
        for( NFSize i = m_Size; i < newSize; i++ )
        {
          constructWithAllocatorIfPossible( m_Data + i, m_Allocator );
          //m_Data[ i ] = T();

        }
      }
      m_Size = newSize;
    }
    m_ThreadingPolicy.Unlock();
  }

  template< typename T, typename ThreadingPolicy >
  inline
  void nfe::Vector<T, ThreadingPolicy>::Clear()
  {
    // Resize itself does lock, so no locking required here
    Resize( 0 );
  }


  template< typename T, typename ThreadingPolicy >
  inline
    void nfe::Vector<T, ThreadingPolicy>::Reserve( NFSize newReserve )
  {
    //m_ThreadingPolicy.Lock();

    // Check if we actually need to increase reserve
    if( m_ReservedSize < newReserve )
    {
      // Create new Memory Block
      T* newData = static_cast< T* >( m_Allocator->Allocate( newReserve * sizeof( T ) ) );
      NF_ASSERT( newData, "Failed to allocate memory for resizing" );
      // Copy over data to new Block
      for( NFSize i = 0; i < m_Size; i++ )
      {
        new ( &newData[ i ] ) T();
        newData[ i ] = m_Data[ i ];
      }
      // Free the old memory block
      m_Allocator->Deallocate( m_Data );
      m_Data = newData;
      m_ReservedSize = newReserve;
    }
    //m_ThreadingPolicy.Unlock();

  }

  template< typename T, typename ThreadingPolicy >
  void nfe::Vector<T, ThreadingPolicy>::RemoveAt( NFSize idx )
  {
    m_ThreadingPolicy.Lock();

    NF_ASSERT( idx < m_Size, "Idx is out of range" );

    m_Data[ idx ].~T();

    for( NFSize i = idx; i < m_Size - 1; i++ )
    {
      m_Data[ i ] = m_Data[ i + 1 ];
    }
    --m_Size;
    m_ThreadingPolicy.Unlock();
  }

  template< typename T, typename ThreadingPolicy >
  void nfe::Vector<T, ThreadingPolicy>::Remove( const T& member )
  {
    m_ThreadingPolicy.Lock();

    for( NFSize i = 0; i < m_Size; i++ )
    {
      if( member == m_Data[ i ] )
      {
        // Need to unlock here, because RemoveAt does lock
        m_ThreadingPolicy.Unlock();
        RemoveAt( i );
        return;
      }
    }
    NF_ASSERT( false, "Could not find member" );
    // Should never be reached
    m_ThreadingPolicy.Unlock();
  }

  template< typename T, typename ThreadingPolicy >
  void nfe::Vector<T, ThreadingPolicy>::Insert(NFSize idx, const T& member )
  {
    m_ThreadingPolicy.Lock();
    NF_ASSERT( idx <= m_Size, "Index is out of range for insertion" );
    //Check if we need to increase space
    if( m_Size >= m_ReservedSize )
    {
      m_ThreadingPolicy.Unlock();

      // Amortized Doubling of the reserved size

      Reserve( m_ReservedSize * 2 );
      m_ThreadingPolicy.Lock();

    }
    for(NFSize i = m_Size; i >= idx && i != -1; i-- )
    {
      m_Data[ i + 1 ] = m_Data[ i ];
    }
    m_Data[ idx ] = member;
    ++m_Size;
    m_ThreadingPolicy.Unlock();
  }

  template< typename T, typename ThreadingPolicy >
  void nfe::Vector<T, ThreadingPolicy>::Add( const T& member )
  {
    m_ThreadingPolicy.Lock();

    //Check if we need to increase space
    if( m_Size >= m_ReservedSize )
    {
      //m_ThreadingPolicy.Unlock();

      // Amortized Doubling of the reserved size
      Reserve( m_ReservedSize * 2 );
      //m_ThreadingPolicy.Lock();

    }
    new ( m_Data + m_Size ) T();
    m_Data[ m_Size ] = member;
    ++m_Size;
    m_ThreadingPolicy.Unlock();

  }

  template< typename T, typename ThreadingPolicy >
  inline
    nfe::Vector<T, ThreadingPolicy>::Vector( IAllocator* allocator /*= nullptr */ ) :
    Vector<T, ThreadingPolicy>( 2U, allocator )
  {

  }

  template< typename T, typename ThreadingPolicy >
  inline
    nfe::Vector<T, ThreadingPolicy>::Vector(NFSize reservedSize, IAllocator* allocator /*= nullptr */ ) :
    m_Size( 0U ),
    m_ReservedSize( reservedSize ),
    m_Allocator( allocator ),
    m_ThreadingPolicy()
  {
    if( m_Allocator == nullptr )
    {
      m_Allocator = GetDefaultAllocator();
    }
    m_Data = static_cast< T* >( m_Allocator->Allocate( sizeof( T ) * m_ReservedSize ) );
  }

  template< typename T, typename ThreadingPolicy >
  inline
    T& nfe::Vector<T, ThreadingPolicy>::operator[](NFSize idx )
  {
    m_ThreadingPolicy.Lock();
    NF_ASSERT( idx < m_Size, "Index is out of range" );
    T& data = m_Data[ idx ];
    m_ThreadingPolicy.Unlock();
    return data;

  }

  template< typename T, typename ThreadingPolicy >
  const T& nfe::Vector<T, ThreadingPolicy>::operator[](NFSize idx ) const
  {
    m_ThreadingPolicy.Lock();
    NF_ASSERT( idx < m_Size, "Index is out of range" );
    const T& data = m_Data[ idx ];
    m_ThreadingPolicy.Unlock();
    return data;
  }

  template< typename T, typename ThreadingPolicy >
  inline
    NFSize nfe::Vector<T, ThreadingPolicy>::ReservedSize() const
  {
    return m_ReservedSize;
  }

  template< typename T, typename ThreadingPolicy >
  inline
    nfe::Vector<T, ThreadingPolicy>::~Vector()
  {
    // We should not require a lock here, since when this is being destroyed no one else should access it anyway.

    // Check if we are actually valid (e.g. was set invalid from move)
    if( m_Allocator != nullptr && m_Data != nullptr )
    {

      for(NFSize idx = 0; idx < m_Size; idx++ )
      {
        m_Data[ idx ].~T();
      }
      m_Allocator->Deallocate( m_Data );
      m_Data = nullptr;
      m_Size = 0U;
      m_ReservedSize = 0U;
    }
  }

  template< typename T, typename ThreadingPolicy >
  inline
    Vector<T, ThreadingPolicy>& Vector<T, ThreadingPolicy>::operator=( const Vector<T, ThreadingPolicy>& rhs )
  {
    // Check if we are actually valid (e.g. was set invalid from move)
    m_ThreadingPolicy.Lock();
    rhs.m_ThreadingPolicy.Lock();
    if( m_Allocator != nullptr && m_Data != nullptr )
    {

      for(NFSize idx = 0; idx < m_Size; idx++ )
      {
        m_Data[ idx ].~T();
      }
      m_Allocator->Deallocate( m_Data );
      m_Data = nullptr;
      m_Size = 0U;
      m_ReservedSize = 0U;
    }
    m_Allocator = rhs.m_Allocator;
    m_Data = static_cast< T* >( m_Allocator->Allocate( sizeof( T ) * rhs.m_ReservedSize ) );
    m_Size = rhs.m_Size;
    m_ReservedSize = rhs.m_ReservedSize;

    for(NFSize idx = 0; idx < m_Size; idx++ )
    {
      m_Data[ idx ] = rhs.m_Data[ idx ];
    }
    rhs.m_ThreadingPolicy.Unlock();
    m_ThreadingPolicy.Unlock();

    return *this;
  }


  template< typename T, typename ThreadingPolicy /*= NoSTLThreadingPolicy */>
  bool nfe::Vector<T, ThreadingPolicy>::TryPop( T* result )
  {
    m_ThreadingPolicy.Lock();
    if( m_Size > 0 )
    {
      *result = m_Data[ m_Size - 1 ];
      m_Size--;
      m_ThreadingPolicy.Unlock();
      return true;
    }
    else
    {
      m_ThreadingPolicy.Unlock();
      return false;
    }
  }



  template< typename T, typename ThreadingPolicy >
  inline
    nfe::NFSize nfe::Vector<T, ThreadingPolicy>::Size() const
  {
    return m_Size;
  }

}
