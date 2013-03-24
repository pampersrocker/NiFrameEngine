#include "NiFrameRendererPCH.h"
#include "NiFrameD3DResolution.h"

namespace NiFrame
{


	D3DResolution::D3DResolution( D3DDISPLAYMODE* displayMode ) :
		Resolution(displayMode->Width, displayMode->Height, displayMode->RefreshRate ),
		m_DisplayMode( displayMode )
	{

	}

	D3DResolution::~D3DResolution()
	{
		SAFE_DELETE( m_DisplayMode )
	}

}