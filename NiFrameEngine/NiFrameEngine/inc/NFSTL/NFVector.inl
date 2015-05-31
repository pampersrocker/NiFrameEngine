#pragma once

#include "NFSTL/NFVector.hpp"
#include "NFTraits.hpp"

namespace nfe
{

  template< typename T>
  inline
    nfe::Vector<T>::Vector( Vector<T>&& rhs ) :
    m_Data( rhs.m_Data ),
    m_Size( rhs.m_Size ),
    m_ReservedSize( rhs.m_ReservedSize ),
    m_Allocator( rhs.m_Allocator )
  {
    rhs.m_Size = 0U;
    rhs.m_ReservedSize = 0U;
    rhs.m_Data = nullptr;
    rhs.m_Allocator = nullptr;
  }

  template< typename T>
  inline
    nfe::Vector<T>::Vector( const Vector<T>& rhs ) :
    m_Size( rhs.m_Size ),
    m_ReservedSize( rhs.m_ReservedSize ),
    m_Allocator( rhs.m_Allocator )
  {
    if( m_Allocator == nullptr )
    {
      m_Allocator = GetDefaultAllocator();
    }
    m_Data = static_cast< T* >( m_Allocator->Allocate( m_ReservedSize * sizeof( T ) ) );
    for( uint64 idx = 0; idx < m_Size; idx++ )
    {
      m_Data[ idx ] = rhs.m_Data[ idx ];
    }
  }


  template< typename T>
  inline
  IAllocator* nfe::Vector<T>::Allocator() const
  {
    return m_Allocator;
  }

  template< typename T>
  inline
    T* nfe::Vector<T>::Data() const
  {
    return m_Data;
  }

  template< typename T>
  VectorIterator< Vector<T> > nfe::Vector<T>::end() const
  {
    return VectorIterator< Vector<T> >( *this, m_Size );
  }

  template< typename T>
  VectorIterator< Vector<T> > nfe::Vector<T>::begin() const
  {
    return VectorIterator< Vector<T> >( *this, 0 );
  }


  template< typename T>
  inline
    void nfe::Vector<T>::Resize( uint64 newSize )
  {
    if( newSize != m_Size )
    {
      // Destruct the entries which are going to be deleted
      if( newSize < m_Size )
      {
        for( uint64 i = newSize; i < m_Size; i++ )
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
        for( uint64 i = 0; i < newSize && i < m_Size; i++ )
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
        for( uint64 i = m_Size; i < newSize; i++ )
        {
          constructWithAllocatorIfPossible( m_Data + i, m_Allocator );
          //m_Data[ i ] = T();

        }
      }
      m_Size = newSize;
    }
  }

  template< typename T>
  inline
  void nfe::Vector<T>::Clear()
  {
    Resize( 0 );
  }


  template< typename T>
  inline
    void nfe::Vector<T>::Reserve( uint64 newReserve )
  {
    // Check if we actually need to increase reserve
    if( m_ReservedSize < newReserve )
    {
      // Create new Memory Block
      T* newData = static_cast< T* >( m_Allocator->Allocate( newReserve * sizeof( T ) ) );
      NF_ASSERT( newData, "Failed to allocate memory for resizing" );
      // Copy over data to new Block
      for( uint64 i = 0; i < m_Size; i++ )
      {
        newData[ i ] = m_Data[ i ];
      }
      // Free the old memory block
      m_Allocator->Deallocate( m_Data );
      m_Data = newData;
      m_ReservedSize = newReserve;
    }
  }

  template< typename T>
  void nfe::Vector<T>::RemoveAt( uint64 idx )
  {
    NF_ASSERT( idx < m_Size, "Idx is out of range" );

    m_Data[ idx ].~T();

    for( uint64 i = idx; i < m_Size - 1; i++ )
    {
      m_Data[ i ] = m_Data[ i + 1 ];
    }
    --m_Size;
  }

  template< typename T>
  void nfe::Vector<T>::Remove( const T& member )
  {
    for( uint64 i = 0; i < m_Size; i++ )
    {
      if( member == m_Data[ i ] )
      {
        RemoveAt( i );
        return;
      }
    }
    NF_ASSERT( false, "Could not find member" );
  }

  template< typename T>
  void nfe::Vector<T>::Insert( uint64 idx, const T& member )
  {
    NF_ASSERT( idx <= m_Size, "Index is out of range for insertion" );
    //Check if we need to increase space
    if( m_Size >= m_ReservedSize )
    {
      // Amortized Doubling of the reserved size
      Reserve( m_ReservedSize * 2 );
    }
    for( uint64 i = m_Size; i >= idx && i != -1; i-- )
    {
      m_Data[ i + 1 ] = m_Data[ i ];
    }
    m_Data[ idx ] = member;
    ++m_Size;
  }

  template< typename T>
  void nfe::Vector<T>::Add( const T& member )
  {
    //Check if we need to increase space
    if( m_Size >= m_ReservedSize )
    {
      // Amortized Doubling of the reserved size
      Reserve( m_ReservedSize * 2 );
    }
    m_Data[ m_Size ] = member;
    ++m_Size;
  }

  template< typename T>
  inline
    nfe::Vector<T>::Vector( IAllocator* allocator /*= nullptr */ ) :
    Vector<T>( 2U, allocator )
  {

  }

  template< typename T>
  inline
    nfe::Vector<T>::Vector( uint64 reservedSize, IAllocator* allocator /*= nullptr */ ) :
    m_Size( 0U ),
    m_ReservedSize( reservedSize ),
    m_Allocator( allocator )
  {
    if( m_Allocator == nullptr )
    {
      m_Allocator = GetDefaultAllocator();
    }
    m_Data = static_cast< T* >( m_Allocator->Allocate( sizeof( T ) * m_ReservedSize ) );
  }

  template< typename T>
  inline
    T& nfe::Vector<T>::operator[]( uint64 idx )
  {
    NF_ASSERT( idx < m_Size, "Index is out of range" );
    return m_Data[ idx ];
  }

  template< typename T>
  const T& nfe::Vector<T>::operator[]( uint64 idx ) const
  {
    NF_ASSERT( idx < m_Size, "Index is out of range" );
    return m_Data[ idx ];
  }

  template< typename T>
  inline
    uint64 nfe::Vector<T>::ReservedSize() const
  {
    return m_ReservedSize;
  }

  template< typename T>
  inline
    nfe::Vector<T>::~Vector()
  {
    // Check if we are actually valid (e.g. was set invalid from move)
    if( m_Allocator != nullptr && m_Data != nullptr )
    {

      for( uint64 idx = 0; idx < m_Size; idx++ )
      {
        m_Data[ idx ].~T();
      }
      m_Allocator->Deallocate( m_Data );
      m_Data = nullptr;
      m_Size = 0U;
      m_ReservedSize = 0U;
    }
  }

  template <typename T>
  inline
    Vector<T>& Vector<T>::operator=( const Vector<T>& rhs )
  {
    // Check if we are actually valid (e.g. was set invalid from move)
    if( m_Allocator != nullptr && m_Data != nullptr )
    {

      for( uint64 idx = 0; idx < m_Size; idx++ )
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

    for( uint64 idx = 0; idx < m_Size; idx++ )
    {
      m_Data[ idx ] = rhs[ idx ];
    }

    return *this;
  }


  template< typename T>
  inline
    nfe::uint64 nfe::Vector<T>::Size() const
  {
    return m_Size;
  }

}
