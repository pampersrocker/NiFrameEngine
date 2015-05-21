#pragma once

#include "NFEnginePCH.hpp"
#include "NFSTL/NFVector.hpp"
#include "Memory/NFIAllocator.hpp"

namespace nfe
{

  struct ProxyAllocationInfo
  {

    uint8* Pointer;
    uint64 Size;
  };

  /**
  @brief This allocator just passes the allocation request through to the parentAllocator, it does not have any own allocation logic

  However it does track allocations and deallocation for debugging and statistic purpose.
  */
  class ProxyAllocator : public IAllocator
  {
  public:
    ProxyAllocator( IAllocator* parentAllocator = nullptr, const char* name = "NFProxyAllocator" );
    ~ProxyAllocator();

    /**
    @brief Returns detailed information of allocation which went through this allocator

    */
    Vector<ProxyAllocationInfo> AllocationInfos() const;

    virtual void* Allocate( uint64 size ) override;

    virtual void Deallocate( void* address ) override;

  private:
    IAllocator* m_ParentAllocator;
    Vector<ProxyAllocationInfo> m_AllocationInfos;
  };
}
