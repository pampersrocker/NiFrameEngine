#pragma once
#include "NFMacros.hpp"

#include "NFWindowsCommon.hpp"
#include "NFWindowsTypes.hpp"

#include "NFEnginePCH.hpp"

#define CRTALLOCATION(SectionName) __declspec(allocate(SectionName))

typedef int(*InitializerWithReturnFunctionPointer)(void);
typedef void(*InitializerFunctionPointer)(void);
typedef void(*AtExitFunctionPointer)(void);
