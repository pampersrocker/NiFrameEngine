#pragma once
#include "NFMacros.hpp"

#include "NFWindowsCommon.hpp"
#include "NFWindowsTypes.hpp"

#include "NFEnginePCH.hpp"

#define CRTALLOCATION(SectionName) __declspec(allocate(SectionName))
