#pragma once

#include "NFEnginePCH.hpp"

namespace nfe
{
  enum class LogLevel : int32
  {
    Fatal,
    Error,
    Warning,
    Success,
    Log,
    Info,
    Debug
  };

  enum class LogVerbosity : int32
  {
    None,
    Fatal,
    Error,
    Warning,
    Success,
    Log,
    Info,
    Debug,
    All
  };

  class NIFRAME_API Logger
  {
  public:
    Logger();
    ~Logger();

  private:

  };
}
