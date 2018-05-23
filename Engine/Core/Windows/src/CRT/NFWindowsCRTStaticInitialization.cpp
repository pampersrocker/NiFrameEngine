#include "NFWindowsPCH.hpp"



typedef int (*InitializerWithReturnFunctionPointer)(void);
typedef void (*InitializerFunctionPointer)(void);

#pragma section(".CRT$XCA",    long, read) // First C++ Initializer
#pragma section(".CRT$XCZ",    long, read) // Last C++ Initializer

#pragma section(".CRT$XIA",    long, read) // First C Initializer
#pragma section(".CRT$XIZ",    long, read) // Last C Initializer

#pragma section(".CRT$XPA",    long, read) // First Pre-Terminator
#pragma section(".CRT$XPZ",    long, read) // Last Pre-Terminator

#pragma section(".CRT$XTA",    long, read) // First Terminator
#pragma section(".CRT$XTZ",    long, read) // Last Terminator


extern "C" CRTALLOCATION(".CRT$XIA") InitializerWithReturnFunctionPointer __xi_a[] = { nullptr }; // C initializers (first)
extern "C" CRTALLOCATION(".CRT$XIZ") InitializerWithReturnFunctionPointer __xi_z[] = { nullptr }; // C initializers (last)

extern "C" CRTALLOCATION(".CRT$XCA") InitializerFunctionPointer __xc_a[] = { nullptr }; // C++ initializers (first)
extern "C" CRTALLOCATION(".CRT$XCZ") InitializerFunctionPointer __xc_z[] = { nullptr }; // C++ initializers (last)

extern "C" CRTALLOCATION(".CRT$XPA") InitializerFunctionPointer __xp_a[] = { nullptr }; // C pre-terminators (first)
extern "C" CRTALLOCATION(".CRT$XPZ") InitializerFunctionPointer __xp_z[] = { nullptr }; // C pre-terminators (last)

extern "C" CRTALLOCATION(".CRT$XTA") InitializerFunctionPointer __xt_a[] = { nullptr }; // C terminators (first)
extern "C" CRTALLOCATION(".CRT$XTZ") InitializerFunctionPointer __xt_z[] = { nullptr }; // C terminators (last)

#pragma comment(linker, "/merge:.CRT=.rdata")


int ExecuteFunctionList(InitializerWithReturnFunctionPointer* Start, InitializerWithReturnFunctionPointer* End)
{
  int Result = 0;

  while (Start < End && Result == 0)
  {
    if (*Start != nullptr)
    {
      Result = (**Start)();
    }
    ++Start;
  }
  return Result;
}

void ExecuteFunctionList(InitializerFunctionPointer* Start, InitializerFunctionPointer* End)
{
  while (Start < End)
  {
    if (*Start != nullptr)
    {
      (**Start)();
    }
    ++Start;
  }
}

void InitializeStaticInitializers()
{
  ExecuteFunctionList(__xi_a, __xi_z);
  ExecuteFunctionList(__xc_a, __xc_z);
}

void ShutdownStaticInitializers()
{
  ExecuteFunctionList(__xp_a, __xp_z);
  ExecuteFunctionList(__xp_a, __xp_z);

}

