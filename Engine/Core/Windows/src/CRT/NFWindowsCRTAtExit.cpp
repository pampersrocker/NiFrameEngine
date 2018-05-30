#include "NFWindowsPCH.hpp"

const int MaxAtExitTable = 128;

int AtExitTableCount = 0;
AtExitFunctionPointer AtExitTable[128];

int _cdecl atexit(AtExitFunctionPointer AtExitFunction)
{
  // Todo we could dynamically allocate memory for the table, instead of using a fixed count, however this would require an initialization function
  NF_ASSERT(AtExitTableCount < MaxAtExitTable, "AtExit table is full, either reduce static variable count, or in crease the table size");

  // Only save valid pointers
  if (AtExitFunction)
  {
    AtExitTable[AtExitTableCount++] = AtExitFunction;
    return 0;
  }
  return -1;
}

void RunAtExitFunctions()
{
  for (int AtExitIndex = AtExitTableCount - 1; AtExitIndex >= 0; --AtExitIndex)
  {
    AtExitTable[AtExitIndex]();
  }
  AtExitTableCount = 0;
}
