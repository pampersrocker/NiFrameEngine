#pragma once
#ifndef NiFrameRenderer_h__
#define NiFrameRenderer_h__

#include "NiFrameEnginePCH.h"

namespace NiFrame
{

	class NiFrameRenderDevice;

	class NiFrameRenderer
	{
	public:
		NiFrameRenderer();
		~NiFrameRenderer();

		void CreateDevice( const String& apiName );

		void Release();

		HINSTANCE GetModule() const;

		NiFrameRenderDevice* GetDevice() const;



	private:
		NiFrameRenderDevice* m_RenderDevice;

		HMODULE m_hDLL;
	};
}



#endif // NiFrameRenderer_h__



