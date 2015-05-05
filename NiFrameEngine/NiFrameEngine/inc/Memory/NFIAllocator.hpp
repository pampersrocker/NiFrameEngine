#pragma once

#include "NFEnginePCH.hpp"

namespace nfe
{
  class NIFRAME_DLL_EXPORT IAllocator
  {
  public:
    IAllocator( const char* name );
    virtual ~IAllocator();

    virtual  void* Allocate( uint64 size ) = 0;
    virtual void Deallocate( void* address ) = 0;

    const char* GetName() const;
  private:

    const char* m_Name;

  };

}
