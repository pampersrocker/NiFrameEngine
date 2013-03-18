#pragma once
#pragma once
#ifndef BufferTypeStringable_h__
#define BufferTypeStringable_h__

#include "NiFrameRendererPCH.h"
#include "StringableObject.h"

namespace NiFrame
{
	class BufferTypeStringable :
		public IStringableObject
	{
	public:
		BufferTypeStringable( const _D3DFORMAT& format );
		virtual ~BufferTypeStringable(void);

		virtual String ToString() const;

		_D3DFORMAT GetFormat( ) const 
		{ 
			return m_Format; 
		}
		void SetFormat( _D3DFORMAT val ) 
		{ 
			m_Format = val; 
		}

	private:
		_D3DFORMAT m_Format;
		
	};

}


#endif // BufferTypeStringable_h__
