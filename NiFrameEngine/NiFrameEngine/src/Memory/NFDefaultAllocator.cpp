#include "NFEnginePCH.hpp"
#include "Memory/NFDefaultAllocator.hpp"

nfe::DefaultAllocator::DefaultAllocator( const char* name /*= "NFDefaultAllocator" */ ) :
IAllocator( name )
{

}

nfe::DefaultAllocator::~DefaultAllocator()
{

}

void* nfe::DefaultAllocator::Allocate( uint64 size )
{
  return new uint8[ size ];
}

void nfe::DefaultAllocator::Deallocate( void* address )
{
  delete [] static_cast< uint8* >( address );
}

