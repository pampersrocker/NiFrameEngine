#pragma once

#include "NFEnginePCH.hpp"
#include "NFSTL/NFTraits.hpp"

namespace nfe
{

  class NIFRAME_API IAllocator
  {
  public:
    IAllocator( const char* name );
    virtual ~IAllocator();

    virtual  void* Allocate( NFSize size, uint32 alignment = 0 ) = 0;
    virtual void Deallocate( void* address ) = 0;

    const char* GetName() const;
  private:

    const char* m_Name;

  };

  NIFRAME_API IAllocator* GetDefaultAllocator();

  template< typename T, typename ...Params>
  T* nfnew( IAllocator* allocator, Params...parameters );
  template< typename T >
  T* nfnew( IAllocator* allocator = nullptr );
  template< typename T >
  T* nfnewArray( uint64 arraySize, IAllocator* allocator = nullptr);
  template< typename T>
  void nfdelete(T* object, IAllocator* allocator = nullptr);
  template< typename T>
  void nfdeleteArray( T* object, IAllocator* allocator = nullptr );

  NIFRAME_API NFSize alignedSize(NFSize size, uint32 alignment = 4U );
}

template< typename T>
inline
void nfe::nfdeleteArray( T* object, IAllocator* allocator /*= nullptr */ )
{
  if( allocator == nullptr )
  {
    allocator = GetDefaultAllocator();
  }
  allocator->Deallocate( object );
}

template< typename T>
inline
T* nfe::nfnewArray( uint64 arraySize, IAllocator* allocator /*= nullptr*/ )
{
  if( allocator == nullptr )
  {
    allocator = GetDefaultAllocator();
  }
  void* memBlock = allocator->Allocate( sizeof( T ) * arraySize );
  return static_cast< T* >( memBlock );
}

template< typename T>
inline
void nfe::nfdelete(T* object, IAllocator* allocator /*= nullptr*/ )
{
  if (allocator == nullptr)
  {
    allocator = GetDefaultAllocator();
  }
  object->~T();
  allocator->Deallocate( object );
}

template< typename T, typename ...Params>
inline
T* nfe::nfnew( IAllocator* allocator, Params... parameters )
{
  if (allocator == nullptr)
  {
    allocator = GetDefaultAllocator();
  }

  T* newData = static_cast<T*>( allocator->Allocate( sizeof( T ) ) );
  constructWithAllocatorIfPossible<T>(newData, allocator, parameters...);
  return newData;
}

template< typename T >
inline
T* nfe::nfnew( IAllocator* allocator /*= nullptr */ )
{
  if( allocator == nullptr )
  {
    allocator = GetDefaultAllocator();
  }

  T* newData = static_cast< T* >( allocator->Allocate( sizeof( T ) ) );
  constructWithAllocatorIfPossible<T>( newData, allocator);
  return newData;

}
