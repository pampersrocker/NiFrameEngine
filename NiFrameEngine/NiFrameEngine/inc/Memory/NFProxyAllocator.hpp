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

  class ProxyAllocator : public IAllocator
  {
  public:
    ProxyAllocator( IAllocator* parentAllocator = nullptr, const char* name = "NFProxyAllocator" );
    ~ProxyAllocator();

    Vector<ProxyAllocationInfo> AllocationInfos() const;

    virtual void* Allocate( uint64 size ) override;

    virtual void Deallocate( void* address ) override;

  private:
    IAllocator* m_ParentAllocator;
    Vector<ProxyAllocationInfo> m_AllocationInfos;
  };
}
