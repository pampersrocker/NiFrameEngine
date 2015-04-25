#pragma once

#include "NFEnginePCH.hpp"

namespace nfe
{
  class INativeModule;
  class IPlatform
  {
  public:
    virtual ~IPlatform() {}

    virtual INativeModule* LoadModule(const char* modulePath) = 0;
    virtual void ReleaseModule( INativeModule* module ) = 0;

  private:

  };

  extern NIFRAME_DLL_EXPORT IPlatform* GPlatform;
}
