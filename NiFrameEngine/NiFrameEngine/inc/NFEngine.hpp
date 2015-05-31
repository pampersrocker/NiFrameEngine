#pragma once
#include "Memory/NFIAllocator.hpp"
#include "NFSTL/NFVector.hpp"

namespace nfe
{
  class NIFRAME_API Engine
  {
  public:
    Engine();
    ~Engine();


    void Run();
    void Initialize();
    void Update();
    void Release();

    void Shutdown();

  private:

  };

  NIFRAME_API extern Engine* GEngine;

}
