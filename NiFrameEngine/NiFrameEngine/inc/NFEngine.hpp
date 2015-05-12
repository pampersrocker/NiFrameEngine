#pragma once
#include "Memory/NFIAllocator.hpp"
#include "NFSTL/NFVector.hpp"

namespace nfe
{
  class NIFRAME_DLL_EXPORT Engine
  {
  public:
    Engine();
    ~Engine();

    IAllocator* GetDefaultAllocator() const;

    void Run();

    void Shutdown();

  private:

    IAllocator* m_DefaultAllocator;

  };

  NIFRAME_DLL_EXPORT extern Engine* GEngine;

}
