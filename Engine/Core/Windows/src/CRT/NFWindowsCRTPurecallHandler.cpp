#include "NFWindowsPCH.hpp"


int _purecall()
{
  ::nfe::Platform::DebugBreak();

  return 0;
}
