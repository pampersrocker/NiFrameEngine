#pragma once
#ifndef DllEntryPoint_h__
#define DllEntryPoint_h__

#include "NiFrameEnginePCH.h"

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

#endif // DllEntryPoint_h__