// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.hpp"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>
#include <d3d11.h>
#include <dxgi.h>
#include <DXGI1_2.h>
#include "NFEnginePCH.hpp"

#ifndef SAFE_RELEASE
#define SAFE_RELEASE( p ) { if( p ) { ( p )->Release(); ( p ) = NULL; } }
#endif


// TODO: reference additional headers your program requires here
