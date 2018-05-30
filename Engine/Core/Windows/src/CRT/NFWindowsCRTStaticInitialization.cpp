#include "NFWindowsPCH.hpp"





#pragma section(".CRT$XCA",    long, read) // First C++ Initializer
#pragma section(".CRT$XCZ",    long, read) // Last C++ Initializer

#pragma section(".CRT$XIA",    long, read) // First C Initializer
#pragma section(".CRT$XIZ",    long, read) // Last C Initializer

#pragma section(".CRT$XPA",    long, read) // First Pre-Terminator
#pragma section(".CRT$XPZ",    long, read) // Last Pre-Terminator

#pragma section(".CRT$XTA",    long, read) // First Terminator
#pragma section(".CRT$XTZ",    long, read) // Last Terminator


extern "C" CRTALLOCATION(".CRT$XIA") InitializerWithReturnFunctionPointer CInitializerListStart[] = { nullptr }; // C initializers (first)
extern "C" CRTALLOCATION(".CRT$XIZ") InitializerWithReturnFunctionPointer CInitializerListEnd[] = { nullptr }; // C initializers (last)

extern "C" CRTALLOCATION(".CRT$XCA") InitializerFunctionPointer CPPInitializerListStart[] = { nullptr }; // C++ initializers (first)
extern "C" CRTALLOCATION(".CRT$XCZ") InitializerFunctionPointer CPPInitializerListEnd[] = { nullptr }; // C++ initializers (last)

extern "C" CRTALLOCATION(".CRT$XPA") InitializerFunctionPointer CPPTerminatorListStart[] = { nullptr }; // C pre-terminators (first)
extern "C" CRTALLOCATION(".CRT$XPZ") InitializerFunctionPointer CPPTerminatorListEnd[] = { nullptr }; // C pre-terminators (last)

extern "C" CRTALLOCATION(".CRT$XTA") InitializerFunctionPointer CTerminatorListStart[] = { nullptr }; // C terminators (first)
extern "C" CRTALLOCATION(".CRT$XTZ") InitializerFunctionPointer CTerminatorListEnd[] = { nullptr }; // C terminators (last)

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
  ExecuteFunctionList(CInitializerListStart, CInitializerListEnd);
  ExecuteFunctionList(CPPInitializerListStart, CPPInitializerListEnd);
}

void ShutdownStaticInitializers()
{
  ExecuteFunctionList(CPPTerminatorListStart, CPPTerminatorListEnd);
  ExecuteFunctionList(CPPTerminatorListStart, CPPTerminatorListEnd);
}

