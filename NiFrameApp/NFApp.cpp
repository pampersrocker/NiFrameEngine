// NiFrameApp.cpp : Defines the entry point for the console application.
//

#include "stdafx.hpp"
#include "Renderer/NFRenderer.hpp"
#include "Renderer/NFRenderDevice.hpp"
#include <iostream>
#include "Renderer/NFRenderDeviceParameters.hpp"
#include "NFStringableObject.hpp"
#include <iosfwd>
#include "Renderer/NFResolution.hpp"


using namespace nfe;
using namespace std;

typedef nfe::vector< IStringableObject*> ValueList;

void SelectParameters( RenderDevice* device, nfe::map< nfe::String, uint32> &selectedValues );
int main(int argc, _TCHAR* argv[])
{
  bool bShutdown = false;
  nfe::map< nfe::String, uint32> selectedValues;

  nfe::Renderer renderer;
  cout << "Creating D3DX....";
  renderer.CreateDevice("DirectX");

  RenderDevice* device = renderer.GetDevice();

  device->Initialize();

  cout << "done" << endl;

  const Resolution& res = device->GetRenderParams().InternalResolution();

  if ( SDL_Init( SDL_INIT_VIDEO ) < 0 || !SDL_GetVideoInfo() )
  {
    return 0;
  }
  SDL_SetVideoMode( res.GetWidth(), res.GetHeight(), SDL_GetVideoInfo()->vfmt->BitsPerPixel, SDL_RESIZABLE);

  RenderWindow Window;
  Window.Initialize(GetActiveWindow());

  device->SetupDevice(Window, device->GetRenderParams());

  VertexBuffer* vBuffer = new VertexBuffer();
  vBuffer->push_back(Vector3(0,0,0)); // 0
  vBuffer->push_back(Vector3(0,0,1)); // 1
  vBuffer->push_back(Vector3(1,0,0)); // 2
  vBuffer->push_back(Vector3(1,0,1)); // 3
  vBuffer->push_back(Vector3(0,1,0)); // 4
  vBuffer->push_back(Vector3(0,1,1)); // 5
  vBuffer->push_back(Vector3(1,1,0)); // 6
  vBuffer->push_back(Vector3(1,1,1)); // 7

  IndexBuffer* iBuffer = new IndexBuffer();
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



  SDL_Event event;
  while( !bShutdown )
  {
    if( SDL_PollEvent( &event ) )
    {
      switch( event.type )
      {

      case SDL_KEYDOWN:
        if ( event.key.keysym.sym == SDLK_ESCAPE )
        {
          bShutdown = true;
        }
        break;
      case SDL_QUIT:
        bShutdown = true;
        break;
      }
    }


  }

  return 0;
}