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


    void Run();

    void Shutdown();

  private:

  };

  NIFRAME_DLL_EXPORT extern Engine* GEngine;

}
