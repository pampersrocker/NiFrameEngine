#pragma once
#include <Memory/NFIAllocator.hpp>

namespace nfe
{
  class IAllocator;

  template < class Vector>
  class VectorIterator;

  template< typename T>
  class Vector
  {
  public:

    typedef T DataType;

    template < class Vector >
    friend class VectorIterator;

    static_assert( std::is_constructible<T>::value, "Template Type for Vector must have a default constructor" );
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

    VectorIterator< Vector<T> > begin() const;
    VectorIterator< Vector<T> > end() const;

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
#include "NFSTL/NFVectorIterator.hpp"

#include "NFSTL/NFVector.inl"
