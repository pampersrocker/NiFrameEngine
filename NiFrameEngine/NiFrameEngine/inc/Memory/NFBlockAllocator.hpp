#pragma once

#include "NFEnginePCH.hpp"
#include "NFIAllocator.hpp"
#include <NFSTL/NFVector.hpp>

namespace nfe
{

  enum class BlockAllocatorType
  {
    None,
    FirstFit,
    BestFit,
    WorstFit
  };

  struct NIFRAME_DLL_EXPORT BlockAllocatorChunk
  {
    uint8* Pointer;
    uint8* EndAddress;
    uint64 Size;
    uint32 Offset;

    void CalculateEndAddress();

    bool Valid();

    bool operator ==( const BlockAllocatorChunk& chunk ) const;
    bool operator <= ( const BlockAllocatorChunk& chunk ) const;
    bool operator >= ( const BlockAllocatorChunk& chunk ) const;
    bool operator < ( const BlockAllocatorChunk& chunk ) const;
    bool operator > ( const BlockAllocatorChunk& chunk ) const;

  };


  /**
  @brief Implements an allocator which subdivides a given chunk of memory into smaller chunks of arbitrary size,
  respecting the given alignment.
  When the pre-allocated size is full a new chunk of memory is requested from the parentAllocator

  This allocator has 3 different Types how the chunks will be chosen on an allocation:
  * FirstFit The first free block of memory which is found will be split and used
  * BestFit the smallest possible free chunk available will be split and used
  * WorstFit the biggest chunk available will be split and used
  */
  class NIFRAME_DLL_EXPORT BlockAllocator : public IAllocator
  {
  public:

    /**
    @brief Creates a new block allocator which can optionally pre allocate a chunk of memory on which the blocks will be created.


    @param const char * name The name of the allocator (for debugging)
    @param uint32 alignment The default alignment of the allocates blocks.
    @param BlockAllocatorType allocationType The behaviour how the free blocks will be chosen for a new allocation
    @param uint64 initialAllocationSize The initial chunk of memory which will be allocated from the parent allocator
    @param IAllocator * parentAllocator The parent allocator used for chunk allocation
    @param IAllocator * internalAllocator Allocator used for internal allocator allocations, if not set will be the same as parentAllocator
    */
    BlockAllocator(
      const char* name = "NFBlockAllocator",
      uint32 alignment = 4U,
      BlockAllocatorType allocationType = BlockAllocatorType::FirstFit,
      uint64 initialAllocationSize = 0U,
      IAllocator* parentAllocator = nullptr,
      IAllocator* internalAllocator = nullptr);
    virtual ~BlockAllocator();

    nfe::BlockAllocatorType GetAllocatorType() const;
    void SetAllocatorType( nfe::BlockAllocatorType val );

    virtual void* Allocate( uint64 size, uint32 alignment = 0 ) override;

    virtual void Deallocate( void* address ) override;


  private:
    // Different implementations for the allocator algorithm
    uint64 FindFirstFitBlock( uint64 size );
    uint64 FindBestFitBlock( uint64 size );
    uint64 FindWorstFitBlock( uint64 size );

    /**
    @brief Tries to merge the given chunk with the preceding or follow up block if those are free as well,
    creating one larger block.
    */
    bool TryMergeBlocks( const BlockAllocatorChunk& chunk );

    /**
    @brief Splits the firstHalf into two blocks if there is space left for a second block, otherwise the secondHalf is set to nullptr

    It is expected that the firstHalf has enough memory for the size

    @param size The size of needed chunk
    @param BlockAllocatorChunk & firstHalf Serves first a input of the block to split, will be modified if the block needs to be splitted
    @param BlockAllocatorChunk & secondHalf Output if the block is splitted, otherwise set to nullptr
    */
    void SplitBlock( uint64 size, BlockAllocatorChunk& firstHalf, BlockAllocatorChunk& secondHalf );

    uint32 m_Alignment;

    IAllocator* m_ParentAllocator;
    BlockAllocatorType m_AllocatorType;
    Vector<BlockAllocatorChunk> m_AllocatedBlocks;
    Vector<BlockAllocatorChunk> m_FreeMemoryChunks;
    Vector<BlockAllocatorChunk> m_UsedMemoryChunks;
  };

}
