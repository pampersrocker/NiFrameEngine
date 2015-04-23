#pragma once
#ifndef NiFrameMaterial_h__
#define NiFrameMaterial_h__

#include "NFEnginePCH.hpp"
#include "NFReferenceCounted.hpp"

namespace nfe
{
  class Shader;

  class NIFRAME_DLL_EXPORT Material
  {
  public:
    Material( const String& name );
    ~Material();

    Shader* GetPixelShader( void ) const;
    Shader* GetVertexShader( void ) const;

    void SetPixelShader( Shader* shader );
    void SetVertexShader( Shader* shader );

    const String& GetName( void ) const;

    void SetWireFrame( bool drawWireframe );
    bool GetDrawWireframe( void ) const;

  protected:

    Shader* m_PixelShader;
    Shader* m_VertexShader;

  private:

    String m_Name;

    bool m_bWireframe;

  };

  typedef ReferenceCounted< Material > MaterialPtr;

}

#endif // NiFrameMaterial_h__
