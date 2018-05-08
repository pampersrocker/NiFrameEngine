#include "NFEnginePCH.hpp"
#include "Memory/NFStackAllocator.hpp"
#include "NFEngine.hpp"


nfe::StackAllocator::StackAllocator(
  NFSize size,
  uint32 alignment /*= sizeof(void*)*/,
  IAllocator* parentAllocator /*= nullptr*/,
  const char* name /*= "NFStackAllocator"*/ ) :
  IAllocator( name ),
  m_Size( size ),
  m_Alignment( alignment ),
  m_ParentAllocator( parentAllocator ),
  m_Memory( nullptr ),
  m_CurrentMarker( nullptr )
{
  if( m_ParentAllocator == nullptr )
  {
    m_ParentAllocator = GetDefaultAllocator();
  }

  NFSize alignedSize = ::nfe::alignedSize( size, alignment );

  m_Memory = static_cast< uint8* >( m_ParentAllocator->Allocate( alignedSize, alignment ) );

  m_CurrentMarker = m_Memory;
}

nfe::StackAllocator::~StackAllocator()
{
  m_ParentAllocator->Deallocate( m_Memory );

  m_Memory = nullptr;
  m_CurrentMarker = nullptr;
}

void* nfe::StackAllocator::Allocate(NFSize size, uint32 alignment )
{
  uint32 usedAlignment = alignment == 0 ? m_Alignment : alignment;
  NFSize alignedSize = nfe::alignedSize( size, usedAlignment );
  uintptr_t maxPtr = reinterpret_cast< uintptr_t >( m_Memory ) +m_Size;
  m_LastAllocation = m_CurrentMarker;

  uint32 offset = usedAlignment - ( reinterpret_cast< uintptr_t >( m_CurrentMarker ) % usedAlignment );
  alignedSize += offset;
  void* allocatedAddress = m_CurrentMarker + offset;

  uintptr_t newPtr = ( reinterpret_cast< uintptr_t >( m_CurrentMarker ) + alignedSize );
  NF_ASSERT( newPtr < maxPtr, "Tried to allocate more than the StackAllocator holds" );
  if (newPtr > maxPtr)
  {
    return nullptr;
  }
  m_CurrentMarker += alignedSize;
  return allocatedAddress;
}

void nfe::StackAllocator::Deallocate( void* address )
{
  NF_ASSERT( address > m_Memory && address < m_Memory + m_Size,
    "Tried to Deallocate pointer out of this allocator range" );
  // TODO: Check if skip other allocations ?
  if( address == m_LastAllocation )
  {
    m_CurrentMarker = static_cast< uint8* >( address );
  }
}
