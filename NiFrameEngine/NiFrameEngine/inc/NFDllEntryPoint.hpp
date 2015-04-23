#pragma once
#ifndef DllEntryPoint_h__
#define DllEntryPoint_h__

#include "NFEnginePCH.hpp"

#ifdef WIN32

class DllEntryPoint
{
public:
  DllEntryPoint();
  ~DllEntryPoint();

  static void SetDLLInstance( HINSTANCE newInstance );

  static HINSTANCE GetInstance();

private:
  static HINSTANCE dllInstance;
};

#endif

#endif // DllEntryPoint_h__
