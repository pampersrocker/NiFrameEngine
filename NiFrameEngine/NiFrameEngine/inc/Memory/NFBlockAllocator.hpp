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

    void CalculateEndAddress();

    bool Valid();

    bool operator ==( const BlockAllocatorChunk& chunk ) const;
    bool operator <= ( const BlockAllocatorChunk& chunk ) const;
    bool operator >= ( const BlockAllocatorChunk& chunk ) const;
    bool operator < ( const BlockAllocatorChunk& chunk ) const;
    bool operator > ( const BlockAllocatorChunk& chunk ) const;

  };

  class NIFRAME_DLL_EXPORT BlockAllocator : IAllocator
  {
  public:
    BlockAllocator(
      const char* name = "NFBlockAllocator",
      uint32 alignment = 4U,
      BlockAllocatorType allocationType = BlockAllocatorType::FirstFit,
      uint64 initialAllocationSize = 0U,
      IAllocator* parentAllocator = nullptr);
    virtual ~BlockAllocator();

    nfe::BlockAllocatorType GetAllocatorType() const;
    void SetAllocatorType( nfe::BlockAllocatorType val );

    virtual void* Allocate( uint64 size ) override;

    virtual void Deallocate( void* address ) override;


  private:

    uint64 FindFirstFitBlock( uint64 size );
    uint64 FindBestFitBlock( uint64 size );
    uint64 FindWorstFitBlock( uint64 size );

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
