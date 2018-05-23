#pragma once


#if PLATFORM_WINDOWS
#include "NFWindowsMemory.hpp"
#else
#error "No memory implementation for this platform"
#endif
