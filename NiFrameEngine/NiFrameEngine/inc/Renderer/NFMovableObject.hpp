#pragma once
#ifndef NiFrameMovableObject_h__
  #define NiFrameMovableObject_h__

  #include "NFEnginePCH.hpp"
  #include "NFReferenceCounted.hpp"
#include "Renderer/NFTransform.hpp"

namespace nfe
{
  class NIFRAME_API MoveableObject
  {
  public:

    enum MoveableObjectType
    {
      ENTITIY,
      LIGHT,
      SCENENODE
    };


    MoveableObject(
      IAllocator* allocator = nullptr,
      const String& name = "",
      MoveableObjectType type = MoveableObjectType::SCENENODE,
      const ::nfe::Transform& transform = ::nfe::Transform() );
    ~MoveableObject();

    MoveableObjectType GetType( void ) const;

    void SetPosition( const Vector3& newPos );
    const Vector3& GetPosition( void ) const;

    void SetOrientation( const Rotator& newOrientation );
    const Rotator& GetOrientation( void ) const;

    const Vector3& GetScale( void ) const;
    void SetScale( const Vector3& val );

    const String& GetName( void ) const;
    void SetName( const String& name );

    const Transform& GetTransformation( void ) const;

    void AddChild( ReferenceCounted< MoveableObject > object );
    void RemoveChild( const String& name );
    void RemoveAllChildrenRecursive();
    void RemoveAllChildren();
    MoveableObject* Parent() const;

    const Vector<ReferenceCounted<MoveableObject>>& Children() const;

  protected:
    Vector< ReferenceCounted< MoveableObject > > m_Children;

    String m_Name;

    nfe::Transform m_Transform;
    MoveableObjectType m_Type;

    IAllocator* m_Allocator;

    MoveableObject* m_Parent;
  private:
  };

  NIFRAME_TPL_EXPORT template class NIFRAME_API ReferenceCounted< MoveableObject >;

  typedef ReferenceCounted< MoveableObject > MoveableObjectPtr;
}

#endif  // NiFrameMovableObject_h__
