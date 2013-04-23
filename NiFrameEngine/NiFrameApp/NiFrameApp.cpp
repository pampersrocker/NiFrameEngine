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
	cout << "Creating D3DX....";
	renderer.CreateDevice("DirectX");

	RenderDevice* device = renderer.GetDevice();

	device->Initialize();

	cout << "done" << endl;

	SelectParameters(device, selectedValues);


	if ( SDL_Init( SDL_INIT_VIDEO ) < 0 || !SDL_GetVideoInfo() )
	{
		return 0;
	}
	SDL_SetVideoMode( 800, 600, SDL_GetVideoInfo()->vfmt->BitsPerPixel, SDL_RESIZABLE);

	device->SetupDevice(GetActiveWindow(), selectedValues );

	VertexBuffer::type* vBuffer = new VertexBuffer::type();
	vBuffer->push_back(Vector3(0,0,0)); // 0
	vBuffer->push_back(Vector3(0,0,1)); // 1
	vBuffer->push_back(Vector3(1,0,0)); // 2
	vBuffer->push_back(Vector3(1,0,1)); // 3
	vBuffer->push_back(Vector3(0,1,0)); // 4
	vBuffer->push_back(Vector3(0,1,1)); // 5
	vBuffer->push_back(Vector3(1,1,0)); // 6
	vBuffer->push_back(Vector3(1,1,1)); // 7

	IndexBuffer::type* iBuffer = new IndexBuffer::type();
	iBuffer->push_back(0);
	iBuffer->push_back(1);
	iBuffer->push_back(2);

	iBuffer->push_back(3);
	iBuffer->push_back(1);
	iBuffer->push_back(2);

	iBuffer->push_back(0);
	iBuffer->push_back(4);
	iBuffer->push_back(5);

	iBuffer->push_back(1);
	iBuffer->push_back(0);
	iBuffer->push_back(5);

	Mesh* triangle = device->CreateMesh(vBuffer,iBuffer);

	device->BeginRendering();

	device->RenderMesh(triangle);

	device->EndRendering();

	device->DestroyMesh(triangle);

	SDL_Event event;
	while( SDL_WaitEvent( &event ) )
		switch( event.type )
	{
		case SDL_KEYDOWN:
			if ( event.key.keysym.sym == SDLK_ESCAPE )
			{
				return 0;
			}
			break;
	}

	
	return 0;
}

void SelectParameters( RenderDevice* device, NiFrame::map< NiFrame::String, uint32>::type &selectedValues )
{
	const RenderDeviceParams* devParams = device->GetRenderParams();
	int counter = 0;
	int selectedValue = 0;

	cout << "Windowed?" << endl;
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

