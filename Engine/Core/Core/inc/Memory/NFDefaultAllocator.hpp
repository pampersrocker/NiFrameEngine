#pragma once
#include "NFEnginePCH.hpp"
#include "NFIAllocator.hpp"

namespace nfe
{
  /**
  @brief Implements a default Platform Allocator used for basic allocation
  */
  class NIFRAME_API DefaultAllocator : public IAllocator
  {
  public:
    DefaultAllocator( const char* name = "NFDefaultAllocator" );
    virtual ~DefaultAllocator();

    virtual void* Allocate( NFSize size, uint32 alignment = 0 ) override;

    virtual void Deallocate( void* address ) override;

  private:

  };

}
