#include "NFEnginePCH.hpp"
#include "Memory/NFBlockAllocator.hpp"
#include "Platform/NFPlatform.hpp"

using namespace nfe;


nfe::BlockAllocator::BlockAllocator(
  const char* name /*= "NFBlockAllocator"*/,
  uint32 alignment,
  BlockAllocatorType allocationType /*= BlockAllocatorType::FirstFit*/,
  uint64 initialAllocationSize /*= 0U*/,
  IAllocator* parentAllocator /*= nullptr*/,
  IAllocator* internalAllocator) :
  IAllocator(name),
  m_Alignment(alignment),
  m_ParentAllocator(parentAllocator),
  m_AllocatorType(allocationType),
  m_AllocatedBlocks( internalAllocator ? internalAllocator : parentAllocator ),
  m_FreeMemoryChunks( internalAllocator ? internalAllocator : parentAllocator ),
  m_UsedMemoryChunks( internalAllocator ? internalAllocator : parentAllocator )
{
  if (m_ParentAllocator == nullptr)
  {
    m_ParentAllocator = GetDefaultAllocator();
  }
  if( initialAllocationSize > 0 )
  {
    BlockAllocatorChunk initalBlock;
    uint64 alignedSize = ::nfe::alignedSize( initialAllocationSize, alignment );

    uint8* ptr = static_cast< uint8* >( m_ParentAllocator->Allocate( alignedSize ) );
    initalBlock.Pointer = ptr;
    initalBlock.Size = alignedSize;
    initalBlock.CalculateEndAddress();
    m_AllocatedBlocks.Add( initalBlock );
    m_FreeMemoryChunks.Add( initalBlock );
  }
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

void* nfe::BlockAllocator::Allocate( uint64 size, uint32 alignment )
{
  uint32 usedAlignment = alignment == 0 ? m_Alignment : alignment;
  // Add usedAlignment for the case we need to offset the allocation, so we have enough memory for the movement
  uint64 alignedSize = ::nfe::alignedSize( size, usedAlignment ) + usedAlignment;
  NF_ASSERT( alignedSize > 0, "One cannot simply allocate a size of 0!" );
  if( alignedSize <= 0 )
  {
    return nullptr;
  }
  uint64 blockIdx = -1;
  switch (m_AllocatorType)
  {
  case BlockAllocatorType::BestFit:
    blockIdx = FindBestFitBlock( alignedSize );
    break;
  case BlockAllocatorType::FirstFit:
    blockIdx = FindFirstFitBlock( alignedSize );
    break;
  case BlockAllocatorType::WorstFit:
    blockIdx = FindWorstFitBlock( alignedSize );
    break;
  default:
    NF_ASSERT( false, "?!" );
    break;
  }

  if (blockIdx == -1)
  {
    uint64 newBlockSize = 0;

    if (m_AllocatedBlocks.Size() > 0)
    {
      auto& lastBlock = m_AllocatedBlocks[ m_AllocatedBlocks.Size() - 1 ];
      newBlockSize = alignedSize > lastBlock.Size * 2 ? alignedSize : lastBlock.Size * 2;
    }
    else
    {
      newBlockSize = alignedSize;
    }
    BlockAllocatorChunk newBlock;
    newBlock.Pointer = static_cast< uint8* >( m_ParentAllocator->Allocate( newBlockSize ) );
    newBlock.Size = newBlockSize;
    newBlock.CalculateEndAddress();
    newBlock.Offset = 0;
    m_AllocatedBlocks.Add( newBlock );
    blockIdx = m_FreeMemoryChunks.Size();
    m_FreeMemoryChunks.Add( newBlock );
  }
  BlockAllocatorChunk block = m_FreeMemoryChunks[ blockIdx ];
  BlockAllocatorChunk secondChunk;
  if( reinterpret_cast< uintptr_t >( block.Pointer ) % usedAlignment != 0 )
  {
    block.Offset = static_cast< uint32 >( usedAlignment - (reinterpret_cast< uintptr_t >( block.Pointer ) % usedAlignment) );
  }
  else
  {
    block.Offset = 0;
    // Remove the extra bit for the alignment since we don't need it.
    alignedSize -= usedAlignment;
  }
  SplitBlock( alignedSize, block, secondChunk );
  block.Pointer += block.Offset;
  m_UsedMemoryChunks.Add( block );
  if( secondChunk.Valid() )
  {
    m_FreeMemoryChunks[ blockIdx ] = secondChunk;
  }
  else
  {
    m_FreeMemoryChunks.RemoveAt( blockIdx );
  }
  if( GPlatform )
  {
    GPlatform->OnAllocation( block.Pointer, alignedSize );
  }
  return block.Pointer;
}

void nfe::BlockAllocator::Deallocate( void* address )
{
  if( address != nullptr )
  {
    uint64 idx = 0;
    for( auto& chunk : m_UsedMemoryChunks )
    {
      if( chunk.Pointer == address )
      {
        break;
      }
      idx++;
    }
    uint8 offset = static_cast< uint8* >( address )[ -1 ];
    uint8* pointer = static_cast< uint8* >( address ) -offset;
    if( idx == m_UsedMemoryChunks.Size() )
    {
      idx = 0;
      for( auto& chunk : m_UsedMemoryChunks )
      {
        if( chunk.Pointer == pointer )
        {
          break;
        }
        idx++;
      }
    }

    NF_ASSERT( idx != m_UsedMemoryChunks.Size(), "Could not find Allocated Block" );

    BlockAllocatorChunk chunk = m_UsedMemoryChunks[ idx ];
    memset( chunk.Pointer, 0xFF, chunk.Size );
    if( GPlatform )
    {
      GPlatform->OnDeallocation( chunk.Pointer, chunk.Size );
    }
    m_UsedMemoryChunks.RemoveAt( idx );
    chunk.Pointer -= chunk.Offset;

    if( !TryMergeBlocks( chunk ) )
    {
      m_FreeMemoryChunks.Add( chunk );
    }
  }
}

nfe::uint64 nfe::BlockAllocator::FindFirstFitBlock( uint64 size )
{
  uint64 idx = 0;
  uint64 firstIdx = -1;
  for( auto chunk : m_FreeMemoryChunks )
  {
    if (chunk.Size >= size)
    {
      firstIdx = idx;
      break;
    }
    idx++;
  }

  return idx;
}

nfe::uint64 nfe::BlockAllocator::FindBestFitBlock( uint64 size )
{
  uint64 bestidx = -1;
  uint64 idx = 0;
  for( auto chunk : m_FreeMemoryChunks )
  {
    if( chunk.Size >= size )
    {
      if (bestidx != -1)
      {
        if (m_FreeMemoryChunks[bestidx] > chunk)
        {
          bestidx = idx;
        }
      }
      else
      {
        bestidx = idx;
      }
    }
    idx++;
  }

  return bestidx;
}

nfe::uint64 nfe::BlockAllocator::FindWorstFitBlock( uint64 size )
{

  uint64 worstIdx = -1;
  uint64 idx = 0;
  for( auto chunk : m_FreeMemoryChunks )
  {
    if( chunk.Size >= size )
    {
      if( worstIdx != -1 )
      {
        if( m_FreeMemoryChunks[ worstIdx ] < chunk )
        {
          worstIdx = idx;
        }
      }
      else
      {
        worstIdx = idx;
      }
    }
    idx++;
  }

  return worstIdx;
}

void nfe::BlockAllocator::SplitBlock(uint64 size, BlockAllocatorChunk& firstHalf, BlockAllocatorChunk& secondHalf )
{
  if (firstHalf.Size == size)
  {
    secondHalf.Pointer = nullptr;
  }
  else
  {
    uint64 originalSize = firstHalf.Size;
    firstHalf.Size = size;
    firstHalf.CalculateEndAddress();
    secondHalf.Pointer = firstHalf.EndAddress;
    secondHalf.Size = originalSize - size;
    secondHalf.Offset = 0;
    secondHalf.CalculateEndAddress();
  }
}

bool nfe::BlockAllocator::TryMergeBlocks( const BlockAllocatorChunk& mergeChunk )
{
  uint64 preAllocatorIdx = -1;
  uint64 postAllocatorIdx = -1;
  uint64 idx = 0;
  for( auto& chunk : m_FreeMemoryChunks )
  {
    if( chunk.EndAddress == mergeChunk.Pointer )
    {
      preAllocatorIdx = idx;
      if( postAllocatorIdx != -1 )
      {
        break;
      }
    }
    else if( chunk.Pointer == mergeChunk.EndAddress )
    {
      postAllocatorIdx = idx;
      if( preAllocatorIdx != -1 )
      {
        break;
      }
    }
    idx++;
  }

  if (preAllocatorIdx != -1)
  {
    if (postAllocatorIdx != -1)
    {
      BlockAllocatorChunk& preBlock = m_FreeMemoryChunks[ preAllocatorIdx ];
      preBlock.Size += mergeChunk.Size + m_FreeMemoryChunks[ postAllocatorIdx ].Size;
      preBlock.CalculateEndAddress();

      m_FreeMemoryChunks.RemoveAt( postAllocatorIdx );
      return true;
    }
    else
    {
      BlockAllocatorChunk& preBlock = m_FreeMemoryChunks[ preAllocatorIdx ];
      preBlock.Size += mergeChunk.Size;
      preBlock.CalculateEndAddress();
      return true;
    }
  }
  else if (postAllocatorIdx != -1)
  {
    BlockAllocatorChunk& postBlock = m_FreeMemoryChunks[ postAllocatorIdx ];
    postBlock.Pointer = mergeChunk.Pointer;
    postBlock.Size += mergeChunk.Size;
    postBlock.CalculateEndAddress();

    return true;
  }

  return false;
}

bool nfe::BlockAllocatorChunk::operator==( const BlockAllocatorChunk& chunk ) const
{
  return Pointer == chunk.Pointer && Size == chunk.Size;
}

void nfe::BlockAllocatorChunk::CalculateEndAddress()
{
  EndAddress = Pointer + Size;
}

bool nfe::BlockAllocatorChunk::operator<=( const BlockAllocatorChunk& chunk ) const
{
  return Size <= chunk.Size;
}

bool nfe::BlockAllocatorChunk::operator>=( const BlockAllocatorChunk& chunk ) const
{
  return Size >= chunk.Size;
}

bool nfe::BlockAllocatorChunk::operator<( const BlockAllocatorChunk& chunk ) const
{
  return Size < chunk.Size;

}

bool nfe::BlockAllocatorChunk::operator>( const BlockAllocatorChunk& chunk ) const
{
  return Size > chunk.Size;

}

bool nfe::BlockAllocatorChunk::Valid()
{
  return Pointer != nullptr;
}
