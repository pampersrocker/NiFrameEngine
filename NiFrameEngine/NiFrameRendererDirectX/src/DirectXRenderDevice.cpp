#include "NiFrameRendererPCH.h"
#include "DirectXRenderDevice.h"
#include "NiFrameRenderDeviceParameters.h"
#include "StringUtils.h"
#include "NiFrameD3DResolution.h"
#include "NiFrameStringableBool.h"
#include "NiFrameD3DDevTypeStringable.h"
#include "..\inc\NiFrameBufferTypeStringable.h"

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
		m_DeviceResolutions( new vector< vector< D3DResolution* >::type*>::type() ),
		m_FullScreen( new vector< vector< StringableBool* >::type*>::type() ),
		m_D3DDevTypes( new vector< vector< D3DDevTypeStringable*>::type*>::type() ),
		m_BufferTypes( new vector< vector< BufferTypeStringable*>::type*>::type() )
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
		SAFE_DELETE(m_DeviceResolutions);

		for(vector< vector< StringableBool*>::type* >::iterator iterator = m_FullScreen->begin(); 
			iterator != m_FullScreen->end(); 
			++iterator )
		{
			for(vector< StringableBool*>::iterator fullScreenIter = (*iterator)->begin(); 
				fullScreenIter != (*iterator)->end(); 
				++fullScreenIter )
			{
				delete *fullScreenIter;
			}

			delete *iterator;
		}
		SAFE_DELETE(m_FullScreen);

		for(vector< vector< D3DDevTypeStringable*>::type* >::iterator iterator = m_D3DDevTypes->begin(); 
			iterator != m_D3DDevTypes->end(); 
			++iterator )
		{
			for(vector< D3DDevTypeStringable*>::iterator devTypesIterator = (*iterator)->begin(); 
				devTypesIterator != (*iterator)->end(); 
				++devTypesIterator )
			{
				delete *devTypesIterator;
			}

			delete *iterator;
		}
		SAFE_DELETE(m_D3DDevTypes);

		for(vector< vector< BufferTypeStringable*>::type* >::iterator iterator = m_BufferTypes->begin(); 
			iterator != m_BufferTypes->end(); 
			++iterator )
		{
			for(vector< BufferTypeStringable*>::iterator BufferTypesIterator = (*iterator)->begin(); 
				BufferTypesIterator != (*iterator)->end(); 
				++BufferTypesIterator )
			{
				delete *BufferTypesIterator;
			}

			delete *iterator;
		}
		SAFE_DELETE(m_BufferTypes);

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

				LoadDeviceTypeSelection( i, paramList );

				LoadFullScreenSelection( paramList );

				//Load Resolutions
				LoadDeviceResolutions(i, paramList);

				LoadBufferTypeSelection( i, paramList );

				LoadZBufferTypeSelection( i, paramList );

				LoadMultiSamples( i, paramList );

				LoadMultiSampleQualities( i, paramList );

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

		(*paramList)["Video Mode"] = modeVector;

		delete displayModes;
	}

	void D3DRenderDevice::LoadFullScreenSelection( RenderDeviceParameterList* paramList )
	{
		vector< StringableBool* >::type* modes = new vector< StringableBool* >::type();

		vector< IStringableObject* >::type* paramListMember = new vector< IStringableObject* >::type();

		modes->push_back( new StringableBool( false ) );
		modes->push_back( new StringableBool( true ) );

		for(auto iterator = modes->begin(); iterator != modes->end(); ++iterator )
		{
			paramListMember->push_back( *iterator );
		}

		( *paramList )[ "Full screen" ] = paramListMember;

		m_FullScreen->push_back(modes);
	}



	void D3DRenderDevice::LoadDeviceTypeSelection( uint32 i, RenderDeviceParameterList* paramList )
	{
		vector< D3DDevTypeStringable* >::type* devType = new vector< D3DDevTypeStringable* >::type();

		vector< IStringableObject* >::type* paramListVector = new vector< IStringableObject* >::type();

		devType->push_back( new D3DDevTypeStringable( D3DDEVTYPE_HAL ) );
		devType->push_back( new D3DDevTypeStringable( D3DDEVTYPE_REF ) );

		for(auto iterator = devType->begin(); iterator != devType->end(); ++iterator )
		{
			paramListVector->push_back( *iterator );
		}

		( *paramList )[ "Device Type" ] = paramListVector;

		m_D3DDevTypes->push_back( devType );
	}

	void D3DRenderDevice::LoadBufferTypeSelection( uint32 i, RenderDeviceParameterList* paramList )
	{
		vector< BufferTypeStringable* >::type* devType = new vector< BufferTypeStringable* >::type();

		vector< IStringableObject* >::type* paramListVector = new vector< IStringableObject* >::type();

		devType->push_back( new BufferTypeStringable( D3DFMT_X8R8G8B8 ) );
		devType->push_back( new BufferTypeStringable( D3DFMT_R5G6B5 ) );

		for(auto iterator = devType->begin(); iterator != devType->end(); ++iterator )
		{
			paramListVector->push_back( *iterator );
		}

		( *paramList )[ "Buffer Type" ] = paramListVector;

		m_BufferTypes->push_back( devType );
	}

	void D3DRenderDevice::LoadZBufferTypeSelection( uint32 i, RenderDeviceParameterList* paramList )
	{
		//throw std::exception( "The method or operation is not implemented." );
	}

	void D3DRenderDevice::LoadMultiSamples( uint32 i, RenderDeviceParameterList* paramList )
	{
		//m_pD3D->CheckDeviceMultiSampleType(i, D3DDEVTY)
	}

	void D3DRenderDevice::LoadMultiSampleQualities( uint32 i, RenderDeviceParameterList* paramList )
	{
		//throw std::exception( "The method or operation is not implemented." );
	}


}