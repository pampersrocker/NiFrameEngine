#include "NFWindowsPCH.hpp"
#include "NFPrerequisites.hpp"
#include "NFWindowsMemory.hpp"

void* nfe::WindowsMemory::Allocate(NFSize Size)
{
  void* const Allocation = VirtualAlloc(nullptr, Size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
  NF_ASSERT(Allocation, "Failed to allocate system memory");
  return Allocation;
}

void nfe::WindowsMemory::Free(void* Address)
{
  const bool Result = VirtualFree(Address, 0, MEM_RELEASE);
  NF_ASSERT(Result, "Failed to free system memory");
}
