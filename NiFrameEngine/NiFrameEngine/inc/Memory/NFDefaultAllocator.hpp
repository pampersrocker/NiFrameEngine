#pragma once
#include "NFEnginePCH.hpp"
#include "NFIAllocator.hpp"

namespace nfe
{
  /**
  @brief Implements a default new/delete Allocator used for basic allocation
  */
  class NIFRAME_DLL_EXPORT DefaultAllocator : public IAllocator
  {
  public:
    DefaultAllocator( const char* name = "NFDefaultAllocator" );
    virtual ~DefaultAllocator();

    virtual void* Allocate( uint64 size ) override;

    virtual void Deallocate( void* address ) override;

  private:

  };

}
