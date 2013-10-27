#pragma once
#ifndef NiFrameRenderer_h__
#define NiFrameRenderer_h__

#include "NFEnginePCH.hpp"

namespace nfe
{

	class RenderDevice;

	class NIFRAME_DLL_EXPORT Renderer
	{
	public:
		Renderer();
		~Renderer();

		void CreateDevice( const String& apiName );

		HINSTANCE GetModule() const;

		RenderDevice* GetDevice() const;

		void ShowSettingsDialog(HINSTANCE instance,  HWND parentWindow = nullptr);



	private:

		void Release();

		RenderDevice* m_RenderDevice;

		HMODULE m_hDLL;
	};
}



#endif // NiFrameRenderer_h__



