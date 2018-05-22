#pragma once
#ifndef NiFrameRenderDevice_h__
#define NiFrameRenderDevice_h__

#include "NFEnginePCH.hpp"
#include "NFMesh.hpp"
#include "NFSTL/NFVector.hpp"

namespace nfe
{
  class RenderDeviceParams;
  class Shader;

  class NIFRAME_API RenderDevice
  {
  public:

    virtual void SetupDevice(
      const RenderDeviceParams& renderDeviceParameters ) = 0;

    virtual void Initialize() = 0;

    virtual void Release() = 0;

    virtual Vector<Resolution> GetSupportedResolutions() = 0;

    virtual const RenderDeviceParams& GetRenderParams( void ) const = 0;

    virtual void Clear( bool clearPixel , bool clearDepth ) = 0;

    virtual const uint32 GetCurrentDeviceID( void ) const = 0;
    virtual void SetCurrentDeviceID( uint32 id ) = 0;

    virtual String GetDeviceName( uint32 id ) const = 0;

    virtual const uint32 GetDeviceCount( void ) const = 0;

    virtual ~RenderDevice() = 0;


  private:

  };


}
extern "C"
{
  void __declspec( dllexport ) CreateRenderDevice( nfe::RenderDevice** device );

  void __declspec( dllexport ) ReleaseRenderDevice( nfe::RenderDevice** renderDevice);
};

#endif // NiFrameRenderDevice_h__

