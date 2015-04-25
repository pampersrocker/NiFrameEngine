#pragma once

#include "NFEnginePCH.hpp"

namespace nfe
{
  class IPlatform;
  class PlatformManager
  {
  public:

    static void SetPlatform( IPlatform* platform );

    static IPlatform* GetPlatform();

  private:

    static IPlatform* m_Platform;
  };


}
