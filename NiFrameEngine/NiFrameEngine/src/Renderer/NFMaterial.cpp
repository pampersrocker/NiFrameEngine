#include "NFEnginePCH.hpp"
#include "Renderer/NFMaterial.hpp"

namespace nfe
{
  Material::Material( const String& name ) :
    m_PixelShader( nullptr ),
    m_VertexShader( nullptr ),
    m_Name( name ),
    m_bWireframe( false )
  {
  }

  Material::~Material()
  {
  }

  bool Material::GetDrawWireframe( void ) const
  {
    return m_bWireframe;
  }

  void Material::SetWireFrame( bool drawWireframe )
  {
    m_bWireframe = drawWireframe;
  }

  const String& Material::GetName( void ) const
  {
    return m_Name;
  }

  void Material::SetVertexShader( IShader* shader )
  {
    m_VertexShader = shader;
  }

  void Material::SetPixelShader( IShader* shader )
  {
    m_PixelShader = shader;
  }

  IShader* Material::GetVertexShader( void ) const
  {
    return m_VertexShader;
  }

  IShader* Material::GetPixelShader( void ) const
  {
    return m_PixelShader;
  }
}
