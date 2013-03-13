#pragma once
#include "NiFrameRendererPCH.h"
#include "NiFrameRenderDevice.h"

#ifndef DirectXRenderDevice_h__
#define DirectXRenderDevice_h__

namespace NiFrame
{
	class NiFrameD3DRenderDevice : public NiFrameRenderDevice
	{
	public:
		NiFrameD3DRenderDevice();
		~NiFrameD3DRenderDevice();

	private:

	};

	NiFrameD3DRenderDevice::NiFrameD3DRenderDevice()
	{
	}

	NiFrameD3DRenderDevice::~NiFrameD3DRenderDevice()
	{
	}
}

#endif // DirectXRenderDevice_h__