#include "NFEnginePCH.hpp"
#include "Renderer/NFSceneNode.hpp"

namespace nfe
{
  SceneNode::SceneNode(
    IAllocator* allocator,
    const String& name,
    const Transform& transform) :
    MoveableObject(allocator, name, MoveableObject::SCENENODE, transform ),
    m_Children(allocator)
  {
  }

  SceneNode::~SceneNode()
  {
  }

  void SceneNode::RemoveChild( const String& name )
  {
    for( MoveableObjectPtr& child : m_Children )
    {
      if( child->GetName() == name )
      {
        m_Children.Remove( child );
        break;
      }
    }
  }

  void SceneNode::AddChild( MoveableObjectPtr object )
  {
    m_Children.Add( object );
  }
}
