#pragma once

#ifndef NiFrameEnginePCH_h__
#define NiFrameEnginePCH_h__

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>

#include <assert.h>

#ifdef NIFRAME_DLL_BUILD
#define NIFRAME_DLL_EXPORT __declspec( dllexport )
#else
#define NIFRAME_DLL_EXPORT __declspec( dllimport )
#endif




#define SAFE_DELETE(pointer)	\
	if( pointer != nullptr )	\
	{							\
		delete pointer;			\
		pointer = nullptr;		\
	}							\

#include "NiFramePrerequisites.h"
#include "NiFrameSTLTypes.h"

#ifdef _DEBUG
#include "vld.h"
#endif // DEBUG





// TODO: reference additional headers your program requires here

#endif // NiFrameEnginePCH_h__
