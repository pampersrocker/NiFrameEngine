#pragma once
#include "NFEnginePCH.hpp"
#include "Platform/NFNativeModule.hpp"

class NIFRAME_API NFWin32NativeModule : public nfe::INativeModule
{
public:

  NFWin32NativeModule( const char* name, HMODULE module );

  virtual const nfe::String& GetName() const override;

  HMODULE GetHMODULE() const;

  virtual void* GetNativeModuleFunctionPointer( const char* name ) override;

private:

  nfe::String m_Name;
  HMODULE m_Module;


};
