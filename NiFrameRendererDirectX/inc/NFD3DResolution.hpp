#pragma once

#ifndef NiFrameD3DResolution_h__
#define NiFrameD3DResolution_h__

#include "NFRendererPCH.hpp"
#include "NFResolution.hpp"

namespace nfe
{
  class D3DResolution : public Resolution
  {
  public:
    D3DResolution( D3DDISPLAYMODE* displayMode );
    ~D3DResolution();
    D3DDISPLAYMODE* GetDisplayMode( ) const;

  private:

    D3DDISPLAYMODE* m_DisplayMode;
  };
}

#endif // NiFrameD3DResolution_h__
