#pragma once
#ifndef NiFrameSceneNode_h__
  #define NiFrameSceneNode_h__

  #include "NFEnginePCH.hpp"
  #include "NFReferenceCounted.hpp"
  #include "NFMovableObject.hpp"
#include "NFSTL/NFVector.hpp"

namespace nfe
{
  class SceneNode;

  typedef ReferenceCounted < SceneNode > SceneNodePtr;

  class NIFRAME_API SceneNode : public MoveableObject
  {
  public:

    SceneNode(
      IAllocator* allocator = nullptr,
      const String& name = "",
      const Transform& transform = Transform()
      );
    ~SceneNode();

    void AddChild( MoveableObjectPtr object );
    void RemoveChild( const String& name );


  private:

    Vector< MoveableObjectPtr > m_Children;
  };

}

#endif  // NiFrameSceneNode_h__
