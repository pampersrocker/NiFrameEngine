#pragma once
#include <Memory/NFIAllocator.hpp>
#include "NFThreadingPolicy.hpp"

namespace nfe
{
  class IAllocator;

  template < class Vector>
  class VectorIterator;



  template< typename T, typename ThreadingPolicy = NoSTLThreadingPolicy >
  class Vector
  {
  public:

    typedef T DataType;

    template < class Vector >
    friend class VectorIterator;

    static_assert( IsConstructible<T>::value, "Template Type for Vector must have a default constructor" );
    static_assert( IsCopyAssignable<T>::value, "Template Type for Vector must be assignable" );
    Vector( IAllocator* allocator = nullptr );
    Vector(NFSize reservedSize, IAllocator* allocator = nullptr );
    Vector( const Vector<T, ThreadingPolicy>& rhs );
    Vector( Vector<T, ThreadingPolicy>&& rhs );
    ~Vector();

    Vector<T, ThreadingPolicy>& operator =( const Vector<T, ThreadingPolicy>& rhs );

    void Add( const T& member );
    void Insert(NFSize idx, const T& member );
    bool Remove( const T& member );
    void RemoveAt(NFSize idx );
    void Resize(NFSize newSize );
    void Reserve(NFSize newReserve );
    bool TryPop( T* result );
    void Clear();

    VectorIterator< Vector<T, ThreadingPolicy> > begin() const;
    VectorIterator< Vector<T, ThreadingPolicy> > end() const;

    IAllocator* Allocator() const;
    T* Data() const;

    T& operator[]( NFSize idx );
    const T& operator[]( NFSize idx ) const;

    nfe::NFSize Size() const;
    NFSize ReservedSize() const;

  private:

    void RemoveAt_Unsynchronized(NFSize Index);

    T* m_Data;
    NFSize m_Size;

    NFSize m_ReservedSize;
    IAllocator* m_Allocator;
    mutable ThreadingPolicy m_ThreadingPolicy;
  };




}
#include "NFSTL/NFVectorIterator.hpp"

#include "NFSTL/NFVector.inl"
