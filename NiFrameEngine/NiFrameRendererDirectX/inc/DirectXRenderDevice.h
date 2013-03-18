#pragma once
#include "NiFrameRendererPCH.h"
#include "NiFrameRenderDevice.h"
#include "NiFrameRenderDeviceParameters.h"

#ifndef DirectXRenderDevice_h__
#define DirectXRenderDevice_h__

namespace NiFrame
{
	class D3DResolution;
	class StringableBool;
	class D3DDevTypeStringable;
	class BufferTypeStringable;

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
		void LoadFullScreenSelection( RenderDeviceParameterList* paramList );
		void LoadMultiSamples( uint32 i, RenderDeviceParameterList* paramList );
		void LoadDeviceTypeSelection( uint32 i, RenderDeviceParameterList* paramList );
		void LoadBufferTypeSelection( uint32 i, RenderDeviceParameterList* paramList );
		void LoadZBufferTypeSelection( uint32 i, RenderDeviceParameterList* paramList );
		void LoadMultiSampleQualities( uint32 i, RenderDeviceParameterList* paramList );
	private:

		vector< D3DADAPTER_IDENTIFIER9 >::type* m_AdpaterIdentifier;
		HINSTANCE m_hDLL;
		IDirect3D9 * m_pD3D;
		vector< RenderDeviceParams* >::type m_AdapterParameters;
		vector< vector< D3DResolution* >::type*>::type* m_DeviceResolutions;
		vector< vector< StringableBool* >::type*>::type* m_FullScreen;
		vector< vector< D3DDevTypeStringable* >::type*>::type* m_D3DDevTypes;		
		vector< vector< BufferTypeStringable* >::type*>::type* m_BufferTypes;

	};
}

#endif // DirectXRenderDevice_h__