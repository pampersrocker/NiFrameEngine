#include "NiFrameRendererPCH.h"
#include "NiFrameMultiSample.h"

namespace NiFrame
{

	D3DMultiSample::D3DMultiSample( const D3DMULTISAMPLE_TYPE& multiSampleType ) :
		m_MultiSampleType( multiSampleType )
	{

	}

	D3DMultiSample::~D3DMultiSample()
	{

	}

	String D3DMultiSample::ToString() const
	{
		return std::to_string( m_MultiSampleType ) + " Samples";
	}

	D3DMULTISAMPLE_TYPE D3DMultiSample::GetMultiSampleType() const
	{
		return m_MultiSampleType;
	}

}