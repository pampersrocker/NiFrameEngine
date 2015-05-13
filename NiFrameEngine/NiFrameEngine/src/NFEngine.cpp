#include "NFEnginePCH.hpp"
#include "NFEngine.hpp"
#include "Memory/NFDefaultAllocator.hpp"

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
