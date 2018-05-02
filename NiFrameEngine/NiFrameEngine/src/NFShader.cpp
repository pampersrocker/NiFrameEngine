#include "NFEnginePCH.hpp"

#include "Renderer/NFShader.hpp"




void nfe::Shader::Initialize( const String& fileName )
{
  m_ShaderFileName = fileName;
}

const nfe::String& nfe::Shader::ShaderFileName() const
{
  return m_ShaderFileName;
}

nfe::Shader::Shader()
{

}

nfe::Shader::~Shader()
{

}
