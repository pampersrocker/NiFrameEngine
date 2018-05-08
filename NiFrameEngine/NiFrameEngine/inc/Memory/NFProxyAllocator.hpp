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
  class NIFRAME_API ProxyAllocator : public IAllocator
  {
  public:
    ProxyAllocator( IAllocator* parentAllocator = nullptr, uint32 defaultAlignment = 0U, const char* name = "NFProxyAllocator" );
    ~ProxyAllocator();

    ProxyAllocator& operator =( const ProxyAllocator& rhs );

    /**
    @brief Returns detailed information of allocation which went through this allocator

    */
    Vector<ProxyAllocationInfo> AllocationInfos() const;

    virtual void* Allocate(NFSize size, uint32 alignment = 0 ) override;

    virtual void Deallocate( void* address ) override;

  private:
    IAllocator* m_ParentAllocator;
    Vector<ProxyAllocationInfo> m_AllocationInfos;
    uint32 m_DefaultAlignment;
  };
}
