#pragma once
#include "NiFrameRendererPCH.h"
#include "NiFrameRenderDevice.h"
#include "NiFrameRenderDeviceParameters.h"

#ifndef DirectXRenderDevice_h__
#define DirectXRenderDevice_h__

namespace NiFrame
{
	class D3DResolution;

	class D3DRenderDevice : public RenderDevice
	{
	public:
		D3DRenderDevice(HINSTANCE hDLL);
		~D3DRenderDevice();

		virtual void SetupDevice( HWND hMainWindow, const vector<HWND*>::type& renderWindows, int minDepth, int minStencil, const map< String, uint32 >::type& renderDeviceParameters, bool log = true );

		virtual void Initialize();

		void LoadDeviceResolutions( uint32 i, RenderDeviceParameterList* paramList );

		virtual RenderDeviceParams GetRenderParams( void ) const;

		virtual bool IsRunning() const;

		virtual void UseWindow( int numWindow );

		virtual void BeginRendering();

		virtual void EndRendering();

		virtual void Clear( bool clearPixel , bool clearDepth );

	private:

		vector< D3DADAPTER_IDENTIFIER9 >::type* m_AdpaterIdentifier;
		HINSTANCE m_hDLL;
		IDirect3D9 * m_pD3D;
		vector< RenderDeviceParams* >::type m_AdapterParameters;
		vector< vector< D3DResolution* >::type*>::type* m_DeviceResolutions;
	};
}

#endif // DirectXRenderDevice_h__