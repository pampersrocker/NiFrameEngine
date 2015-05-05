#include "stdafx.hpp"
#include "NFD3D11Device.hpp"
#include <Renderer/NFMesh.hpp>
#include <Renderer/NFRenderDeviceParameters.hpp>
#include <NFArrayUtils.hpp>
#include "NiFrameWin32Platform.h"
#include <NFSTL/NFVector.hpp>


namespace nfe
{

  NFD3D11Device::NFD3D11Device() :
    m_Device( nullptr ),
    m_Context( nullptr ),
    m_IDXGIFactory( nullptr ),
    m_DXGIAdapter( nullptr ),
    m_RenderDeviceAllocator( nullptr )
  {
    m_RenderDeviceAllocator = GetDefaultAllocator();
    m_TmpAllocator = GetDefaultAllocator();
  }

  NFD3D11Device::~NFD3D11Device()
  {

  }

  void NFD3D11Device::Release()
  {
    m_Context->ClearState();

    SAFE_RELEASE( m_SwapChain );
    SAFE_RELEASE( m_Context );
    SAFE_RELEASE( m_Device );
  }

  void NFD3D11Device::Initialize()
  {
    D3D_FEATURE_LEVEL featureLevel;

    D3D_FEATURE_LEVEL featureLevels [] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_11_1 };

    HRESULT hr;

    hr = D3D11CreateDevice(
      nullptr,
      D3D_DRIVER_TYPE_HARDWARE,
      nullptr,
      0,
      featureLevels,
      arraySize( featureLevels ),
      D3D11_SDK_VERSION,
      &m_Device,
      &featureLevel,
      &m_Context );
    NF_ASSERT_HR( hr );

    IDXGIDevice * pDXGIDevice;
    hr = m_Device->QueryInterface( __uuidof( IDXGIDevice ), reinterpret_cast< void ** >( &pDXGIDevice ) );
    NF_ASSERT_HR( hr );
    hr = pDXGIDevice->GetParent( __uuidof( IDXGIAdapter ), reinterpret_cast< void ** >( &m_DXGIAdapter ) );
    NF_ASSERT_HR( hr );
    hr = m_DXGIAdapter->GetParent( __uuidof( IDXGIFactory2 ), reinterpret_cast< void ** >( &m_IDXGIFactory ) );
    NF_ASSERT_HR( hr );
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
    m_Params = renderDeviceParameters;

    HWND windowHandle = mainWindow.GetNativeHandle();

    HRESULT hr;

    DXGI_SWAP_CHAIN_DESC1 swapChainDesc;
    swapChainDesc.BufferCount = renderDeviceParameters.TripleBuffering() ? 3 : 2;
    swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swapChainDesc.Width = mainWindow.GetResolution().GetWidth();
    swapChainDesc.Height = mainWindow.GetResolution().GetHeight();
    swapChainDesc.Format = DXGI_FORMAT_R8G8B8A8_UINT;
    swapChainDesc.AlphaMode = DXGI_ALPHA_MODE_IGNORE;
    swapChainDesc.SampleDesc.Count = renderDeviceParameters.MSAACount();
    swapChainDesc.SampleDesc.Quality = renderDeviceParameters.MSAAQuality();
    swapChainDesc.Stereo = false;
    swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
    swapChainDesc.Scaling = DXGI_SCALING_ASPECT_RATIO_STRETCH;

    DXGI_SWAP_CHAIN_FULLSCREEN_DESC fullscreenDesc;
    // TODO: Might set from device params once this is read from the actual device:
    // https://msdn.microsoft.com/en-us/library/windows/desktop/ee417025(v=vs.85).aspx#full-screen_issues
    fullscreenDesc.RefreshRate.Denominator = 0;
    fullscreenDesc.RefreshRate.Numerator = 0;
    fullscreenDesc.Scaling = DXGI_MODE_SCALING_CENTERED;
    // TODO: Fullscreen Windowed?
    fullscreenDesc.Windowed = false;

    hr = m_IDXGIFactory->CreateSwapChainForHwnd(
      m_Device,
      windowHandle,
      &swapChainDesc,
      &fullscreenDesc,
      nullptr,
      &m_SwapChain );
    NF_ASSERT_HR( hr );
  }

  const RenderDeviceParams& NFD3D11Device::GetRenderParams( void ) const
  {
    return m_Params;
  }

  nfe::Vector<Resolution> NFD3D11Device::GetSupportedResolutions()
  {
    IDXGIOutput* pOutput = nullptr;
    HRESULT hr;

    hr = m_DXGIAdapter->EnumOutputs( 0, &pOutput );

    UINT numModes = 0;
    DXGI_MODE_DESC* displayModes = nullptr;
    DXGI_FORMAT format = DXGI_FORMAT_R8G8B8A8_UINT;

    // Get the number of elements
    hr = pOutput->GetDisplayModeList( format, 0, &numModes, nullptr );

    displayModes = nfnewArray<DXGI_MODE_DESC>(numModes, m_TmpAllocator);

    // Get the list
    hr = pOutput->GetDisplayModeList( format, 0, &numModes, displayModes );

    Vector<Resolution> resolutions( numModes, m_RenderDeviceAllocator );

    for( uint64 idx = 0; idx < numModes; idx++ )
    {
      Resolution res(
        displayModes[ idx ].Width,
        displayModes[ idx ].Height,
        Rational( displayModes[ idx ].RefreshRate.Numerator, displayModes[ idx ].RefreshRate.Denominator ) );
      resolutions.Add( res );
    }

    nfdeleteArray(displayModes, m_TmpAllocator );

    return resolutions;
  }

}
