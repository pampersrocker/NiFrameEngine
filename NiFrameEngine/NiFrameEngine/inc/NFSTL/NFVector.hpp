#pragma once
#include <Memory/NFIAllocator.hpp>

namespace nfe
{
  class IAllocator;

  template< typename T>
  class Vector
  {
  public:

    static_assert( std::is_constructible<T>::value, "Template Type for Vector must be trivially constructible" );
    static_assert( std::is_copy_assignable<T>::value, "Template Type for Vector must be assignable" );
    Vector( IAllocator* allocator = nullptr );
    Vector( uint64 reservedSize, IAllocator* allocator = nullptr );
    Vector( const Vector<T>& rhs );
    Vector( Vector<T>&& rhs );
    ~Vector();

    Vector<T>& operator =( const Vector<T>& rhs );

    void Add( const T& member );
    void Insert( uint64 idx, const T& member );
    void Remove( const T& member );
    void RemoveAt( uint64 idx );
    void Resize( uint64 newSize );
    void Reserve( uint64 newReserve );

    IAllocator* Allocator() const;
    T* Data() const;

    T& operator[]( uint64 idx );
    const T& operator[]( uint64 idx ) const;

    nfe::uint64 Size() const;
    uint64 ReservedSize() const;

  private:

    T* m_Data;
    uint64 m_Size;

    uint64 m_ReservedSize;
    IAllocator* m_Allocator;
  };


}

#include "NFSTL/NFVector.inl"
