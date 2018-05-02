#pragma once

#ifndef NiFrameEnginePCH_h__
#define NiFrameEnginePCH_h__

#pragma warning(disable : 4251)

#ifdef WIN32


#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:

#include <windows.h>

#endif // WIN32

#include <assert.h>

#include "NFMacros.hpp"

#include "NFPrerequisites.hpp"
#include "NFSTLTypes.hpp"
#include "NFSTL/NFVector.hpp"
#include "Memory/NFIAllocator.hpp"

#ifdef WIN32
#ifdef _DEBUG
#include "vld.h"
#endif // DEBUG


#endif // WIN32




// TODO: reference additional headers your program requires here

#endif // NiFrameEnginePCH_h__
