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



}
