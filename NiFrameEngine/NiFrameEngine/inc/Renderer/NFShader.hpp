#pragma once
#ifndef NiFramePixelShader_h__
#define NiFramePixelShader_h__

#include "NFEnginePCH.hpp"

namespace nfe
{
  class IRenderContext;

  class NIFRAME_API Shader
  {
  public:
    Shader();
    virtual ~Shader();

    virtual void Initialize( const String& fileName );

    virtual void PrepareShader( IRenderContext* context ) = 0;

    const nfe::String& ShaderFileName() const;


  private:

    String m_ShaderFileName;
  };

}

#endif // NiFramePixelShader_h__
