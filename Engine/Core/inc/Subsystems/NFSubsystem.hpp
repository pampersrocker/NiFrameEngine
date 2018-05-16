#pragma once

#include "NFEnginePCH.hpp"

namespace nfe
{
  class ISubsystem
  {
  public:

    inline ISubsystem()
    { }

    virtual void Initialize() = 0;
    virtual void Release() = 0;
    virtual void Update(Real elapsedTime) = 0;

  };
}
