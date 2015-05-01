// NiFrameWin32Platform.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "NiFrameWin32Platform.h"
#include <NFWin32NativeModule.hpp>

using namespace nfe;
// This is the constructor of a class that has been exported.
// see NiFrameWin32Platform.h for the class definition
NiFrameWin32Platform::NiFrameWin32Platform()
{
}

nfe::INativeModule* NiFrameWin32Platform::LoadModule( const char* modulePath )
{
  HMODULE module = LoadLibraryEx( modulePath, nullptr, 0 );
  if( module )
  {
    return new NFWin32NativeModule( modulePath, module );
  }
  else
  {
    return nullptr;
  }
}

NiFrameWin32Platform::~NiFrameWin32Platform()
{

}

void NiFrameWin32Platform::ReleaseModule( nfe::INativeModule* module )
{
  NFWin32NativeModule* nativeModule = static_cast< NFWin32NativeModule* >( module );
  FreeLibrary( nativeModule->GetHMODULE() );
}

nfe::Resolution NiFrameWin32Platform::GetNativeResolution( uint32 monitorIdx ) const
{
  // Data struct for lambda-value passing
  struct MonitorCBData
  {
    HMONITOR monitor = nullptr;
    uint32 idx = 0;
    uint32 monitorIndex = 0;
  };
  MonitorCBData data;
  // Enumerate all monitors until we find our idx
  EnumDisplayMonitors(
    nullptr,
    nullptr,
    [](HMONITOR enumMonitor, HDC, LPRECT, LPARAM param) -> BOOL
    {
      // Because captured lambdas are not allowed we need to pass our data ... somehow
      MonitorCBData* data = reinterpret_cast<MonitorCBData* >(param);
      if( data->idx++ == data->monitorIndex )
      {
        data->monitor = enumMonitor;
        // Stop enumerating
        return false;
      }
      else
      {
        // Continue enumerating
        return true;
      }
    },
    reinterpret_cast<LPARAM>( &data ) );
  MONITORINFO monitorInfo;
  GetMonitorInfo( data.monitor, &monitorInfo );

  return Resolution( monitorInfo.rcMonitor.right - monitorInfo.rcMonitor.left, monitorInfo.rcMonitor.top - monitorInfo.rcMonitor.bottom, 0 );
}
