#include "NFRendererPCH.hpp"
#include "NFD3DResolution.hpp"

namespace nfe
{


  D3DResolution::D3DResolution( D3DDISPLAYMODE* displayMode ) :
    Resolution(displayMode->Width, displayMode->Height, displayMode->RefreshRate ),
    m_DisplayMode( displayMode )
  {

  }

  D3DResolution::~D3DResolution()
  {
    SAFE_DELETE( m_DisplayMode )
  }

  D3DDISPLAYMODE* D3DResolution::GetDisplayMode() const
  {
    return m_DisplayMode;
  }

}