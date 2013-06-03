#pragma once
#ifndef NiFrameSceneNode_h__
	#define NiFrameSceneNode_h__

	#include "NiFrameEnginePCH.hpp"
	#include "NiFrameReferenceCounted.hpp"
	#include "NiFrameMovableObject.hpp"

namespace NiFrame
{
	
	
	class SceneNode;

	EXPORT_STL( vector< MoveableObjectPtr > )

	TYPEDEF_EXPORT_REFCOUNT_PTR( SceneNode )


	class NIFRAME_DLL_EXPORT SceneNode : public MoveableObject
	{
	public:

		SceneNode(
			const String& name,
			const Vector3& position = Vector3( 0 ),
			const Matrix4x4& orientation = Matrix4x4::IDENTITY,
			const Vector3& scale = Vector3( 1.0f )
			);
		~SceneNode();

		void AddChild( MoveableObjectPtr object );
		void RemoveChild( const String& name );
		void RemoveChild( const uint32& hash );

		SceneNodePtr CreateChildSceneNode( const String& name );

	private:

		vector< MoveableObjectPtr >::type m_Children;
	};

}

#endif	// NiFrameSceneNode_h__
