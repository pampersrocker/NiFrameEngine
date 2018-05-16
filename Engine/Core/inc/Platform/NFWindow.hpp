#pragma once

#include "NFEnginePCH.hpp"
#include "Renderer/NFResolution.hpp"

#if PLATFORM_WINDOWS
#include "Windows/NFWindowsWindow.hpp"
#elif PLATFOMR_PS4
#include "PS4/NFPS4Window.hpp"
#endif
