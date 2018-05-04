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

  for( auto& subsystem : m_Subsystems )
  {
    subsystem->Update( 0.016f );
  }
}

void nfe::Engine::Initialize()
{
  NF_ASSERT( GPlatform, "Not platform on initialization!" );
  GPlatform->Initialize();
  new (&m_Worlds) Vector<World*>(GPlatform->GetDefaultAllocator());
  new (&m_Subsystems) Vector<ISubsystem*>(GPlatform->GetDefaultAllocator());

}

void nfe::Engine::Release()
{
  NF_ASSERT( GPlatform, "Not platform on release!" );
  for( auto& system : m_Subsystems )
  {
    system->Release();
  }
  GPlatform->Release();
}

void nfe::Engine::AddWorld( World* world )
{
  m_Worlds.Add( world );
}

void nfe::Engine::RemoveWorld( World* world )
{
  m_Worlds.Remove( world );
}

const Vector< World* >& nfe::Engine::Worlds() const
{
  return m_Worlds;
}

void nfe::Engine::AddSubsystem( ISubsystem* system )
{
  system->Initialize();
  m_Subsystems.Add( system );
}

void nfe::Engine::RemoveSubsystems( ISubsystem* system )
{
  system->Release();
  m_Subsystems.Remove( system );
}
