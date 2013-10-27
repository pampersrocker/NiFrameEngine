#pragma once
#ifndef NiFramePixelShader_h__
#define NiFramePixelShader_h__

#include "NFEnginePCH.hpp"

namespace nfe
{
	class NIFRAME_DLL_EXPORT Shader
	{
	public:
		Shader();
		~Shader();

		virtual void SetShaderParameter( const String& paramName, const Real value ) = 0;
		virtual void SetShaderParameter( const String& paramName, const int32 value ) = 0;
		virtual void SetShaderParameter( const String& paramName, const Matrix4x4& value ) = 0;
		virtual void SetShaderParameter( const String& paramName, const Vector3& value ) = 0;

		virtual Real GetShaderParameterReal( const String& paramName ) const = 0;
		virtual int32 GetShaderParameterInt( const String& paramName ) const = 0;
		virtual Matrix4x4 GetShaderParameterMatrix( const String& paramName ) const = 0;
		virtual Vector3 GetShaderParameterVector3( const String& paramName ) const = 0;

	private:

		String m_ShaderName;
		String m_ShaderFileName;

	};
}

#endif // NiFramePixelShader_h__
