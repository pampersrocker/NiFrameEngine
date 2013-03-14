#include "NiFrameEnginePCH.h"
#include "NiFrameRenderDeviceParameters.h"

namespace NiFrame
{
	NiFrameRenderDeviceParams::NiFrameRenderDeviceParams( RenderDeviceParameterList paramList /*= nullptr */ ) :
		m_Parameters ( paramList )
	{

	}

	NiFrameRenderDeviceParams::~NiFrameRenderDeviceParams()
	{
		SAFE_DELETE( m_Parameters )
	}

	void NiFrameRenderDeviceParams::SetParameters( RenderDeviceParameterList val )
	{
		m_Parameters = val;
	}

	NiFrame::RenderDeviceParameterList NiFrameRenderDeviceParams::GetParameters() const
	{
		return m_Parameters;
	}

	vector< String >::type* NiFrameRenderDeviceParams::GetParametersNames() const
	{
		//TODO: Better solution then returning a pointer
		vector< String >::type* parameterNames = new vector< String >::type();
		map< String, vector< String >::type* >::iterator iterator;

		for( iterator = m_Parameters->begin(); iterator != m_Parameters->end(); ++iterator )
		{
			parameterNames->push_back( iterator->first );
		}

		return parameterNames;
	}

	vector< String >::type* NiFrameRenderDeviceParams::GetParamterValues( const String& parameterName ) const
	{
		return ( *m_Parameters )[ parameterName ];
	}



}