#include "NiFrameEnginePCH.h"
#include "NiFrameMaterial.h"

namespace NiFrame
{
	Material::Material( const String& name ) :
		m_bWireframe( false ),
		m_Name( name ),
		m_PixelShader( nullptr ),
		m_VertexShader( nullptr )
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
}
