#pragma once
#ifndef NiFrameRenderDevice_h__
#define NiFrameRenderDevice_h__

#include "NiFrameEnginePCH.h"

namespace NiFrame
{
	class RenderDeviceParams;

	typedef map< String, uint32>::type SelectedRenderDevVals;

	class NIFRAME_DLL_EXPORT RenderDevice
	{
	public:

		virtual void SetupDevice( 
			HWND hMainWindow, 
			const map< String, uint32 >::type& renderDeviceParameters , 
			bool log = true ) = 0;

		virtual void Initialize() = 0;

		virtual const RenderDeviceParams* GetRenderParams( void ) const = 0;

		virtual bool IsRunning() const = 0;

		virtual void UseWindow( int numWindow ) = 0;

		virtual void BeginRendering() = 0;

		virtual void EndRendering() = 0;

		virtual void Clear( bool clearPixel , bool clearDepth ) = 0;

		virtual ~RenderDevice() = 0;


	private:

	};

	
}

extern "C"
{
	HRESULT __declspec( dllexport ) CreateRenderDevice(HINSTANCE hdll, NiFrame::RenderDevice** renderDevice);
	typedef HRESULT (*CREATERENDERDEVICE)(HINSTANCE hdll, NiFrame::RenderDevice** renderDevice);

	HRESULT __declspec( dllexport ) ReleaseRenderDevice( NiFrame::RenderDevice** renderDevice);
	typedef HRESULT (*RELEASERENDERDEVICE)( NiFrame::RenderDevice** renderDevice);
};

#endif // NiFrameRenderDevice_h__

