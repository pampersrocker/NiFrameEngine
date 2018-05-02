#pragma once
#ifndef NiFrameMaterial_h__
#define NiFrameMaterial_h__

#include "NFEnginePCH.hpp"
#include "NFReferenceCounted.hpp"

namespace nfe
{
  class Shader;
  class IRenderContext;

  class NIFRAME_API Material
  {
  public:
    Material( const String& name );
    ~Material();

    virtual void Initialize();

    Shader* GetPixelShader( void ) const;
    Shader* GetVertexShader( void ) const;

    void SetPixelShader( Shader* shader );
    void SetVertexShader( Shader* shader );

    const String& GetName( void ) const;

  protected:

    Shader* m_PixelShader;
    Shader* m_VertexShader;

  private:

    String m_Name;

  };

  //typedef ReferenceCounted< Material > MaterialPtr;
  TYPEDEF_EXPORT_REFCOUNT_PTR(Material);

}

#endif // NiFrameMaterial_h__
