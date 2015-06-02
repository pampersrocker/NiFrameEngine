#pragma once
#include "Memory/NFIAllocator.hpp"
#include "NFSTL/NFVector.hpp"
#include "Renderer/NFWorld.hpp"

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

    const Vector< World* >& Worlds() const;

  private:

    Vector< World* >* m_Worlds;

  };

  NIFRAME_API extern Engine* GEngine;

}
