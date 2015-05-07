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

  class BlockAllocator : IAllocator
  {
  public:
    BlockAllocator(
      const char* name = "NFBlockAllocator",
      BlockAllocatorType allocationType = BlockAllocatorType::FirstFit,
      uint64 initialAllocationSize = 0U,
      IAllocator* parentAllocator = nullptr);
    virtual ~BlockAllocator();

    nfe::BlockAllocatorType GetAllocatorType() const;
    void SetAllocatorType( nfe::BlockAllocatorType val );

    virtual void* Allocate( uint64 size ) override;

    virtual void Deallocate( void* address ) override;


  private:
    IAllocator* m_ParentAllocator;
    BlockAllocatorType m_AllocatorType;

    Vector<uint8*> m_MemoryChunks;
  };

}
