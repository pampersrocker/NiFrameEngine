#include "NiFrameEnginePCH.hpp"
#include "NiFrameRenderer.hpp"
#include <winuser.h>
#include <exception>
#include "NiFrameRenderDevice.hpp"
#include "resource.h"
#include <commctrl.h>
#include "NiFrameDllEntryPoint.hpp"
#include "..\inc\NiFrameSettingsDialog.hpp"

namespace NiFrame
{
	Renderer::~Renderer()
	{
		Release();
	}

	Renderer::Renderer()
	{

	}

	void Renderer::CreateDevice( const String& apiName )
	{
		if ( apiName == "DirectX" )
		{
			m_hDLL = LoadLibraryEx( "NiFrameD3DX.dll", nullptr, 0 );
			if ( !m_hDLL )
			{
				MessageBox( 
					nullptr, 
					"Loading NiFrameD3DX.dll failed, is it present?",
					"Error Loading D3D DLL", 
					MB_OK | MB_ICONERROR);
			} 
		} 
		else
		{
			//TODO: Better Error text
			MessageBox( 
				nullptr, 
				"The given api is not supported",
				"Error Loading D3D DLL", 
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
				"Failed to Create the Render Device",
				"Error Creating Render Device", 
				MB_OK | MB_ICONERROR);

			throw new std::exception("Failed to create RenderDevice");
		}


	}

	void Renderer::Release()
	{
		if (m_RenderDevice != nullptr)
		{
			RELEASERENDERDEVICE _ReleaseRenderDevice = 0;
			HRESULT hr;
			_ReleaseRenderDevice = (RELEASERENDERDEVICE) GetProcAddress(m_hDLL, "ReleaseRenderDevice");
			if ( _ReleaseRenderDevice != nullptr )
			{
				hr = _ReleaseRenderDevice( &m_RenderDevice );
				if ( FAILED(hr) )
				{
					MessageBox(nullptr, "Failed to destroy renderDevice", "Error", MB_OK | MB_ICONERROR );
				}
			} 

			m_RenderDevice = nullptr;
		}
	}

	HINSTANCE Renderer::GetModule() const
	{
		return m_hDLL;
	}

	RenderDevice* Renderer::GetDevice() const
	{
		return m_RenderDevice;
	}

	void Renderer::ShowSettingsDialog( HINSTANCE instance, HWND parentWindow /*= nullptr*/ )
	{
		SettingsDialog dlg(m_RenderDevice);

		SelectedRenderDevVals vals;

		dlg.ShowDialog(&vals);


	}

}