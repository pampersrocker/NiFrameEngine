#pragma once
#ifndef NiFrameScene_h__
#define NiFrameScene_h__

#include "NiFrameEnginePCH.hpp"
#include "NiFrameSceneNode.hpp"


namespace NiFrame
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
