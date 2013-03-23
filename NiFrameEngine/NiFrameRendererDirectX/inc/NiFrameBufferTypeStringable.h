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

		static map< D3DFORMAT, String >::type* D3DFormatToStringMap;

		static map< D3DFORMAT, String >::type* PopulateMap();
		
	};

}


#endif // BufferTypeStringable_h__
