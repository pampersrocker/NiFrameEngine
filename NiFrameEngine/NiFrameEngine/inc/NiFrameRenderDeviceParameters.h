#pragma once
#ifndef RenderDeviceParameters_h__
#define RenderDeviceParameters_h__

#include "NiFrameEnginePCH.h"

namespace NiFrame
{
	typedef map< String, vector<String>::type* >::type* RenderDeviceParameterList;

	class NIFRAME_DLL_EXPORT NiFrameRenderDeviceParams
	{
	public:
		NiFrameRenderDeviceParams( RenderDeviceParameterList paramList = nullptr );
		~NiFrameRenderDeviceParams();

		RenderDeviceParameterList GetParameters( ) const;
		void SetParameters( RenderDeviceParameterList val );

		vector< String >::type* GetParametersNames() const;
		vector< String >::type* GetParamterValues( const String& parameterName ) const;

	private:
		map< String, vector<String>::type* >::type* m_Parameters;

	};
}

#endif // RenderDeviceParameters_h__