#pragma once
#ifndef RenderDeviceParameters_h__
#define RenderDeviceParameters_h__

#include "NiFrameEnginePCH.h"

namespace NiFrame
{
	class IStringableObject;

	typedef map< String, vector<IStringableObject*>::type* >::type RenderDeviceParameterList;

	class NIFRAME_DLL_EXPORT RenderDeviceParams
	{
	public:
		RenderDeviceParams( RenderDeviceParameterList* paramList = nullptr );
		~RenderDeviceParams();

		RenderDeviceParameterList* GetParameters( ) const;
		void SetParameters( RenderDeviceParameterList* val );

		vector< String >::type* GetParametersNames() const;
		vector< IStringableObject* >::type* GetParamterValues( const String& parameterName ) const;

	private:
		RenderDeviceParameterList* m_Parameters;

	};
}

#endif // RenderDeviceParameters_h__