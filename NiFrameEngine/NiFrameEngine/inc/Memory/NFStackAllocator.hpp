#pragma once

#include "NFEnginePCH.hpp"
#include "NFIAllocator.hpp"

namespace nfe
{

  class NIFRAME_API StackAllocator : public IAllocator
  {
  public:
    StackAllocator(uint64 size, uint32 alignment = sizeof(void*), IAllocator* parentAllocator = nullptr, const char* name = "NFStackAllocator");
    ~StackAllocator();

    virtual void* Allocate( uint64 size, uint32 alignment = 0 ) override;

    virtual void Deallocate( void* address ) override;

  private:

    uint64 m_Size;
    uint32 m_Alignment;
    IAllocator* m_ParentAllocator;
    uint8* m_Memory;
    uint8* m_CurrentMarker;
    uint8* m_LastAllocation;
  };

}
