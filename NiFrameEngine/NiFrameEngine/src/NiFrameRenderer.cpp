#include "NiFrameEnginePCH.h"
#include "NiFrameRenderer.h"
#include <winuser.h>
#include <exception>
#include "NiFrameRenderDevice.h"

namespace NiFrame
{
	NiFrameRenderer::~NiFrameRenderer()
	{

	}

	NiFrameRenderer::NiFrameRenderer()
	{

	}

	void NiFrameRenderer::CreateDevice( const String& apiName )
	{
		if ( apiName == "DirectX" )
		{
			m_hDLL = LoadLibraryEx( L"NiFrameD3DX.dll", nullptr, 0 );
			if ( !m_hDLL )
			{
				MessageBox( 
					nullptr, 
					L"Loading NiFrameD3DX.dll failed, is it present?",
					L"Error Loading D3D DLL", 
					MB_OK | MB_ICONERROR);
			} 
		} 
		else
		{
			//TODO: Better Error text
			MessageBox( 
				nullptr, 
				L"The given api is not supported",
				L"Error Loading D3D DLL", 
				MB_OK | MB_ICONERROR);

			throw new std::exception("Failed to create RenderDevice");
		}

		CREATERENDERDEVICE _CreateRenderDevice = 0;
		HRESULT hr;

		//Get CreateRenderDevice function pointer from dll
		_CreateRenderDevice = (CREATERENDERDEVICE) GetProcAddress(m_hDLL,"CreateRenderDevice");
		hr = _CreateRenderDevice(m_hDLL, &m_RenderDevice);

		//Check for success
		if ( FAILED(hr) )
		{
			//TODO: Better Error text
			MessageBox( 
				nullptr, 
				L"Failed to Create the Render Device",
				L"Error Creating Render Device", 
				MB_OK | MB_ICONERROR);

			throw new std::exception("Failed to create RenderDevice");
		}


	}

	void NiFrameRenderer::Release()
	{
			
	}

	HINSTANCE NiFrameRenderer::GetModule() const
	{
		return m_hDLL;
	}

	NiFrameRenderDevice* NiFrameRenderer::GetDevice() const
	{
		return m_RenderDevice;
	}

}