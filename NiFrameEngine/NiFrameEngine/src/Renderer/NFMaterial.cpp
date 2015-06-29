#include "NFEnginePCH.hpp"
#include "Renderer/NFMaterial.hpp"

namespace nfe
{
  Material::Material( const String& name ) :
    m_PixelShader( nullptr ),
    m_VertexShader( nullptr ),
    m_Name( name )
  {
  }

  Material::~Material()
  {
  }

  const String& Material::GetName( void ) const
  {
    return m_Name;
  }

  void Material::SetVertexShader( Shader* shader )
  {
    m_VertexShader = shader;
  }

  void Material::SetPixelShader( Shader* shader )
  {
    m_PixelShader = shader;
  }

  Shader* Material::GetVertexShader( void ) const
  {
    return m_VertexShader;
  }

  Shader* Material::GetPixelShader( void ) const
  {
    return m_PixelShader;
  }

  void Material::Initialize()
  {

  }

}
