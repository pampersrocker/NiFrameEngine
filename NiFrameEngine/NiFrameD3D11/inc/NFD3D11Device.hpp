#pragma once

#include "stdafx.hpp"
#include "NiFrameD3D11.hpp"
#include <Renderer/NFRenderDevice.hpp>

namespace nfe
{

  class NIFRAMED3D11_API NFD3D11Device : public nfe::RenderDevice
  {
  public:
    NFD3D11Device();
    ~NFD3D11Device();

    virtual void Initialize() override;

    virtual void Clear( bool clearPixel, bool clearDepth ) override;

    virtual const uint32 GetCurrentDeviceID( void ) const override;

    virtual void SetCurrentDeviceID( uint32 id ) override;

    virtual String GetDeviceName( uint32 id ) const override;

    virtual const uint32 GetDeviceCount( void ) const override;

    virtual void SetupDevice( const RenderWindow& mainWindow, const RenderDeviceParams& renderDeviceParameters ) override;

    virtual const RenderDeviceParams& GetRenderParams( void ) const override;

  private:

  };

}
