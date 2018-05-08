#pragma once

#ifndef NiFrameEnginePCH_h__
#define NiFrameEnginePCH_h__

#pragma warning(disable : 4251)

#ifdef PLATFORM_WINDOWS


#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:

#include <windows.h>

#endif // PLATFORM_WINDOWS

#include <assert.h>

#include "NFMacros.hpp"

#include "NFPrerequisites.hpp"
#include "NFSTLTypes.hpp"
#include "NFSTL/NFVector.hpp"
#include "Memory/NFIAllocator.hpp"
#include "Memory/NFMemoryUtils.hpp"

#include "Platform/NFPlatform.hpp"

#endif // NiFrameEnginePCH_h__
