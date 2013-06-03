#pragma once

#ifndef NiFrameD3DResolution_h__
#define NiFrameD3DResolution_h__

#include "NiFrameRendererPCH.hpp"
#include "NiFrameResolution.hpp"

namespace NiFrame
{
	class D3DResolution : public Resolution
	{
	public:
		D3DResolution( D3DDISPLAYMODE* displayMode );
		~D3DResolution();
		D3DDISPLAYMODE* GetDisplayMode( ) const;

	private:

		D3DDISPLAYMODE* m_DisplayMode;
	};
}

#endif // NiFrameD3DResolution_h__
