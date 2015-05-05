#include "NFEnginePCH.hpp"
#include "NFEngine.hpp"
#include "Memory/NFDefaultAllocator.hpp"

using namespace nfe;

// Storage for the Most Basic Engine and default allocator.
// Before the engine runs there is no default allocator instantiated
uint8 engineMem[ sizeof( Engine ) ];

uint8 defaultAllocMem[ sizeof( DefaultAllocator ) ];

Engine* nfe::GEngine = new (engineMem) Engine();

IAllocator* nfe::Engine::GetDefaultAllocator() const
{
  return m_DefaultAllocator;
}

nfe::Engine::Engine()
{
  m_DefaultAllocator = new ( defaultAllocMem ) DefaultAllocator();
}

nfe::Engine::~Engine()
{
  m_DefaultAllocator->~IAllocator();
  m_DefaultAllocator = nullptr;
}

void nfe::Engine::Shutdown()
{
  this->~Engine();
  GEngine = nullptr;
}
