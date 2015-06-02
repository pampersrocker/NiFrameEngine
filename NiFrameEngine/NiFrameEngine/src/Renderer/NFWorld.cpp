#include "NFEnginePCH.hpp"
#include "Renderer/NFWorld.hpp"

using namespace nfe;

nfe::World::World( IAllocator* allocator /*= nullptr */ ) :
m_Allocator(allocator, 0U, "WorldAllocator")
{

}

void nfe::World::RootSceneNode( const nfe::SceneNodePtr& val )
{
  m_RootSceneNode = val;
}

const nfe::SceneNodePtr& nfe::World::RootSceneNode() const
{
  return m_RootSceneNode;
}


void nfe::World::Initialize()
{
  m_RootSceneNode = nfnew<SceneNode>( &m_Allocator, "WorldNode", Transform() );
}

void nfe::World::Release()
{
  m_RootSceneNode.SetNull();
}
