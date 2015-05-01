#include "stdafx.hpp"
#include "NFD3D11Device.hpp"
#include <Renderer/NFMesh.hpp>
#include <Renderer/NFRenderDeviceParameters.hpp>
#include <NFArrayUtils.hpp>
#include "NiFrameWin32Platform.h"


namespace nfe
{

  NFD3D11Device::NFD3D11Device() :
    m_Device( nullptr ),
    m_Context( nullptr )
  {

  }

  NFD3D11Device::~NFD3D11Device()
  {

  }

  void NFD3D11Device::Release()
  {
    m_Context->ClearState();

    SAFE_RELEASE( m_Context );
    SAFE_RELEASE( m_Device );
  }

  void NFD3D11Device::Initialize()
  {
  }

  const uint32 NFD3D11Device::GetDeviceCount( void ) const
  {
    throw std::exception( "The method or operation is not implemented." );
  }

  String NFD3D11Device::GetDeviceName( uint32 id ) const
  {
    throw std::exception( "The method or operation is not implemented." );
  }

  void NFD3D11Device::SetCurrentDeviceID( uint32 id )
  {
    throw std::exception( "The method or operation is not implemented." );
  }

  const uint32 NFD3D11Device::GetCurrentDeviceID( void ) const
  {
    throw std::exception( "The method or operation is not implemented." );
  }

  void NFD3D11Device::Clear( bool clearPixel, bool clearDepth )
  {
    throw std::exception( "The method or operation is not implemented." );
  }

  void NFD3D11Device::SetupDevice( const RenderWindow& mainWindow, const RenderDeviceParams& renderDeviceParameters )
  {
    HWND windowHandle = mainWindow.GetNativeHandle();

    D3D_FEATURE_LEVEL featureLevel;

    D3D_FEATURE_LEVEL featureLevels[] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_11_1 };

    HRESULT hr;

    hr = D3D11CreateDevice(
      nullptr,
      D3D_DRIVER_TYPE_HARDWARE,
      nullptr,
      0,
      featureLevels,
      arraySize(featureLevels),
      D3D11_SDK_VERSION,
      &m_Device,
      &featureLevel,
      &m_Context);

    NF_ASSERT_HR( hr );

    IDXGIDevice * pDXGIDevice;
    hr = m_Device->QueryInterface( __uuidof( IDXGIDevice ), reinterpret_cast<void ** >(&pDXGIDevice) );
    NF_ASSERT_HR( hr );

    IDXGIAdapter * pDXGIAdapter;
    hr = pDXGIDevice->GetParent( __uuidof( IDXGIAdapter ), reinterpret_cast<void ** >(&pDXGIAdapter) );
    NF_ASSERT_HR( hr );

    IDXGIFactory * pIDXGIFactory;
    hr = pDXGIAdapter->GetParent( __uuidof( IDXGIFactory ), reinterpret_cast<void ** >(&pIDXGIFactory) );
    NF_ASSERT_HR( hr );

  }

  const RenderDeviceParams& NFD3D11Device::GetRenderParams( void ) const
  {
    throw std::exception( "The method or operation is not implemented." );
  }

}
