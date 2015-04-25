#pragma once

#include "NFEnginePCH.hpp"

namespace nfe
{
  class NativeModule;
  class IPlatform
  {
  public:

    NativeModule* LoadModule(const char* modulePath);

  private:

  };

  extern IPlatform* GPlatform;
}
