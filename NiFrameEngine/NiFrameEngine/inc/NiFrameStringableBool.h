#pragma once
#include "NiFrameEnginePCH.h"
#include "NiFrameStringableObject.h"
#ifndef FullScreen_h__
#define FullScreen_h__

namespace NiFrame
{
	class NIFRAME_DLL_EXPORT StringableBool : public IStringableObject
	{
	public:
		StringableBool( bool value );
		~StringableBool();

		virtual String ToString() const;
		bool GetBool( ) const;

	private:

		bool m_Bool;
		
		
	}; 
}

#endif // FullScreen_h__
