#pragma once
#ifndef RenderDeviceParameters_h__
#define RenderDeviceParameters_h__

#include "NFEnginePCH.hpp"
#include "Renderer/NFResolution.hpp"

namespace nfe
{
  class IStringableObject;

  class NIFRAME_DLL_EXPORT RenderDeviceParams
  {

  public:

    void Initialize(
      const Resolution& interalResolution,
      bool fullScreen,
      bool tripleBuffering = false,
      uint32 msaaCount = 1,
      uint32 msaaQuality = 0
      );

    const nfe::Resolution& InternalResolution() const;
    void InternalResolution( nfe::Resolution val );
    bool FullScreen() const;
    void FullScreen( bool val );
    bool TripleBuffering() const;
    void TripleBuffering( bool val );
    nfe::uint32 MSAACount() const;
    void MSAACount( nfe::uint32 val );
    nfe::uint32 MSAAQuality() const;
    void MSAAQuality( nfe::uint32 val );

  private:

    Resolution m_InternalResolution;
    bool m_FullScreen;
    bool m_TripleBuffering;
    uint32 m_MSAACount;
    uint32 m_MSAAQuality;

  };
}

#endif // RenderDeviceParameters_h__
