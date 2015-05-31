#pragma once

#include "NFEnginePCH.hpp"
#include "NFMovableObject.hpp"
#include "NFSceneNode.hpp"
#include "Memory/NFProxyAllocator.hpp"

namespace nfe
{
  class NIFRAME_API World
  {
  public:
    World( IAllocator* allocator = nullptr );

    void Initialize();

    void Release();

    const nfe::SceneNodePtr& RootSceneNode() const;
    void RootSceneNode( const nfe::SceneNodePtr& val );
  private:

    ProxyAllocator m_Allocator;

    SceneNodePtr m_RootSceneNode;
  };
}
