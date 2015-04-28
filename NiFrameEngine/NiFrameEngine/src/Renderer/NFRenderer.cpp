#include "NFEnginePCH.hpp"
#include "Renderer/NFRenderer.hpp"
#include <winuser.h>
#include <exception>
#include "Renderer/NFRenderDevice.hpp"
#include "NFDllEntryPoint.hpp"
#include "Platform/NFPlatform.hpp"
#include "Platform/NFNativeModule.hpp"

namespace nfe
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
    if( apiName == "DirectX" )
    {
      INativeModule* renderModule = GPlatform->LoadModule( "NiFrameD3DX.dll" );
      m_RenderModule = renderModule;

      decltype( CreateRenderDevice )* _CreateRenderDevice = nullptr;

      //Get CreateRenderDevice function pointer from dll
      _CreateRenderDevice = renderModule->GetModuleFunctionPointer<decltype( CreateRenderDevice )>( "CreateRenderDevice" );
      _CreateRenderDevice( &m_RenderDevice );
      if( m_RenderDevice == nullptr )
      {
        // TODO: Log
      }
    }
  }

  void Renderer::Release()
  {
    if (m_RenderDevice != nullptr && m_RenderModule != nullptr)
    {
      decltype(ReleaseRenderDevice)* _ReleaseRenderDevice = 0;
      _ReleaseRenderDevice = m_RenderModule->GetModuleFunctionPointer<decltype(ReleaseRenderDevice)>("ReleaseRenderDevice");
      if ( _ReleaseRenderDevice != nullptr )
      {
        _ReleaseRenderDevice( &m_RenderDevice );
        if (m_RenderDevice != nullptr)
        {
          // TODO: Log failed release
        }
      }

      m_RenderDevice = nullptr;
    }
  }

  INativeModule* Renderer::GetModule() const
  {
    return m_RenderModule;
  }

  RenderDevice* Renderer::GetDevice() const
  {
    return m_RenderDevice;
  }

}
