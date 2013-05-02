#include "NiFrameEnginePCH.h"
#include "NiFrameSceneNode.h"

namespace NiFrame
{
	SceneNode::SceneNode(
		const String& name,
		const Vector3& position /*= Vector3( 0 )*/,
		const Matrix4x4& orientation /*= Matrix4x4::IDENTITY */,
		const Vector3& scale ) :
		MoveableObject( name, MoveableObject::SCENENODE, position, orientation, scale )
	{
	}

	SceneNode::~SceneNode()
	{
	}

	NiFrame::SceneNodePtr SceneNode::CreateChildSceneNode( const String& name )
	{
		//TODO: Create an actual sceneNode
		return SceneNodePtr( nullptr );
	}

	void SceneNode::RemoveChild( const uint32& hash )
	{
	}

	void SceneNode::RemoveChild( const String& name )
	{
	}

	void SceneNode::AddChild( MoveableObjectPtr object )
	{
	}
}
