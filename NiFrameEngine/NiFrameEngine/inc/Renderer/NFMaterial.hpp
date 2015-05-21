#pragma once
#ifndef NiFrameMaterial_h__
#define NiFrameMaterial_h__

#include "NFEnginePCH.hpp"
#include "NFReferenceCounted.hpp"

namespace nfe
{
  class IShader;

  class NIFRAME_DLL_EXPORT Material
  {
  public:
    Material( const String& name );
    ~Material();

    IShader* GetPixelShader( void ) const;
    IShader* GetVertexShader( void ) const;

    void SetPixelShader( IShader* shader );
    void SetVertexShader( IShader* shader );

    const String& GetName( void ) const;

    void SetWireFrame( bool drawWireframe );
    bool GetDrawWireframe( void ) const;

  protected:

    IShader* m_PixelShader;
    IShader* m_VertexShader;

  private:

    String m_Name;

    bool m_bWireframe;

  };

  typedef ReferenceCounted< Material > MaterialPtr;

}

#endif // NiFrameMaterial_h__
