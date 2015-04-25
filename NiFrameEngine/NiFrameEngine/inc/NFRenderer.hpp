#pragma once
#ifndef NiFrameRenderer_h__
#define NiFrameRenderer_h__

#include "NFEnginePCH.hpp"

namespace nfe
{
  class INativeModule;
  class RenderDevice;

  class NIFRAME_DLL_EXPORT Renderer
  {
  public:
    Renderer();
    ~Renderer();

    void CreateDevice( const String& apiName );

    INativeModule* GetModule() const;

    RenderDevice* GetDevice() const;


  private:

    void Release();

    RenderDevice* m_RenderDevice;

    INativeModule* m_RenderModule;
  };
}



#endif // NiFrameRenderer_h__



