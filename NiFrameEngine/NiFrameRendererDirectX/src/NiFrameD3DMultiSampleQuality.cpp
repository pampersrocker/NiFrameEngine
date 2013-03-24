#include "NiFrameRendererPCH.h"
#include "NiFrameD3DMultiSampleQuality.h"

namespace NiFrame
{


	NiFrame::String D3DMultiSampleQuality::ToString() const
	{
		return std::to_string( m_MultiSampleQuality );
	}

	D3DMultiSampleQuality::D3DMultiSampleQuality( DWORD multiSampleQuality ) :
		m_MultiSampleQuality( multiSampleQuality )
	{

	}

	D3DMultiSampleQuality::~D3DMultiSampleQuality()
	{

	}

}