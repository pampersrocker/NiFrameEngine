#include "NFEnginePCH.hpp"
#include "Memory/NFBlockAllocator.hpp"
#include "Platform/NFPlatform.hpp"

using namespace nfe;
#if PLATFORM_X64
const NFSize INVALID_BLOCK_ID = 0xFFFFFFFFFFFFFFFF;
#else
const NFSize INVALID_BLOCK_ID = 0xFFFFFFFF;
#endif

nfe::BlockAllocator::BlockAllocator(
  const char* name /*= "NFBlockAllocator"*/,
  uint32 alignment,
  BlockAllocatorType allocationType /*= BlockAllocatorType::FirstFit*/,
  NFSize initialAllocationSize /*= 0U*/,
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
    NFSize alignedSize = ::nfe::alignedSize( initialAllocationSize, alignment );

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

void* nfe::BlockAllocator::Allocate(NFSize size, uint32 alignment )
{
  uint32 usedAlignment = alignment == 0 ? m_Alignment : alignment;
  // Add usedAlignment for the case we need to offset the allocation, so we have enough memory for the movement
  NFSize alignedSize = ::nfe::alignedSize( size, usedAlignment ) + usedAlignment + 4;
  NF_ASSERT( alignedSize > 0, "One cannot simply allocate a size of 0!" );
  if( alignedSize <= 0 )
  {
    return nullptr;
  }
  NFSize blockIdx = INVALID_BLOCK_ID;
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

  if (blockIdx == INVALID_BLOCK_ID)
  {
    NFSize newBlockSize = 0;

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
  Platform::OnAllocation( block.Pointer, alignedSize );
  uint8* address = (uint8*)block.Pointer;
  address -= block.Offset;
  address += block.Size - 4;
  address[ 0 ] = 0xBA;
  address[ 1 ] = 0xDF;
  address[ 2 ] = 0x00;
  address[ 3 ] = 0x0D;

  NF_ASSERT( reinterpret_cast< uintptr_t >( block.Pointer ) % usedAlignment == 0, "Failed to align block!" );
  return block.Pointer;
}

void nfe::BlockAllocator::Deallocate( void* InAddress )
{
  if(InAddress != nullptr )
  {
    NFSize idx = 0;
    for( auto& chunk : m_UsedMemoryChunks )
    {
      if( chunk.Pointer == InAddress)
      {
        break;
      }
      idx++;
    }

    NF_ASSERT( idx != m_UsedMemoryChunks.Size(), "Could not find Allocated Block" );


    BlockAllocatorChunk chunk = m_UsedMemoryChunks[ idx ];

    Platform::OnDeallocation( chunk.Pointer, chunk.Size );
    m_UsedMemoryChunks.RemoveAt( idx );
    chunk.Pointer -= chunk.Offset;
    chunk.Offset = 0;

    uint8* address = ( uint8* ) chunk.Pointer;
    address += chunk.Size - 4;
    NF_ASSERT( address[ 0 ] == 0xBA, "Heap corruption detected!" );
    NF_ASSERT( address[ 1 ] == 0xDF, "Heap corruption detected!" );
    NF_ASSERT( address[ 2 ] == 0x00, "Heap corruption detected!" );
    NF_ASSERT( address[ 3 ] == 0x0D, "Heap corruption detected!" );
    MemSet( chunk.Pointer, 0xFE, chunk.Size );
    if( !TryMergeBlocks( chunk ) )
    {
      m_FreeMemoryChunks.Add( chunk );
    }
  }
}

nfe::NFSize nfe::BlockAllocator::FindFirstFitBlock(NFSize size )
{
	NFSize idx = 0;
	NFSize firstIdx = INVALID_BLOCK_ID;
  for( auto chunk : m_FreeMemoryChunks )
  {
    if (chunk.Size >= size)
    {
      firstIdx = idx;
      break;
    }
    idx++;
  }

  return static_cast<NFSize>(firstIdx);
}

nfe::NFSize nfe::BlockAllocator::FindBestFitBlock(NFSize size )
{
	NFSize bestidx = INVALID_BLOCK_ID;
	NFSize idx = 0;
  for( auto chunk : m_FreeMemoryChunks )
  {
    if( chunk.Size >= size )
    {
      if (bestidx != INVALID_BLOCK_ID)
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

  return static_cast<NFSize>(bestidx);
}

nfe::NFSize nfe::BlockAllocator::FindWorstFitBlock(NFSize size )
{

	NFSize worstIdx = INVALID_BLOCK_ID;
	NFSize idx = 0;
  for( auto chunk : m_FreeMemoryChunks )
  {
    if( chunk.Size >= size )
    {
      if( worstIdx != INVALID_BLOCK_ID)
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

  return static_cast<NFSize>(worstIdx);
}

void nfe::BlockAllocator::SplitBlock(NFSize size, BlockAllocatorChunk& firstHalf, BlockAllocatorChunk& secondHalf )
{
  if (firstHalf.Size == size)
  {
    secondHalf.Pointer = nullptr;
  }
  else
  {
    NFSize originalSize = firstHalf.Size;
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
	NFSize preAllocatorIdx = INVALID_BLOCK_ID;
	NFSize postAllocatorIdx = INVALID_BLOCK_ID;
	NFSize idx = 0;
  for( auto& chunk : m_FreeMemoryChunks )
  {
    if( chunk.EndAddress == mergeChunk.Pointer )
    {
      preAllocatorIdx = idx;
      if( postAllocatorIdx != INVALID_BLOCK_ID)
      {
        break;
      }
    }
    else if( chunk.Pointer == mergeChunk.EndAddress )
    {
      postAllocatorIdx = idx;
      if( preAllocatorIdx != INVALID_BLOCK_ID)
      {
        break;
      }
    }
    idx++;
  }

  if (preAllocatorIdx != INVALID_BLOCK_ID)
  {
    if (postAllocatorIdx != INVALID_BLOCK_ID)
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
  else if (postAllocatorIdx != INVALID_BLOCK_ID)
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
