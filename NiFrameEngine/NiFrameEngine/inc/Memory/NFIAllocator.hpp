#pragma once

#include "NFEnginePCH.hpp"

namespace nfe
{

  class NIFRAME_DLL_EXPORT IAllocator
  {
  public:
    IAllocator( const char* name );
    virtual ~IAllocator();

    virtual  void* Allocate( uint64 size ) = 0;
    virtual void Deallocate( void* address ) = 0;

    const char* GetName() const;
  private:

    const char* m_Name;

  };

  NIFRAME_DLL_EXPORT IAllocator* GetDefaultAllocator();

  template< typename T, typename ...Params>
  T* nfnew( IAllocator* allocator = nullptr, Params... parameters );
  template< typename T, typename ...Params>
  T* nfnewArray( uint64 arraySize, IAllocator* allocator = nullptr, Params... parameters );
  template< typename T>
  void nfdelete(T* object, IAllocator* allocator = nullptr);
  template< typename T>
  void nfdeleteArray( T* object, IAllocator* allocator = nullptr );
}

template< typename T>
void nfe::nfdeleteArray( T* object, IAllocator* allocator /*= nullptr */ )
{
  if( allocator == nullptr )
  {
    allocator = GetDefaultAllocator();
  }
  allocator->Deallocate( object );
}

template< typename T, typename ...Params>
inline
T* nfe::nfnewArray( uint64 arraySize, IAllocator* allocator /*= nullptr*/, Params... parameters )
{
  if( allocator == nullptr )
  {
    allocator = GetDefaultAllocator();
  }
  void* memBlock = allocator->Allocate( sizeof( T ) * arraySize );
  return static_cast< T* >( memBlock );
}

template< typename T>
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
T* nfe::nfnew( IAllocator* allocator /*= nullptr */, Params... parameters )
{
  if (allocator == nullptr)
  {
    allocator = GetDefaultAllocator();
  }
  void* memBlock = allocator->Allocate( sizeof( T ) );
  T* newData = new ( memBlock ) T( parameters );
  return newData;
}
