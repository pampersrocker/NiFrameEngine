#include "NFRendererPCH.hpp"
#include "NFD3DDevTypeStringable.hpp"

namespace nfe
{


	D3DDevTypeStringable::D3DDevTypeStringable(const D3DDEVTYPE& devType) :
		m_Type( devType )
	{

	}

	D3DDevTypeStringable::~D3DDevTypeStringable()
	{

	}

	nfe::String D3DDevTypeStringable::ToString() const
	{
		if (m_Type == D3DDEVTYPE_HAL)
		{
			return "Hardware Abstraction Layer";
		}
		else if( m_Type == D3DDEVTYPE_REF )
		{
			return "Reference Implementation";
		}
		else
		{
			return "Unknown Device Type";
		}
	}

}