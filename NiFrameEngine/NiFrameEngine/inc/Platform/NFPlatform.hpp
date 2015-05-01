#pragma once

#include "NFEnginePCH.hpp"
#include <Renderer/NFResolution.hpp>

namespace nfe
{
  class INativeModule;
  class NIFRAME_DLL_EXPORT IPlatform
  {
  public:
    virtual ~IPlatform() {}

    virtual INativeModule* LoadModule(const char* modulePath) = 0;
    virtual void ReleaseModule( INativeModule* module ) = 0;

    virtual Resolution GetNativeResolution( uint32 monitorIdx ) const = 0;

  private:

  };

  extern NIFRAME_DLL_EXPORT IPlatform* GPlatform;
}
