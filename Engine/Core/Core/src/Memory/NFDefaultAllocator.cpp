#include "NFEnginePCH.hpp"
#include "Memory/NFDefaultAllocator.hpp"
#include "Platform/NFPlatformMemory.hpp"

nfe::DefaultAllocator::DefaultAllocator( const char* name /*= "NFDefaultAllocator" */ ) :
IAllocator( name )
{

}

nfe::DefaultAllocator::~DefaultAllocator()
{

}

void* nfe::DefaultAllocator::Allocate( NFSize size, uint32 alignment )
{
  NFSize alSize = alignedSize( size, alignment == 0 ? 4U : alignment );
  uint8* address = reinterpret_cast<uint8*>(::nfe::PlatformMemory::Allocate(alSize));
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
  ::nfe::PlatformMemory::Free(memory);
}

