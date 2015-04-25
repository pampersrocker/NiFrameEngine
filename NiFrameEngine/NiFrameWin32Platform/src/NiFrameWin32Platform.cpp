// NiFrameWin32Platform.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "NiFrameWin32Platform.h"
#include <NFWin32NativeModule.hpp>


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
