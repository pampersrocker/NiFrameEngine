#include "NFEnginePCH.hpp"
#include "Memory/NFDefaultAllocator.hpp"

nfe::DefaultAllocator::DefaultAllocator( const char* name /*= "NFDefaultAllocator" */ ) :
IAllocator( name )
{

}

nfe::DefaultAllocator::~DefaultAllocator()
{

}

void* nfe::DefaultAllocator::Allocate( uint64 size, uint32 alignment )
{
  uint64 alSize = alignedSize( size, alignment == 0 ? 4U : alignment );
  uint8* address = new uint8[ alSize ];
  uint8 offset = static_cast< uint8 >( alignment - ( reinterpret_cast< uintptr_t >( address ) % alignment ) );
  address += offset;
  address[ -1 ] = offset;
  return address;
}

void nfe::DefaultAllocator::Deallocate( void* address )
{
  uint8* memory = static_cast< uint8* >( address );
  uint8 offset = memory[ -1 ];
  memory -= offset;
  delete [] static_cast< uint8* >( memory );
}

