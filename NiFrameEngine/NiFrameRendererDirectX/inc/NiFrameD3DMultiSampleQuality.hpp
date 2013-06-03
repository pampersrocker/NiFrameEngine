#pragma once
#ifndef NiFrameMultiSampleQuality_h__
#define NiFrameMultiSampleQuality_h__
#include "NiFrameRendererPCH.hpp"
#include "NiFrameStringableObject.hpp"

namespace NiFrame
{
	class D3DMultiSampleQuality : public IStringableObject
	{
	public:
		D3DMultiSampleQuality( DWORD multiSampleQuality );
		~D3DMultiSampleQuality();

		virtual String ToString() const;

	private:

		DWORD m_MultiSampleQuality;

	};
}

#endif // NiFrameMultiSampleQuality_h__
