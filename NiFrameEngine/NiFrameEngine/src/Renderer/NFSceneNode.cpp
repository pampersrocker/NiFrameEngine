#include "NFEnginePCH.hpp"
#include "Renderer/NFSceneNode.hpp"

namespace nfe
{
  SceneNode::SceneNode(
    IAllocator* allocator,
    const String& name,
    const Transform& transform) :
    MoveableObject(allocator, name, MoveableObject::SCENENODE, transform )
  {
  }

  SceneNode::~SceneNode()
  {
  }



}
