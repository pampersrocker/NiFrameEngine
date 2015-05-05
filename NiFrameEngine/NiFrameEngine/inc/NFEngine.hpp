#pragma once
#include "Memory/NFIAllocator.hpp"
#include "NFSTL/NFVector.hpp"

namespace nfe
{
  class Engine
  {
  public:
    Engine();
    ~Engine();

    IAllocator* GetDefaultAllocator() const;

    void Shutdown();

  private:

    IAllocator* m_DefaultAllocator;
    Vector < int > test;

  };

  extern Engine* GEngine;

}
