#pragma once
#ifndef NiFrameScene_h__
#define NiFrameScene_h__

#include "NFEnginePCH.hpp"
#include "NFSceneNode.hpp"


namespace nfe
{
  class NIFRAME_DLL_EXPORT Scene
  {
  public:
    Scene( const String& sceneName );
    ~Scene();

    SceneNodePtr GetRootSceneNode( void ) const;

  protected:

  private:

    String m_SceneName;

    SceneNodePtr m_RootSceneNode;

  };

}

#endif // NiFrameScene_h__
