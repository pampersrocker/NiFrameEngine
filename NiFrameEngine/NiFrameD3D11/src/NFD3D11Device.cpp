#include "stdafx.hpp"
#include "NFD3D11Device.hpp"
#include <Renderer/NFMesh.hpp>
#include <Renderer/NFRenderDeviceParameters.hpp>


namespace nfe
{

  NFD3D11Device::NFD3D11Device()
  {

  }

  NFD3D11Device::~NFD3D11Device()
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

  void NFD3D11Device::Initialize()
  {
    throw std::exception( "The method or operation is not implemented." );
  }

  void NFD3D11Device::SetupDevice( const RenderWindow& mainWindow, const RenderDeviceParams& renderDeviceParameters )
  {
    throw std::exception( "The method or operation is not implemented." );
  }

  const RenderDeviceParams& NFD3D11Device::GetRenderParams( void ) const
  {
    throw std::exception( "The method or operation is not implemented." );
  }


}
