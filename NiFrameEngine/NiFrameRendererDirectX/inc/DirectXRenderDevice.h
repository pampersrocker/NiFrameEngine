#pragma once
#include "NiFrameRendererPCH.h"
#include "NiFrameRenderDevice.h"
#include "NiFrameRenderDeviceParameters.h"
#include "SSEMatrix4x4.h"

#ifndef DirectXRenderDevice_h__
	#define DirectXRenderDevice_h__

namespace NiFrame
{
	class D3DResolution;
	class StringableBool;
	class D3DDevTypeStringable;
	class BufferTypeStringable;
	class D3DMultiSample;
	class D3DMultiSampleQuality;

	class D3DRenderDevice :
		public RenderDevice
	{
	public:

		D3DRenderDevice( HINSTANCE hDLL );
		~D3DRenderDevice();

		virtual void SetupDevice(
			HWND hMainWindow,
			const map< String, uint32 >::type& renderDeviceParameters,
			bool log = true );

		virtual void Initialize();

		virtual const RenderDeviceParams* GetRenderParams( void ) const;

		virtual bool IsRunning() const;

		virtual void UseWindow( int numWindow );

		virtual void BeginRendering();

		virtual void RenderMesh( Mesh* mesh );

		virtual void EndRendering();

		virtual void Clear( bool clearPixel, bool clearDepth );

		void CreateVertexBuffer( NFSize size, IDirect3DVertexBuffer9** buffer );

		void DestroyVertexBuffer( IDirect3DVertexBuffer9** vertexBuffer );

		void CreateIndexBuffer( NFSize size, IDirect3DIndexBuffer9** buffer );

		void DestroyIndexBuffer( IDirect3DIndexBuffer9** buffer );

		const String GetGetVideoModeID() const;

		const String GetGetBufferID() const;

		const String GetGetZBufferTypeID() const;

		const String GetGetWindowedID() const;

		const String GetGetMultisampleID() const;

		const String GetGetDeviceTypeID() const;

		const String GetGetMultisampleQualityID() const;

	private:
		LinearMath::SSEMatrix4x4 m_ProjectionMatrix;

		map< String, uint32 >::type* m_SelectedValues;

		const String DEVICE_TYPE;
		const String VIDEOMODE;
		const String BUFFERTYPE;
		const String ZBUFFERTYPE;
		const String WINDOWED;
		const String MULTISAMPLE_TYPE;
		const String MULTISAMPLE_QUALITY;

		_D3DDEVTYPE GetCurrentDevType();

		D3DFORMAT GetCurrentBufferFormat();

		bool GetWindowed();

		D3DMULTISAMPLE_TYPE GetCurrentMultiSampleType();

		uint32 m_CurrentDevice;

		vector< D3DADAPTER_IDENTIFIER9 >::type* m_AdpaterIdentifier;
		HINSTANCE m_hDLL;
		IDirect3D9* m_pD3D;
		IDirect3DDevice9* m_Device;

		D3DPRESENT_PARAMETERS m_Params;

		D3DXMATRIX m_D3DProjectionMatrix;

		vector< RenderDeviceParams* >::type m_AdapterParameters;
		vector< vector< D3DResolution* >::type* >::type* m_DeviceResolutions;
		vector< vector< StringableBool* >::type* >::type* m_Windowed;
		vector< vector< D3DDevTypeStringable* >::type* >::type* m_D3DDevTypes;
		vector< vector< BufferTypeStringable* >::type* >::type* m_BufferTypes;
		vector< vector< BufferTypeStringable* >::type* >::type* m_ZBufferTypes;
		vector< vector< D3DMultiSample* >::type* >::type* m_MultiSampleTypes;
		vector< vector< D3DMultiSampleQuality* >::type* >::type* m_MultiSampleQualities;

		void LoadDeviceResolutions( uint32 adapterID, RenderDeviceParameterList* paramList );

		void LoadFullScreenSelection( RenderDeviceParameterList* paramList );

		void LoadMultiSamples( uint32 adapterID, RenderDeviceParameterList* paramList );

		void LoadDeviceTypeSelection( uint32 adapterID, RenderDeviceParameterList* paramList );

		void LoadBufferTypeSelection( uint32 adapterID, RenderDeviceParameterList* paramList );

		void LoadZBufferTypeSelection( uint32 adapterID, RenderDeviceParameterList* paramList );

		void LoadMultiSampleQualities( uint32 adapterID, RenderDeviceParameterList* paramList );

		void FillBufferTypeVector( vector< D3DFORMAT >::type* vec );

		virtual Mesh* CreateMesh( VertexBuffer::type* vertexBuffer, IndexBuffer::type* indexBuffer ) override;

		virtual void DestroyMesh( Mesh* mesh) override;
	};
}

#endif	// DirectXRenderDevice_h__
