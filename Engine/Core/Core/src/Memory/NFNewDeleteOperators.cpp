#include "NFEnginePCH.hpp"
#include "Memory\NFDefaultAllocator.hpp"



#if PLATFORM_WINDOWS
#pragma warning(push)
// This warning is about missing SAL annotations to the new operator, which I cannot find anywhere, as it is a compiler internal definition
#pragma warning(disable: 28251)
#endif

nfe::uint8 GlobalDefaultAllocatorMemory[sizeof(nfe::DefaultAllocator)];
nfe::DefaultAllocator* GlobalDefaultAllocator;

void nfe::InitializeGlobalDefaultAllocator()
{
  GlobalDefaultAllocator = new (GlobalDefaultAllocatorMemory) nfe::DefaultAllocator("Global Default Allocator");
}

void nfe::ShutdownGlobalDefaultAllocator()
{
  GlobalDefaultAllocator->~DefaultAllocator();
}


void* operator new(nfe::NFSize Size)
{
  return GlobalDefaultAllocator->Allocate(Size);
}

void* __cdecl operator new[](nfe::NFSize Size)
{
  return GlobalDefaultAllocator->Allocate(Size);
}

void __cdecl operator delete(void* Address, nfe::NFSize Size)
{
  GlobalDefaultAllocator->Deallocate(Address);
}

void __cdecl operator delete[](void* Address, nfe::NFSize Size)
{
  GlobalDefaultAllocator->Deallocate(Address);
}

#if PLATFORM_WINDOWS
#pragma warning(pop)
#endif
