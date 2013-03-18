#include "NiFrameRendererPCH.h"
#include "NiFrameBufferTypeStringable.h"


namespace NiFrame
{
	BufferTypeStringable::BufferTypeStringable(const _D3DFORMAT& format) :
		m_Format( format )
	{
	}


	BufferTypeStringable::~BufferTypeStringable(void)
	{
	}

	String BufferTypeStringable::ToString() const
	{
		if (m_Format == D3DFMT_X8R8G8B8)
		{
			return "X8R8G8B8";
		}
		else
		{
			return "R5G6B5";
		}
	} 
}
