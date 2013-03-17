#include "NiFrameEnginePCH.h"
#include "NiFrameResolution.h"

namespace NiFrame
{


	NiFrame::String Resolution::ToString() const
	{
		return StringUtils::ToString( m_Width ) + 
			"x" + 
			StringUtils::ToString( m_Height ) + 
			" @ " + 
			StringUtils::ToString( m_RefreshRate ) + 
			"Hz";
	}

	Resolution::Resolution( uint32 wdith, uint32 height, uint32 refreshRate ) :
		m_Width( wdith ),
		m_Height( height ),
		m_RefreshRate( refreshRate )
	{

	}

	Resolution::~Resolution()
	{

	}

}