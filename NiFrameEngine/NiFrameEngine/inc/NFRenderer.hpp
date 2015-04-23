#pragma once
#ifndef NiFrameRenderer_h__
#define NiFrameRenderer_h__

#include "NFEnginePCH.hpp"

namespace nfe
{

  class RenderDevice;

  class NIFRAME_DLL_EXPORT Renderer
  {
  public:
    Renderer();
    ~Renderer();

    void CreateDevice( const String& apiName );

    NativeInstance GetModule() const;

    RenderDevice* GetDevice() const;


  private:

    void Release();

    RenderDevice* m_RenderDevice;

    NativeModule m_hDLL;
  };
}



#endif // NiFrameRenderer_h__



