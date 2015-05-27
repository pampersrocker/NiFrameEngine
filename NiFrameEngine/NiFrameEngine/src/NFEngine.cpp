#include "NFEnginePCH.hpp"
#include "NFEngine.hpp"
#include "Memory/NFDefaultAllocator.hpp"
#include "Platform/NFPlatform.hpp"

using namespace nfe;

// Storage for the Most Basic Engine and default allocator.
// Before the engine runs there is no default allocator instantiated
uint8 engineMem[ sizeof( Engine ) ];

uint8 defaultAllocMem[ sizeof( DefaultAllocator ) ];

Engine* nfe::GEngine = new (engineMem) Engine();


nfe::Engine::Engine()
{
}

nfe::Engine::~Engine()
{
}

void nfe::Engine::Shutdown()
{
  this->~Engine();
  GEngine = nullptr;
}

void nfe::Engine::Run()
{

}

void nfe::Engine::Update()
{
  if( GPlatform )
  {
    GPlatform->Update();
  }
}

void nfe::Engine::Initialize()
{
  NF_ASSERT( GPlatform, "Not platform on initialization!" );
  GPlatform->Initialize();
}

void nfe::Engine::Release()
{
  NF_ASSERT( GPlatform, "Not platform on release!" );
  GPlatform->Release();

}
