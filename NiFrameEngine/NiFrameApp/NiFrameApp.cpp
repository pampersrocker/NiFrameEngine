// NiFrameApp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "NiFrameRenderer.h"
#include "NiFrameRenderDevice.h"
#include <iostream>
#include "NiFrameRenderDeviceParameters.h"
#include "StringableObject.h"
#include <iosfwd>


using namespace NiFrame;
using namespace std;

typedef NiFrame::vector< IStringableObject*>::type ValueList;

void SelectParameters( RenderDevice* device, NiFrame::map< NiFrame::String, uint32>::type &selectedValues );
int main(int argc, _TCHAR* argv[])
{
	

	NiFrame::map< NiFrame::String, uint32>::type selectedValues;

	NiFrame::Renderer renderer;

	renderer.CreateDevice("DirectX");

	RenderDevice* device = renderer.GetDevice();

	device->Initialize();

	SelectParameters(device, selectedValues);


	if ( SDL_Init( SDL_INIT_VIDEO ) < 0 || !SDL_GetVideoInfo() )
	{
		return 0;
	}

	device->SetupDevice(GetActiveWindow(), selectedValues );

	SDL_SetVideoMode( 800, 600, SDL_GetVideoInfo()->vfmt->BitsPerPixel, SDL_RESIZABLE);
	
	return 0;
}

void SelectParameters( RenderDevice* device, NiFrame::map< NiFrame::String, uint32>::type &selectedValues )
{
	const RenderDeviceParams* devParams = device->GetRenderParams();
	int counter = 0;
	int selectedValue = 0;

	cout << "Fullscreen?" << endl;
	ValueList windowedParams = devParams->GetParamterValues("Windowed");
	counter = 0;
	for (auto it : windowedParams)
	{
		cout << counter << ": " << it->ToString() << endl;
		++counter;
	}
	cin >> selectedValue;
	selectedValues["Windowed"] = selectedValue;

	cout << "Select Video Mode:" << endl;
	ValueList params = device->GetRenderParams()->GetParamterValues("VideoMode");
	counter = 0;
	selectedValue = 0;
	for (auto it : params)
	{
		cout << counter << ": " << it->ToString() << endl;
		++counter;
	}
	cin >> selectedValue;
	selectedValues["VideoMode"] = selectedValue;
}

