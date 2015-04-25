#include "stdafx.h"
#include "NFWin32NativeModule.hpp"



NFWin32NativeModule::NFWin32NativeModule( const char* name, HMODULE module ) :
m_Name( name ),
m_Module( module )
{

}

const nfe::String& NFWin32NativeModule::GetName() const
{
  return m_Name;
}

HMODULE NFWin32NativeModule::GetHMODULE() const
{
  return m_Module;
}

void* NFWin32NativeModule::GetNativeModuleFunctionPointer( const char* name )
{
  return static_cast< void* >( GetProcAddress( m_Module, name ) );
}
