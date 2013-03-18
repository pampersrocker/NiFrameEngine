#pragma once
#include "NiFrameRendererPCH.h"
#include "StringableObject.h"
#ifndef FullScreen_h__
#define FullScreen_h__

namespace NiFrame
{
	class StringableBool : public IStringableObject
	{
	public:
		StringableBool( bool value );
		~StringableBool();

		virtual String ToString() const;

	private:

		bool m_Bool;

	}; 
}

#endif // FullScreen_h__
