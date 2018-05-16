#include "NFEnginePCH.hpp"
#include "NFDllEntryPoint.hpp"

#ifdef WIN32

HINSTANCE DllEntryPoint::dllInstance = nullptr;

BOOL WINAPI DllMain(
  HINSTANCE hinstDLL,  // handle to DLL module
  DWORD fdwReason,     // reason for calling function
  LPVOID lpReserved )  // reserved
{
  // Perform actions based on the reason for calling.
  switch( fdwReason )
  {
  case DLL_PROCESS_ATTACH:
    // Initialize once for each new process.
    // Return FALSE to fail DLL load.
    DllEntryPoint::SetDLLInstance(hinstDLL);
    break;

  case DLL_THREAD_ATTACH:
    // Do thread-specific initialization.
    break;

  case DLL_THREAD_DETACH:
    // Do thread-specific cleanup.
    break;

  case DLL_PROCESS_DETACH:
    DllEntryPoint::SetDLLInstance(nullptr);
    // Perform any necessary cleanup.
    break;
  }
  return TRUE;  // Successful DLL_PROCESS_ATTACH.
}

void DllEntryPoint::SetDLLInstance( HINSTANCE newInstance )
{
  dllInstance = newInstance;
}

HINSTANCE DllEntryPoint::GetInstance()
{
  return dllInstance;
}
#endif
