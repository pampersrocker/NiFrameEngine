#pragma once
#ifndef NiFrameSceneNode_h__
  #define NiFrameSceneNode_h__

  #include "NFEnginePCH.hpp"
  #include "NFReferenceCounted.hpp"
  #include "NFMovableObject.hpp"

namespace nfe
{


  class SceneNode;

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

    vector< MoveableObjectPtr > m_Children;
  };

}

#endif  // NiFrameSceneNode_h__
