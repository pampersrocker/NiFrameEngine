#pragma once


#include "NFPrerequisites.hpp"
namespace nfe
{
  class NIFRAME_API WindowsMemory
  {
  public:
    static void* Allocate(NFSize Size);
    static void Free(void* Address);
  };

  typedef WindowsMemory PlatformMemory;
}
