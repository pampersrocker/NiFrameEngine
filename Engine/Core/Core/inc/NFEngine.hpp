#pragma once
#include "Memory/NFIAllocator.hpp"
#include "NFSTL/NFVector.hpp"
#include "Renderer/NFWorld.hpp"
#include "Subsystems/NFSubsystem.hpp"
#include "Utils/NFEnumUtils.hpp"

namespace nfe
{
  class NIFRAME_API Engine
  {
  public:
    Engine();
    ~Engine();


    void Run();
    void Initialize();
    void Update();
    void Release();

    void Shutdown();

    void AddWorld( World* world );
    void RemoveWorld( World* world );


    void AddSubsystem( ISubsystem* system );
    void RemoveSubsystems( ISubsystem* system );

    const Vector< World* >& Worlds() const;

  private:

    Vector< World* > m_Worlds;
    Vector< ISubsystem* > m_Subsystems;

  };

  NIFRAME_API extern Engine* GEngine;


}

#pragma warning(disable : 4251)

