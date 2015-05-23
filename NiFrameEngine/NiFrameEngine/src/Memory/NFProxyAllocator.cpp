#include "NFEnginePCH.hpp"
#include "Memory/NFProxyAllocator.hpp"

using namespace nfe;

nfe::ProxyAllocator::ProxyAllocator(
  IAllocator* parentAllocator /*= nullptr*/, const char* name /*= "NFProxyAllocator" */ ) :
  IAllocator(name),
m_ParentAllocator(parentAllocator),
m_AllocationInfos(parentAllocator)
{
  if (m_ParentAllocator == nullptr)
  {
    m_ParentAllocator = GetDefaultAllocator();
  }
}

nfe::ProxyAllocator::~ProxyAllocator()
{

}
void nfe::ProxyAllocator::Deallocate( void* address )
{
  bool found = false;
  for( uint64 i = 0; i < m_AllocationInfos.Size(); i++ )
  {
    if (m_AllocationInfos[i].Pointer == address)
    {
      m_AllocationInfos.RemoveAt( i );
      found = true;
      break;
    }
  }
  NF_ASSERT( found, "Could not find address in allocated blocks" );
}

void* nfe::ProxyAllocator::Allocate( uint64 size, uint32 alignment )
{
  void* m_Pointer = m_ParentAllocator->Allocate( size, alignment );
  ProxyAllocationInfo info;
  info.Pointer = static_cast< uint8* >( m_Pointer );
  info.Size = size;
  m_AllocationInfos.Add( info );

  return m_Pointer;
}

Vector<ProxyAllocationInfo> nfe::ProxyAllocator::AllocationInfos() const
{
  return m_AllocationInfos;
}

