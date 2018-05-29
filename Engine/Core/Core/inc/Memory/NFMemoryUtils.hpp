#pragma once
#include "NFPrerequisites.hpp"

namespace nfe
{
  void MemZero(void* Address, NFSize Size);
  void MemSet(void* Address, uint8 Value, NFSize Size);

  void InitializeGlobalDefaultAllocator();
  void ShutdownGlobalDefaultAllocator();
}

void * operator new (nfe::NFSize, void *Address);
void * operator new[](nfe::NFSize, void *Address);
