#pragma once
#ifndef NiFrameRenderDevice_h__
#define NiFrameRenderDevice_h__

#include "NiFrameEnginePCH.h"

namespace NiFrame
{

	class NiFrameRenderDevice
	{
	public:

		virtual void Init(  ) = 0;

		virtual bool IsRunning() const = 0;

		virtual void UseWindow() = 0;

		virtual void BeginRendering() = 0;

		virtual void EndRendering() = 0;

		virtual void Clear( bool clearPixel , bool clearDepth ) = 0;


	private:

	};
}

extern "C"
{
	HRESULT CreateRenderDevice(HINSTANCE hdll, NiFrame::NiFrameRenderDevice** renderDevice);
	typedef HRESULT (*CREATERENDERDEVICE)(HINSTANCE hdll, NiFrame::NiFrameRenderDevice** renderDevice);

	HRESULT ReleaseRenderDevice(HINSTANCE hdll, NiFrame::NiFrameRenderDevice** renderDevice);
	typedef HRESULT (*RELEASERENDERDEVICE)(HINSTANCE hdll, NiFrame::NiFrameRenderDevice** renderDevice);
};

#endif // NiFrameRenderDevice_h__

