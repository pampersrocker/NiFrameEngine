#include "NiFrameEnginePCH.h"
#include "NiFrameRenderDeviceParameters.h"

namespace NiFrame
{
	RenderDeviceParams::RenderDeviceParams( RenderDeviceParameterList* paramList /*= nullptr */ ) :
		m_Parameters ( paramList )
	{
		if ( m_Parameters == nullptr )
		{
			m_Parameters = new RenderDeviceParameterList();
		} 
	}

	RenderDeviceParams::~RenderDeviceParams()
	{
		for(auto iterator = m_Parameters->begin(); iterator != m_Parameters->end(); ++iterator )
		{
			delete iterator->second;
		}

		SAFE_DELETE( m_Parameters )
	}

	void RenderDeviceParams::SetParameters( RenderDeviceParameterList* val )
	{
		m_Parameters = val;
	}

	NiFrame::RenderDeviceParameterList* RenderDeviceParams::GetParameters() const
	{
		return m_Parameters;
	}

	vector< String >::type RenderDeviceParams::GetParametersNames() const
	{
		//TODO: Better solution then returning a pointer
		vector< String >::type parameterNames;
		map< String, vector< IStringableObject* >::type* >::iterator iterator;

		for( iterator = m_Parameters->begin(); iterator != m_Parameters->end(); ++iterator )
		{
			parameterNames.push_back( iterator->first );
		}

		return parameterNames;
	}

	vector< IStringableObject* >::type RenderDeviceParams::GetParamterValues( const String& parameterName ) const
	{
		return *( *m_Parameters )[ parameterName ];
	}



}