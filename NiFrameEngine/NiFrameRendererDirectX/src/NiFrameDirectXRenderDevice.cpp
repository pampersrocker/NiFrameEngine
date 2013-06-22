#include "NiFrameRendererPCH.hpp"
#include "NiFrameDirectXRenderDevice.hpp"
#include "NiFrameRenderDeviceParameters.hpp"
#include "NiFrameStringUtils.hpp"
#include "NiFrameD3DResolution.hpp"
#include "NiFrameStringableBool.hpp"
#include "NiFrameD3DDevTypeStringable.hpp"
#include "NiFrameBufferTypeStringable.hpp"
#include "NiFrameMultiSample.hpp"
#include "NiFrameD3DMultiSampleQuality.hpp"
#include <vector>
#include <SSEMatrix4x4.hpp>
#include "NiFrameD3DMesh.hpp"

using namespace LinearMath;

extern "C"
{
	HRESULT __declspec( dllexport ) CreateRenderDevice( HINSTANCE hdll, NiFrame::RenderDevice * *renderDevice )
	{
		*renderDevice = new NiFrame::D3DRenderDevice( hdll );

		return S_OK;
	}

	HRESULT __declspec( dllexport ) ReleaseRenderDevice( NiFrame::RenderDevice * *renderDevice )
	{
		if( *renderDevice != nullptr )
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
		m_AdpaterIdentifier( new vector< D3DADAPTER_IDENTIFIER9 >::type() ),
		m_AdapterParameters( vector< RenderDeviceParams* >::type() ),
		m_DeviceResolutions( new vector< vector< D3DResolution* >::type* >::type() ),
		m_Windowed( new vector< vector< StringableBool* >::type* >::type() ),
		m_D3DDevTypes( new vector< vector< D3DDevTypeStringable* >::type* >::type() ),
		m_BufferTypes( new vector< vector< BufferTypeStringable* >::type* >::type() ),
		m_ZBufferTypes( new vector< vector< BufferTypeStringable* >::type* >::type() ),
		m_MultiSampleTypes( new vector< vector< D3DMultiSample* >::type* >::type() ),
		m_MultiSampleQualities( new vector< vector< D3DMultiSampleQuality* >::type* >::type() ),
		m_SelectedValues( new map< String, uint32 >::type() ),
		VIDEOMODE( "VideoMode" ),
		BUFFERTYPE( "BackBufferType" ),
		ZBUFFERTYPE( "Z-BufferType" ),
		WINDOWED( "Windowed" ),
		MULTISAMPLE_TYPE( "MultisampleType" ),
		MULTISAMPLE_QUALITY( "MultisampleQuality" ),
		DEVICE_TYPE( "Device Type" ),
		m_CurrentDevice( 0 ),
		m_ProjectionMatrix( SSEMatrix4x4() ),
		m_Params( D3DPRESENT_PARAMETERS() )
	{
		( *m_SelectedValues )[ VIDEOMODE ] = 0;
		( *m_SelectedValues )[ BUFFERTYPE ] = 0;
		( *m_SelectedValues )[ ZBUFFERTYPE ] = 0;
		( *m_SelectedValues )[ WINDOWED ] = 0;
		( *m_SelectedValues )[ MULTISAMPLE_TYPE ] = 0;
		( *m_SelectedValues )[ MULTISAMPLE_QUALITY ] = 0;
		( *m_SelectedValues )[ DEVICE_TYPE ] = 0;
	}

	D3DRenderDevice::~D3DRenderDevice()
	{
		SAFE_DELETE( m_SelectedValues )
		SAFE_DELETE( m_AdpaterIdentifier )

		for( auto d3dResolutions = m_AdapterParameters.begin();
			d3dResolutions != m_AdapterParameters.end();
			++d3dResolutions )
		{
			delete *d3dResolutions;
		}

		for( vector< vector< D3DResolution* >::type* >::iterator d3dResolutions = m_DeviceResolutions->begin();
			d3dResolutions != m_DeviceResolutions->end();
			++d3dResolutions )
		{
			for( vector< D3DResolution* >::iterator d3dRes = ( *d3dResolutions )->begin();
				d3dRes != ( *d3dResolutions )->end();
				++d3dRes )
			{
				delete *d3dRes;
			}

			delete *d3dResolutions;
		}

		SAFE_DELETE( m_DeviceResolutions )

		for( vector< vector< StringableBool* >::type* >::iterator iterator = m_Windowed->begin();
			iterator != m_Windowed->end();
			++iterator )
		{
			for( vector< StringableBool* >::iterator fullScreenIter = ( *iterator )->begin();
				fullScreenIter != ( *iterator )->end();
				++fullScreenIter )
			{
				delete *fullScreenIter;
			}

			delete *iterator;
		}

		SAFE_DELETE( m_Windowed )

		for( vector< vector< D3DDevTypeStringable* >::type* >::iterator iterator = m_D3DDevTypes->begin();
			iterator != m_D3DDevTypes->end();
			++iterator )
		{
			for( vector< D3DDevTypeStringable* >::iterator devTypesIterator = ( *iterator )->begin();
				devTypesIterator != ( *iterator )->end();
				++devTypesIterator )
			{
				delete *devTypesIterator;
			}

			delete *iterator;
		}

		SAFE_DELETE( m_D3DDevTypes )

		for( vector< vector< BufferTypeStringable* >::type* >::iterator iterator = m_BufferTypes->begin();
			iterator != m_BufferTypes->end();
			++iterator )
		{
			for( vector< BufferTypeStringable* >::iterator BufferTypesIterator = ( *iterator )->begin();
				BufferTypesIterator != ( *iterator )->end();
				++BufferTypesIterator )
			{
				delete *BufferTypesIterator;
			}

			delete *iterator;
		}

		SAFE_DELETE( m_BufferTypes )

		for( vector< vector< BufferTypeStringable* >::type* >::iterator iterator = m_ZBufferTypes->begin();
			iterator != m_ZBufferTypes->end();
			++iterator )
		{
			for( vector< BufferTypeStringable* >::iterator BufferTypesIterator = ( *iterator )->begin();
				BufferTypesIterator != ( *iterator )->end();
				++BufferTypesIterator )
			{
				delete *BufferTypesIterator;
			}

			delete *iterator;
		}

		SAFE_DELETE( m_ZBufferTypes )

		for( vector< vector< D3DMultiSample* >::type* >::iterator iterator = m_MultiSampleTypes->begin();
			iterator != m_MultiSampleTypes->end();
			++iterator )
		{
			for( vector< D3DMultiSample* >::iterator BufferTypesIterator = ( *iterator )->begin();
				BufferTypesIterator != ( *iterator )->end();
				++BufferTypesIterator )
			{
				delete *BufferTypesIterator;
			}

			delete *iterator;
		}

		SAFE_DELETE( m_MultiSampleTypes )

		for( vector< vector< D3DMultiSampleQuality* >::type* >::iterator iterator = m_MultiSampleQualities->begin();
			iterator != m_MultiSampleQualities->end();
			++iterator )
		{
			for( vector< D3DMultiSampleQuality* >::iterator BufferTypesIterator = ( *iterator )->begin();
				BufferTypesIterator != ( *iterator )->end();
				++BufferTypesIterator )
			{
				delete *BufferTypesIterator;
			}

			delete *iterator;
		}

		SAFE_DELETE( m_MultiSampleQualities )

		m_AdpaterIdentifier = nullptr;
		m_hDLL = nullptr;

		m_Device->Release();
		m_Device = nullptr;
		m_pD3D->Release();
		m_pD3D = nullptr;
	}

	void D3DRenderDevice::Clear( bool clearPixel, bool clearDepth )
	{
		m_Device->Clear( 0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB( 255, 255, 255 ), 1.0f, 0 );
	}

	void D3DRenderDevice::EndRendering()
	{
		m_Device->EndScene();

		if( m_Device->Present( nullptr, nullptr, nullptr, nullptr ) == D3DERR_DEVICELOST )
		{
			m_Device->Reset( &m_Params );
		}
	}

	void D3DRenderDevice::BeginRendering()
	{
		Clear( true, true );
		m_Device->BeginScene();
	}

	void D3DRenderDevice::SetupDevice(
		HWND hMainWindow,
		const map< String, uint32 >::type& renderDeviceParameters,
		bool log /*= true */ )
	{
		ZeroMemory( &m_Params, sizeof( m_Params ) );

		auto windowedResult = renderDeviceParameters.find( WINDOWED );
		m_Params.Windowed = ( ( *( *m_Windowed )[ m_CurrentDevice ] )[ windowedResult->second ] )->GetBool();
		m_Params.SwapEffect = D3DSWAPEFFECT_DISCARD;
		m_Params.EnableAutoDepthStencil = true;
		m_Params.AutoDepthStencilFormat = D3DFMT_D16;
		m_Params.hDeviceWindow = hMainWindow;
		auto videoResult = renderDeviceParameters.find( VIDEOMODE );
		m_Params.BackBufferWidth
			= ( ( *( *m_DeviceResolutions )[ m_CurrentDevice ] )[ videoResult->second ] )->GetDisplayMode()->Width;
		m_Params.BackBufferHeight
			= ( ( *( *m_DeviceResolutions )[ m_CurrentDevice ] )[ videoResult->second ] )->GetDisplayMode()->Height;
		m_Params.BackBufferFormat
			= ( ( *( *m_DeviceResolutions )[ m_CurrentDevice ] )[ videoResult->second ] )->GetDisplayMode()->Format;
		m_Params.MultiSampleType = D3DMULTISAMPLE_NONE;

		if( FAILED( m_pD3D->CreateDevice( m_CurrentDevice, D3DDEVTYPE_HAL, hMainWindow,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING, &m_Params,
			&m_Device ) ) )
		{
			MessageBox( hMainWindow, "Failed to Create D3D9Device", "Error creating Device", MB_OK );
		}

		m_ProjectionMatrix = LinearMath::SSEMatrix4x4::CreateProjectionMatrix( 60.0f,
			( Real )m_Params.BackBufferWidth / ( Real )m_Params.BackBufferHeight,
			1.0f,
			1000.0f );
		float tmp[ 16 ];
		m_ProjectionMatrix.TransposedCopy().GetAsFloatArray( tmp );
		D3DXMATRIX matrix( tmp );
		m_Device->SetTransform( D3DTS_PROJECTION, &matrix );
		LinearMath::SSEMatrix4x4::CreateLookAt( SSEVector3( 2, 10,
			0 ), SSEVector3( 0, 0, 0 ), SSEVector3( 0, 1, 0 ) ).TransposedCopy().GetAsFloatArray( tmp );
		matrix = D3DXMATRIX( tmp );
		m_Device->SetTransform( D3DTS_VIEW, &matrix );
		m_Device->SetRenderState( D3DRS_AMBIENT, RGB( 255, 255, 255 ) );

		m_Device->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );

		m_Device->SetRenderState( D3DRS_FILLMODE, D3DFILL_WIREFRAME );

		m_Device->SetRenderState( D3DRS_ZENABLE, D3DZB_TRUE );

		// m_Device->SetFVF( ( D3DFVF_XYZ | D3DFVF_DIFFUSE ) );
	}

	const NiFrame::RenderDeviceParams* D3DRenderDevice::GetRenderParams( void ) const
	{
		return m_AdapterParameters[ m_CurrentDevice ];
	}

	void D3DRenderDevice::Initialize()
	{
		m_pD3D = Direct3DCreate9( D3D_SDK_VERSION );

		if( m_pD3D == nullptr )
		{
			throw new exception( "Failed to load DirectX\nInstall the latest DirectX version" );
		}

		uint32 numAdapters = m_pD3D->GetAdapterCount();

		if( numAdapters == 0 )
		{
			throw new exception( "Found no DirectX Adapters" );
		}

		D3DADAPTER_IDENTIFIER9 tmp_identifier;

		for( uint32 i = 0; i < numAdapters; i++ )
		{
			if( FAILED( m_pD3D->GetAdapterIdentifier( i, 0, &tmp_identifier ) ) )
			{
				throw new exception( "Failed to get Adapter identifier" );
			}
			else
			{
				m_AdapterParameters.push_back( new RenderDeviceParams() );
				RenderDeviceParameterList* paramList = m_AdapterParameters[ i ]->GetParameters();

				LoadDeviceTypeSelection( i, paramList );

				LoadFullScreenSelection( paramList );

				LoadBufferTypeSelection( i, paramList );

				// Load Resolutions
				LoadDeviceResolutions( i, paramList );

				LoadZBufferTypeSelection( i, paramList );

				LoadMultiSamples( i, paramList );

				LoadMultiSampleQualities( i, paramList );
			}
		}
	}

	void D3DRenderDevice::LoadDeviceResolutions( uint32 deviceID, RenderDeviceParameterList* paramList )
	{
		uint32 videoModeCount = m_pD3D->GetAdapterModeCount( deviceID, GetCurrentBufferFormat() );
		D3DDISPLAYMODE* displayModes = new D3DDISPLAYMODE[ videoModeCount ];

		vector< D3DResolution* >::type* d3dResolutions = new vector< D3DResolution* >::type();

		vector< IStringableObject* >::type* modeVector = new vector< IStringableObject* >::type();

		for( uint32 videoMode = 0; videoMode < videoModeCount; videoMode++ )
		{
			m_pD3D->EnumAdapterModes( deviceID, GetCurrentBufferFormat(), videoMode, &displayModes[ videoMode ] );
			D3DDISPLAYMODE* d3dMode = new D3DDISPLAYMODE( displayModes[ videoMode ] );

			D3DResolution* resolution = new D3DResolution( d3dMode );
			d3dResolutions->push_back( resolution );
			modeVector->push_back( resolution );
		}

		m_DeviceResolutions->push_back( d3dResolutions );

		( *paramList )[ VIDEOMODE ] = modeVector;

		delete displayModes;
	}

	void D3DRenderDevice::LoadFullScreenSelection( RenderDeviceParameterList* paramList )
	{
		vector< StringableBool* >::type* modes = new vector< StringableBool* >::type();

		vector< IStringableObject* >::type* paramListMember = new vector< IStringableObject* >::type();

		modes->push_back( new StringableBool( false ) );
		modes->push_back( new StringableBool( true ) );

		for( auto iterator = modes->begin(); iterator != modes->end(); ++iterator )
		{
			paramListMember->push_back( *iterator );
		}

		( *paramList )[ WINDOWED ] = paramListMember;

		m_Windowed->push_back( modes );
	}

	void D3DRenderDevice::LoadDeviceTypeSelection( uint32 adapterID, RenderDeviceParameterList* paramList )
	{
		vector< D3DDevTypeStringable* >::type* devType = new vector< D3DDevTypeStringable* >::type();

		vector< IStringableObject* >::type* paramListVector = new vector< IStringableObject* >::type();

		devType->push_back( new D3DDevTypeStringable( D3DDEVTYPE_HAL ) );
		devType->push_back( new D3DDevTypeStringable( D3DDEVTYPE_REF ) );

		for( auto iterator = devType->begin(); iterator != devType->end(); ++iterator )
		{
			paramListVector->push_back( *iterator );
		}

		( *paramList )[ DEVICE_TYPE ] = paramListVector;

		m_D3DDevTypes->push_back( devType );
	}

	void D3DRenderDevice::LoadBufferTypeSelection( uint32 adapterID, RenderDeviceParameterList* paramList )
	{
		vector< BufferTypeStringable* >::type* bufferTypes = new vector< BufferTypeStringable* >::type();

		vector< IStringableObject* >::type* paramListVector = new vector< IStringableObject* >::type();

		vector< D3DFORMAT >::type* vec = new vector< D3DFORMAT >::type();

		FillBufferTypeVector( vec );
		D3DDISPLAYMODE mode = D3DDISPLAYMODE();
		m_pD3D->GetAdapterDisplayMode( adapterID, &mode );

		for( vector< D3DFORMAT >::iterator iterator = vec->begin(); iterator != vec->end(); ++iterator )
		{
			if(
				m_pD3D->CheckDeviceFormat(
				adapterID, GetCurrentDevType(), mode.Format, D3DUSAGE_RENDERTARGET, D3DRTYPE_SURFACE,
				*iterator ) == D3D_OK
			)
			{
				// Check if BackBuffer is valid
				if( m_pD3D->CheckDeviceType( adapterID, GetCurrentDevType(), mode.Format, *iterator,
					GetWindowed() ) == D3D_OK )
				{
					bufferTypes->push_back( new BufferTypeStringable( *iterator ) );
				}
			}
		}

		SAFE_DELETE( vec )

		for( auto iterator = bufferTypes->begin(); iterator != bufferTypes->end(); ++iterator )
		{
			paramListVector->push_back( *iterator );
		}

		( *paramList )[ BUFFERTYPE ] = paramListVector;

		m_BufferTypes->push_back( bufferTypes );
	}

	void D3DRenderDevice::LoadZBufferTypeSelection( uint32 adapterID, RenderDeviceParameterList* paramList )
	{
		vector< BufferTypeStringable* >::type* zBufferTypes = new vector< BufferTypeStringable* >::type();

		vector< IStringableObject* >::type* paramListVector = new vector< IStringableObject* >::type();

		vector< D3DFORMAT >::type vec = vector< D3DFORMAT >::type();

		FillBufferTypeVector( &vec );
		D3DDISPLAYMODE mode = D3DDISPLAYMODE();
		m_pD3D->GetAdapterDisplayMode( adapterID, &mode );

		for( vector< D3DFORMAT >::iterator iterator = vec.begin(); iterator != vec.end(); ++iterator )
		{
			// Check if ZBuffer is valid
			if(
				m_pD3D->CheckDeviceFormat(
				adapterID, GetCurrentDevType(), mode.Format, D3DUSAGE_DEPTHSTENCIL, D3DRTYPE_SURFACE, *iterator )
				== D3D_OK
			)
			{
				if(
					m_pD3D->CheckDepthStencilMatch(
					adapterID, GetCurrentDevType(), mode.Format, GetCurrentBufferFormat(), *iterator ) == D3D_OK
				)
				{
					zBufferTypes->push_back( new BufferTypeStringable( *iterator ) );
				}
			}
		}

		for( auto iterator = zBufferTypes->begin(); iterator != zBufferTypes->end(); ++iterator )
		{
			paramListVector->push_back( *iterator );
		}

		( *paramList )[ ZBUFFERTYPE ] = paramListVector;

		m_ZBufferTypes->push_back( zBufferTypes );
	}

	void D3DRenderDevice::LoadMultiSamples( uint32 adapterID, RenderDeviceParameterList* paramList )
	{
		vector< D3DMultiSample* >::type* multiSampleTypes = new vector< D3DMultiSample* >::type();

		vector< IStringableObject* >::type* paramListVector = new vector< IStringableObject* >::type();

		for( uint32 typeCount = D3DMULTISAMPLE_NONE; typeCount <= D3DMULTISAMPLE_16_SAMPLES; ++typeCount )
		{
			D3DMULTISAMPLE_TYPE type = static_cast< D3DMULTISAMPLE_TYPE >( typeCount );
			DWORD qualityLevels;

			if(
				m_pD3D->CheckDeviceMultiSampleType(
				adapterID, GetCurrentDevType(), GetCurrentBufferFormat(), GetWindowed(), type,
				&qualityLevels ) == D3D_OK
			)
			{
				multiSampleTypes->push_back( new D3DMultiSample( type ) );
			}
		}

		for( auto iterator = multiSampleTypes->begin(); iterator != multiSampleTypes->end(); ++iterator )
		{
			paramListVector->push_back( *iterator );
		}

		( *paramList )[ MULTISAMPLE_TYPE ] = paramListVector;

		m_MultiSampleTypes->push_back( multiSampleTypes );
	}

	void D3DRenderDevice::LoadMultiSampleQualities( uint32 adapterID, RenderDeviceParameterList* paramList )
	{
		vector< D3DMultiSampleQuality* >::type* multiSampleQualities = new vector< D3DMultiSampleQuality* >::type();

		vector< IStringableObject* >::type* paramListVector = new vector< IStringableObject* >::type();

		D3DMULTISAMPLE_TYPE mSType = GetCurrentMultiSampleType();
		DWORD qualityLevels;

		if(
			m_pD3D->CheckDeviceMultiSampleType(
			adapterID, GetCurrentDevType(), GetCurrentBufferFormat(), GetWindowed(), mSType, &qualityLevels ) == D3D_OK
		)
		{
			for( DWORD i = 0; i < qualityLevels; i++ )
			{
				multiSampleQualities->push_back( new D3DMultiSampleQuality( i ) );
			}
		}

		for( auto iterator = multiSampleQualities->begin(); iterator != multiSampleQualities->end(); ++iterator )
		{
			paramListVector->push_back( *iterator );
		}

		( *paramList )[ MULTISAMPLE_QUALITY ] = paramListVector;

		m_MultiSampleQualities->push_back( multiSampleQualities );
	}

	void D3DRenderDevice::FillBufferTypeVector( vector< D3DFORMAT >::type* vec )
	{
		vec->push_back( D3DFMT_X8R8G8B8 );
		vec->push_back( D3DFMT_R8G8B8 );
		vec->push_back( D3DFMT_A8R8G8B8 );
		vec->push_back( D3DFMT_R5G6B5 );
		vec->push_back( D3DFMT_X1R5G5B5 );
		vec->push_back( D3DFMT_A1R5G5B5 );
		vec->push_back( D3DFMT_A4R4G4B4 );
		vec->push_back( D3DFMT_R3G3B2 );
		vec->push_back( D3DFMT_A8 );
		vec->push_back( D3DFMT_A8R3G3B2 );
		vec->push_back( D3DFMT_X4R4G4B4 );
		vec->push_back( D3DFMT_A2B10G10R10 );
		vec->push_back( D3DFMT_A8B8G8R8 );
		vec->push_back( D3DFMT_X8B8G8R8 );
		vec->push_back( D3DFMT_G16R16 );
		vec->push_back( D3DFMT_A2R10G10B10 );
		vec->push_back( D3DFMT_A16B16G16R16 );
		vec->push_back( D3DFMT_A8P8 );
		vec->push_back( D3DFMT_P8 );
		vec->push_back( D3DFMT_L8 );
		vec->push_back( D3DFMT_A8L8 );
		vec->push_back( D3DFMT_A4L4 );
		vec->push_back( D3DFMT_V8U8 );
		vec->push_back( D3DFMT_L6V5U5 );
		vec->push_back( D3DFMT_X8L8V8U8 );
		vec->push_back( D3DFMT_Q8W8V8U8 );
		vec->push_back( D3DFMT_V16U16 );
		vec->push_back( D3DFMT_A2W10V10U10 );
		vec->push_back( D3DFMT_UYVY );
		vec->push_back( D3DFMT_R8G8_B8G8 );
		vec->push_back( D3DFMT_YUY2 );
		vec->push_back( D3DFMT_G8R8_G8B8 );
		vec->push_back( D3DFMT_DXT1 );
		vec->push_back( D3DFMT_DXT2 );
		vec->push_back( D3DFMT_DXT3 );
		vec->push_back( D3DFMT_DXT4 );
		vec->push_back( D3DFMT_DXT5 );
		vec->push_back( D3DFMT_D16_LOCKABLE );
		vec->push_back( D3DFMT_D32 );
		vec->push_back( D3DFMT_D15S1 );
		vec->push_back( D3DFMT_D24S8 );
		vec->push_back( D3DFMT_D24X8 );
		vec->push_back( D3DFMT_D24X4S4 );
		vec->push_back( D3DFMT_D16 );
		vec->push_back( D3DFMT_D32F_LOCKABLE );
		vec->push_back( D3DFMT_D24FS8 );

		/* D3D9Ex only -- */
#if !defined( D3D_DISABLE_9EX )

		/* Z-Stencil formats valid for CPU access */
		vec->push_back( D3DFMT_D32_LOCKABLE );
		vec->push_back( D3DFMT_S8_LOCKABLE );

#endif	// !D3D_DISABLE_9EX

		/* -- D3D9Ex only */

		vec->push_back( D3DFMT_L16 );

		vec->push_back( D3DFMT_VERTEXDATA );
		vec->push_back( D3DFMT_INDEX16 );
		vec->push_back( D3DFMT_INDEX32 );

		vec->push_back( D3DFMT_Q16W16V16U16 );

		vec->push_back( D3DFMT_MULTI2_ARGB8 );

		// Floating point surface formats

		// s10e5 formats (16-bits per channel)
		vec->push_back( D3DFMT_R16F );
		vec->push_back( D3DFMT_G16R16F );
		vec->push_back( D3DFMT_A16B16G16R16F );

		// IEEE s23e8 formats (32-bits per channel)
		vec->push_back( D3DFMT_R32F );
		vec->push_back( D3DFMT_G32R32F );
		vec->push_back( D3DFMT_A32B32G32R32F );

		vec->push_back( D3DFMT_CxV8U8 );

		/* D3D9Ex only -- */
#if !defined( D3D_DISABLE_9EX )

		// Monochrome 1 bit per pixel format
		vec->push_back( D3DFMT_A1 );

		// 2.8 biased fixed point
		vec->push_back( D3DFMT_A2B10G10R10_XR_BIAS );

		// Binary format indicating that the data has no inherent type
		vec->push_back( D3DFMT_BINARYBUFFER );
#endif	// !D3D_DISABLE_9EX

		/* -- D3D9Ex only */
		vec->push_back( D3DFMT_FORCE_DWORD );
	}

	_D3DDEVTYPE D3DRenderDevice::GetCurrentDevType()
	{
		return ( *( ( *m_D3DDevTypes )[ m_CurrentDevice ] ) )[ ( *m_SelectedValues )[ DEVICE_TYPE ] ]->GetType();
	}

	D3DFORMAT D3DRenderDevice::GetCurrentBufferFormat()
	{
		return ( *( ( *m_BufferTypes )[ m_CurrentDevice ] ) )[ ( *m_SelectedValues )[ BUFFERTYPE ] ]->GetFormat();
	}

	bool D3DRenderDevice::GetWindowed()
	{
		return ( *( ( *m_Windowed )[ m_CurrentDevice ] ) )[ ( *m_SelectedValues )[ WINDOWED ] ]->GetBool();
	}

	D3DMULTISAMPLE_TYPE D3DRenderDevice::GetCurrentMultiSampleType()
	{
		return ( *( ( *m_MultiSampleTypes )[ m_CurrentDevice ] ) )[ ( *m_SelectedValues )[ MULTISAMPLE_TYPE ] ]->
			   GetMultiSampleType();
	}

	const String D3DRenderDevice::GetGetMultisampleQualityID() const
	{
		return MULTISAMPLE_QUALITY;
	}

	const String D3DRenderDevice::GetGetDeviceTypeID() const
	{
		return DEVICE_TYPE;
	}

	const String D3DRenderDevice::GetGetMultisampleID() const
	{
		return MULTISAMPLE_TYPE;
	}

	const String D3DRenderDevice::GetGetWindowedID() const
	{
		return WINDOWED;
	}

	const String D3DRenderDevice::GetGetZBufferTypeID() const
	{
		return ZBUFFERTYPE;
	}

	const String D3DRenderDevice::GetGetBufferID() const
	{
		return ZBUFFERTYPE;
	}

	const String D3DRenderDevice::GetGetVideoModeID() const
	{
		return VIDEOMODE;
	}

	void D3DRenderDevice::CreateVertexBuffer( NFSize size, IDirect3DVertexBuffer9** buffer )
	{
		m_Device->CreateVertexBuffer( ( UINT )size * sizeof( D3DVertex ), D3DUSAGE_WRITEONLY, D3DVertex_FVF,
			D3DPOOL_MANAGED, buffer, nullptr );
	}

	void D3DRenderDevice::DestroyVertexBuffer( IDirect3DVertexBuffer9** vertexBuffer )
	{
		( *vertexBuffer )->Release();
		( *vertexBuffer ) = nullptr;
	}

	void D3DRenderDevice::DestroyIndexBuffer( IDirect3DIndexBuffer9** buffer )
	{
		( *buffer )->Release();
		( *buffer ) = nullptr;
	}

	void D3DRenderDevice::CreateIndexBuffer( NFSize size, IDirect3DIndexBuffer9** buffer )
	{
		m_Device->CreateIndexBuffer( ( UINT )size * sizeof( uint32 ), D3DUSAGE_WRITEONLY, D3DFMT_INDEX32,
			D3DPOOL_MANAGED, buffer, nullptr );
	}

	MeshPtr D3DRenderDevice::CreateMesh( VertexBuffer::type* vertexBuffer, IndexBuffer::type* indexBuffer )
	{
		IDirect3DVertexBuffer9* vBuffer = nullptr;
		IDirect3DIndexBuffer9* iBuffer = nullptr;
		CreateVertexBuffer( vertexBuffer->size(), &vBuffer );
		CreateIndexBuffer( indexBuffer->size(), &iBuffer );
		return MeshPtr( new D3DMesh( vertexBuffer, indexBuffer, vBuffer, iBuffer ) );
	}

	void D3DRenderDevice::RenderMesh( MeshPtr mesh )
	{
		D3DMesh* d3dMesh = static_cast< D3DMesh* >( *mesh );

		m_Device->SetStreamSource( 0, d3dMesh->GetVertexBuffer(), 0, sizeof( D3DVertex ) );
		m_Device->SetFVF( D3DVertex_FVF );
		m_Device->SetIndices( d3dMesh->GetIndexBuffer() );
		m_Device->DrawIndexedPrimitive( D3DPT_TRIANGLELIST, 0, 0,
			( UINT )d3dMesh->GetVertexCount(), 0, ( UINT )d3dMesh->GetIndexCount() / 3 );
	}

	void D3DRenderDevice::DestroyMesh( MeshPtr mesh )
	{
		D3DMesh* d3dMesh = static_cast< D3DMesh* >( *mesh );
		DestroyVertexBuffer( &d3dMesh->m_GPU_vertexBuffer );
		d3dMesh->m_GPU_vertexBuffer = nullptr;
		DestroyIndexBuffer( &d3dMesh->m_GPU_indexBuffer );
		d3dMesh->m_GPU_indexBuffer = nullptr;

		// delete d3dMesh;
	}

	const uint32 D3DRenderDevice::GetCurrentDeviceID( void ) const
	{
		return m_CurrentDevice;
	}

	void D3DRenderDevice::SetCurrentDeviceID( uint32 id )
	{
		assert( id < GetDeviceCount() && "Set Invalid device id" );
		m_CurrentDevice = id;
	}

	const uint32 D3DRenderDevice::GetDeviceCount( void ) const
	{
		return m_pD3D->GetAdapterCount();
	}

	String D3DRenderDevice::GetDeviceName( uint32 id ) const
	{
		D3DADAPTER_IDENTIFIER9 identifier;
		m_pD3D->GetAdapterIdentifier( id, 0, &identifier );

		return String( identifier.Description );
	}
}
