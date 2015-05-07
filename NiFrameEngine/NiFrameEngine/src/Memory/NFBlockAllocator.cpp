#include "NFEnginePCH.hpp"
#include "Memory/NFBlockAllocator.hpp"

using namespace nfe;


nfe::BlockAllocator::BlockAllocator(
  const char* name /*= "NFBlockAllocator"*/,
  BlockAllocatorType allocationType /*= BlockAllocatorType::FirstFit*/,
  uint64 initialAllocationSize /*= 0U*/,
  IAllocator* parentAllocator /*= nullptr*/ ) :
  IAllocator(name),
  m_ParentAllocator(parentAllocator),
  m_AllocatorType(allocationType)
{
  if (m_ParentAllocator == nullptr)
  {
    m_ParentAllocator = GetDefaultAllocator();
  }
  m_MemoryChunks = Vector<uint8*>( m_ParentAllocator );
}

nfe::BlockAllocator::~BlockAllocator()
{

}

void nfe::BlockAllocator::SetAllocatorType( nfe::BlockAllocatorType val )
{
  m_AllocatorType = val;
}

nfe::BlockAllocatorType nfe::BlockAllocator::GetAllocatorType() const
{
  return m_AllocatorType;
}

void* nfe::BlockAllocator::Allocate( uint64 size )
{
  return nullptr;
}

void nfe::BlockAllocator::Deallocate( void* address )
{

}
