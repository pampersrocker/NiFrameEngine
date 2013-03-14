#include "NiFrameRendererPCH.h"
#include "DirectXRenderDevice.h"
#include "NiFrameRenderDeviceParameters.h"

extern "C"
{
	HRESULT __declspec( dllexport ) CreateRenderDevice(HINSTANCE hdll, NiFrame::NiFrameRenderDevice** renderDevice)
	{
		*renderDevice = new NiFrame::NiFrameD3DRenderDevice( hdll );

		return S_OK;
	}

	HRESULT __declspec( dllexport ) ReleaseRenderDevice( NiFrame::NiFrameRenderDevice** renderDevice)
	{
		if ( *renderDevice != nullptr )
		{
			delete *renderDevice;
			*renderDevice = nullptr;
		}

		return S_OK;
	}
};

namespace NiFrame
{

	NiFrameD3DRenderDevice::NiFrameD3DRenderDevice( HINSTANCE hDLL ) :
		m_hDLL( hDLL ),
		m_pD3D( nullptr ),
		m_iNumAdapters( 0 ),
		m_AdpaterIdentifier( new vector<D3DADAPTER_IDENTIFIER9>::type() )
	{
	}

	NiFrameD3DRenderDevice::~NiFrameD3DRenderDevice()
	{
		delete m_AdpaterIdentifier;
		m_AdpaterIdentifier = nullptr;
		m_hDLL = nullptr;
	}

	void NiFrameD3DRenderDevice::Clear( bool clearPixel , bool clearDepth )
	{
		throw std::exception( "The method or operation is not implemented." );
	}

	void NiFrameD3DRenderDevice::EndRendering()
	{
		throw std::exception( "The method or operation is not implemented." );
	}

	void NiFrameD3DRenderDevice::BeginRendering()
	{
		throw std::exception( "The method or operation is not implemented." );
	}

	void NiFrameD3DRenderDevice::UseWindow( int numWindow )
	{
		throw std::exception( "The method or operation is not implemented." );
	}

	bool NiFrameD3DRenderDevice::IsRunning() const
	{
		throw std::exception( "The method or operation is not implemented." );
	}

	void NiFrameD3DRenderDevice::SetupDevice( 
		HWND hMainWindow, 
		const vector< HWND* >::type& renderWindows, 
		int minDepth, 
		int minStencil, 
		const map< String, uint32 >::type& renderDeviceParameters ,
		bool log /*= true */ )
	{
		

	}

	NiFrame::NiFrameRenderDeviceParams NiFrameD3DRenderDevice::GetRenderParams( void ) const
	{
		return NiFrame::NiFrameRenderDeviceParams();
	}

	void NiFrameD3DRenderDevice::Initialize()
	{
		m_pD3D = Direct3DCreate9( D3D_SDK_VERSION );
		if ( m_pD3D == nullptr )
		{
			throw new exception("Failed to load DirectX\nInstall the latest DirectX version");
		}

		m_iNumAdapters = m_pD3D->GetAdapterCount();
		if ( m_iNumAdapters == 0 )
		{
			throw new exception( "Found no DirectX Adapters" );
		}

		D3DADAPTER_IDENTIFIER9 tmp_identifier;
		
		String output;

		for (int i = 0; i < m_iNumAdapters; i++)
		{
			if ( FAILED( m_pD3D->GetAdapterIdentifier( i, 0, &tmp_identifier) ) )
			{
				throw new exception( "Failed to get Adapter identifier" );
			} 
			else
			{
				m_AdpaterIdentifier->push_back(tmp_identifier);
				output.append( "Description: " ).append( tmp_identifier.Description );
				output += "\n";
				output .append( "Device Name: " ).append( tmp_identifier.DeviceName );
				output += "\n";

				MessageBox( nullptr, output.c_str(), "Device Information", MB_OK );
			}
		}
	}


}