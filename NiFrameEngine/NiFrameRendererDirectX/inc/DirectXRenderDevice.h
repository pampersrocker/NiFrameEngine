#pragma once
#include "NiFrameRendererPCH.h"
#include "NiFrameRenderDevice.h"

#ifndef DirectXRenderDevice_h__
#define DirectXRenderDevice_h__

namespace NiFrame
{
	class NiFrameD3DRenderDevice : public NiFrameRenderDevice
	{
	public:
		NiFrameD3DRenderDevice(HINSTANCE hDLL);
		~NiFrameD3DRenderDevice();

		virtual void SetupDevice( HWND hMainWindow, const vector<HWND*>::type& renderWindows, int minDepth, int minStencil, const map< String, uint32 >::type& renderDeviceParameters, bool log = true );

		virtual void Initialize();

		virtual NiFrameRenderDeviceParams GetRenderParams( void ) const;

		virtual bool IsRunning() const;

		virtual void UseWindow( int numWindow );

		virtual void BeginRendering();

		virtual void EndRendering();

		virtual void Clear( bool clearPixel , bool clearDepth );
		HINSTANCE m_hDLL;
		IDirect3D9 * m_pD3D;
	private:

		int32 m_iNumAdapters;
		vector< D3DADAPTER_IDENTIFIER9 >::type* m_AdpaterIdentifier;
	};
}

#endif // DirectXRenderDevice_h__