#include "NFEnginePCH.hpp"
#include "Renderer/NFRenderDeviceParameters.hpp"

namespace nfe
{

  void RenderDeviceParams::Initialize( const Resolution& resolution, bool fullScreen, bool tripleBuffering /*= false*/, uint32 msaaCount /*= 1*/, uint32 msaaQuality /*= 0 */ )
  {
    m_InternalResolution = resolution;
    m_FullScreen = fullScreen;
    m_TripleBuffering = tripleBuffering;
    m_MSAACount = msaaCount;
    m_MSAAQuality = msaaQuality;
  }

  void RenderDeviceParams::MSAAQuality( nfe::uint32 val )
  {
    m_MSAAQuality = val;
  }

  nfe::uint32 RenderDeviceParams::MSAAQuality() const
  {
    return m_MSAAQuality;
  }

  void RenderDeviceParams::MSAACount( nfe::uint32 val )
  {
    m_MSAACount = val;
  }

  nfe::uint32 RenderDeviceParams::MSAACount() const
  {
    return m_MSAACount;
  }

  void RenderDeviceParams::TripleBuffering( bool val )
  {
    m_TripleBuffering = val;
  }

  bool RenderDeviceParams::TripleBuffering() const
  {
    return m_TripleBuffering;
  }

  void RenderDeviceParams::FullScreen( bool val )
  {
    m_FullScreen = val;
  }

  bool RenderDeviceParams::FullScreen() const
  {
    return m_FullScreen;
  }

  void RenderDeviceParams::InternalResolution( nfe::Resolution val )
  {
    m_InternalResolution = val;
  }

  const nfe::Resolution& RenderDeviceParams::InternalResolution() const
  {
    return m_InternalResolution;
  }



}
