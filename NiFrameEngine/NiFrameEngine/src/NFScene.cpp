#include "NFEnginePCH.hpp"
#include "NFScene.hpp"

namespace nfe
{
  Scene::Scene( const String& sceneName ) :
    m_RootSceneNode( SceneNodePtr( new SceneNode( sceneName ) ) )
  {

  }

  Scene::~Scene()
  {

  }

  nfe::SceneNodePtr Scene::GetRootSceneNode( void ) const
  {
    return m_RootSceneNode;
  }

}

