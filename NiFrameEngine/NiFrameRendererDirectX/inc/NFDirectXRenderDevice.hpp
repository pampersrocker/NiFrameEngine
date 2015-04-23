#pragma once
#include "NFRendererPCH.hpp"
#include "NFRenderDevice.hpp"
#include "NFRenderDeviceParameters.hpp"
#include <LinearMath/SSEMatrix4x4.hpp>

#ifndef DirectXRenderDevice_h__
  #define DirectXRenderDevice_h__

namespace nfe
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
      const map< String, uint32 >& renderDeviceParameters,
      bool log = true );

    virtual void Initialize();

    virtual const RenderDeviceParams* GetRenderParams( void ) const;

    virtual void BeginRendering();

    virtual void RenderMesh( MeshPtr mesh );

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

    virtual const uint32 GetCurrentDeviceID( void ) const override;

    virtual void SetCurrentDeviceID( uint32 id ) override;

    virtual const uint32 GetDeviceCount( void ) const override;

    virtual String GetDeviceName( uint32 id ) const override;
    
    virtual MeshPtr CreateMesh( VertexBuffer* vertexBuffer, IndexBuffer* indexBuffer ) override;

    virtual void DestroyMesh( MeshPtr mesh) override;

  private:
    LinearMath::SSEMatrix4x4 m_ProjectionMatrix;

    map< String, uint32 >* m_SelectedValues;

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

    vector< D3DADAPTER_IDENTIFIER9 >* m_AdpaterIdentifier;
    HINSTANCE m_hDLL;
    IDirect3D9* m_pD3D;
    IDirect3DDevice9* m_Device;

    D3DPRESENT_PARAMETERS m_Params;

    D3DXMATRIX m_D3DProjectionMatrix;

    vector< RenderDeviceParams* > m_AdapterParameters;
    vector< vector< D3DResolution* >* >* m_DeviceResolutions;
    vector< vector< StringableBool* >* >* m_Windowed;
    vector< vector< D3DDevTypeStringable* >* >* m_D3DDevTypes;
    vector< vector< BufferTypeStringable* >* >* m_BufferTypes;
    vector< vector< BufferTypeStringable* >* >* m_ZBufferTypes;
    vector< vector< D3DMultiSample* >* >* m_MultiSampleTypes;
    vector< vector< D3DMultiSampleQuality* >* >* m_MultiSampleQualities;

    void LoadDeviceResolutions( uint32 adapterID, RenderDeviceParameterList* paramList );

    void LoadFullScreenSelection( RenderDeviceParameterList* paramList );

    void LoadMultiSamples( uint32 adapterID, RenderDeviceParameterList* paramList );

    void LoadDeviceTypeSelection( uint32 adapterID, RenderDeviceParameterList* paramList );

    void LoadBufferTypeSelection( uint32 adapterID, RenderDeviceParameterList* paramList );

    void LoadZBufferTypeSelection( uint32 adapterID, RenderDeviceParameterList* paramList );

    void LoadMultiSampleQualities( uint32 adapterID, RenderDeviceParameterList* paramList );

    void FillBufferTypeVector( vector< D3DFORMAT >* vec );



  };
}

#endif  // DirectXRenderDevice_h__
