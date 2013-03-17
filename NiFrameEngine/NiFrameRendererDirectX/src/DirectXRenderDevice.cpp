#include "NiFrameRendererPCH.h"
#include "DirectXRenderDevice.h"
#include "NiFrameRenderDeviceParameters.h"
#include "StringUtils.h"
#include "NiFrameD3DResolution.h"

extern "C"
{
	HRESULT __declspec( dllexport ) CreateRenderDevice(HINSTANCE hdll, NiFrame::RenderDevice** renderDevice)
	{
		*renderDevice = new NiFrame::D3DRenderDevice( hdll );

		return S_OK;
	}

	HRESULT __declspec( dllexport ) ReleaseRenderDevice( NiFrame::RenderDevice** renderDevice)
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

	D3DRenderDevice::D3DRenderDevice( HINSTANCE hDLL ) :
		m_hDLL( hDLL ),
		m_pD3D( nullptr ),
		m_AdpaterIdentifier( new vector<D3DADAPTER_IDENTIFIER9>::type() ),
		m_AdapterParameters ( vector< RenderDeviceParams* >::type() ),
		m_DeviceResolutions( new vector< vector< D3DResolution* >::type*>::type() )
	{
	}

	D3DRenderDevice::~D3DRenderDevice()
	{
		delete m_AdpaterIdentifier;
		for( auto d3dResolutions = m_AdapterParameters.begin(); d3dResolutions != m_AdapterParameters.end(); ++d3dResolutions )
		{
			
			delete *d3dResolutions;
		}

		for( vector< vector< D3DResolution *>::type*>::iterator d3dResolutions = m_DeviceResolutions->begin(); 
			d3dResolutions != m_DeviceResolutions->end(); 
			++d3dResolutions )
		{
			for(vector< D3DResolution *>::iterator d3dRes = (*d3dResolutions)->begin(); 
				d3dRes != (*d3dResolutions)->end(); 
				++d3dRes )
			{
				delete *d3dRes;
			}
			delete *d3dResolutions;
		}
		 delete m_DeviceResolutions;

		m_AdpaterIdentifier = nullptr;
		m_hDLL = nullptr;
	}

	void D3DRenderDevice::Clear( bool clearPixel , bool clearDepth )
	{
		throw std::exception( "The method or operation is not implemented." );
	}

	void D3DRenderDevice::EndRendering()
	{
		throw std::exception( "The method or operation is not implemented." );
	}

	void D3DRenderDevice::BeginRendering()
	{
		throw std::exception( "The method or operation is not implemented." );
	}

	void D3DRenderDevice::UseWindow( int numWindow )
	{
		throw std::exception( "The method or operation is not implemented." );
	}

	bool D3DRenderDevice::IsRunning() const
	{
		throw std::exception( "The method or operation is not implemented." );
	}

	void D3DRenderDevice::SetupDevice( 
		HWND hMainWindow, 
		const vector< HWND* >::type& renderWindows, 
		int minDepth, 
		int minStencil, 
		const map< String, uint32 >::type& renderDeviceParameters ,
		bool log /*= true */ )
	{
		

	}

	NiFrame::RenderDeviceParams D3DRenderDevice::GetRenderParams( void ) const
	{
		return NiFrame::RenderDeviceParams();
	}

	void D3DRenderDevice::Initialize()
	{
		m_pD3D = Direct3DCreate9( D3D_SDK_VERSION );
		if ( m_pD3D == nullptr )
		{
			throw new exception("Failed to load DirectX\nInstall the latest DirectX version");
		}

		uint32 numAdapters = m_pD3D->GetAdapterCount();
		if ( numAdapters == 0 )
		{
			throw new exception( "Found no DirectX Adapters" );
		}

		D3DADAPTER_IDENTIFIER9 tmp_identifier;
		

		for (uint32 i = 0; i < numAdapters; i++)
		{
			if ( FAILED( m_pD3D->GetAdapterIdentifier( i, 0, &tmp_identifier) ) )
			{
				throw new exception( "Failed to get Adapter identifier" );
			} 
			else
			{
				m_AdapterParameters.push_back( new RenderDeviceParams() );
				RenderDeviceParameterList* paramList = m_AdapterParameters[i]->GetParameters();

				LoadDeviceResolutions(i, paramList);

			}
		}
	}

	void D3DRenderDevice::LoadDeviceResolutions( uint32 deviceID, RenderDeviceParameterList* paramList )
	{
		uint32 videoModeCount = m_pD3D->GetAdapterModeCount(deviceID, D3DFMT_X8R8G8B8 );
		D3DDISPLAYMODE* displayModes = new D3DDISPLAYMODE[videoModeCount];

		
		vector< D3DResolution* >::type* d3dResolutions = new vector< D3DResolution* >::type();

		vector< IStringableObject* >::type* modeVector = new vector< IStringableObject* >::type();

		for (uint32 videoMode = 0; videoMode < videoModeCount; videoMode++)
		{
			m_pD3D->EnumAdapterModes( deviceID, D3DFMT_X8R8G8B8, videoMode, &displayModes[videoMode]);
			D3DDISPLAYMODE* d3dMode = new D3DDISPLAYMODE(displayModes[videoMode]);

			D3DResolution* resolution = new D3DResolution(d3dMode);
			d3dResolutions->push_back( resolution );
			modeVector->push_back(resolution);
		}

		m_DeviceResolutions->push_back( d3dResolutions );

		(*paramList)["VideMode"] = modeVector;

		delete displayModes;
	}


}