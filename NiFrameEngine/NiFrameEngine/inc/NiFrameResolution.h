#pragma once
#ifndef NiFrameResolution_h__
#define NiFrameResolution_h__

#include "NiFrameEnginePCH.h"
#include "NiFrameStringableObject.h"
#include "NiFrameStringUtils.h"

namespace NiFrame
{
	class NIFRAME_DLL_EXPORT Resolution : public IStringableObject
	{
	public:
		Resolution( uint32 wdith, uint32 height, uint32 refreshRate );
		~Resolution();

		virtual String ToString() const;

		uint32 GetWidth( void ) const;

		uint32 GetHeight( void ) const;

	private:
		uint32 m_Width, m_Height, m_RefreshRate;

	};
}

#endif // NiFrameResolution_h__