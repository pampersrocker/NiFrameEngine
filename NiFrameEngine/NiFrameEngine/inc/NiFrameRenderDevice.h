#pragma once
#ifndef NiFrameRenderDevice_h__
#define NiFrameRenderDevice_h__

#include "NiFrameEnginePCH.h"

namespace NiFrame
{
	class NiFrameRenderDeviceParams;

	class NIFRAME_DLL_EXPORT NiFrameRenderDevice
	{
	public:

		virtual void SetupDevice( 
			HWND hMainWindow, 
			const vector<HWND*>::type& renderWindows, 
			int minDepth, 
			int minStencil, 
			const map< String, uint32 >::type& renderDeviceParameters , 
			bool log = true ) = 0;

		virtual void Initialize() = 0;

		virtual NiFrameRenderDeviceParams GetRenderParams( void ) const = 0;

		virtual bool IsRunning() const = 0;

		virtual void UseWindow( int numWindow ) = 0;

		virtual void BeginRendering() = 0;

		virtual void EndRendering() = 0;

		virtual void Clear( bool clearPixel , bool clearDepth ) = 0;


	private:

	};
}

extern "C"
{
	HRESULT __declspec( dllexport ) CreateRenderDevice(HINSTANCE hdll, NiFrame::NiFrameRenderDevice** renderDevice);
	typedef HRESULT (*CREATERENDERDEVICE)(HINSTANCE hdll, NiFrame::NiFrameRenderDevice** renderDevice);

	HRESULT __declspec( dllexport ) ReleaseRenderDevice( NiFrame::NiFrameRenderDevice** renderDevice);
	typedef HRESULT (*RELEASERENDERDEVICE)( NiFrame::NiFrameRenderDevice** renderDevice);
};

#endif // NiFrameRenderDevice_h__

