#include "NFEnginePCH.hpp"
#include "Renderer/NFMovableObject.hpp"
#include "Platform/NFPlatform.hpp"

namespace nfe
{
  MoveableObject::MoveableObject(
    IAllocator* allocator,
    const String& name,
    MoveableObjectType type,
    const Transform& transform) :
    m_Children(allocator),
    m_Name( name ),
    m_Transform(transform),
    m_Type( type ),
    m_Allocator(allocator),
    m_Parent(nullptr)
  {
    if( m_Allocator == nullptr )
    {
      m_Allocator = NFPlatform::GetDefaultAllocator();
    }
  }

  MoveableObject::~MoveableObject()
  {
  }

  nfe::MoveableObject::MoveableObjectType MoveableObject::GetType( void ) const
  {
    return m_Type;
  }

  void MoveableObject::SetPosition( const Vector3& newPos )
  {
    m_Transform.Position(newPos);
  }

  const Vector3& MoveableObject::GetPosition( void ) const
  {
    return m_Transform.Position();
  }

  void MoveableObject::SetOrientation( const Rotator& newOrientation )
  {
    m_Transform.Rotation(newOrientation);
  }

  const Rotator& MoveableObject::GetOrientation( void ) const
  {
    return m_Transform.Rotation();
  }

  const String& MoveableObject::GetName( void ) const
  {
    return m_Name;
  }

  void MoveableObject::SetName( const String& name )
  {
    m_Name = name;
  }

  void MoveableObject::SetScale( const Vector3& val )
  {
    m_Transform.Scale();
  }

  const Vector3& MoveableObject::GetScale( void ) const
  {
    return m_Transform.Scale();
  }

  void MoveableObject::RemoveChild( const String& name )
  {
    for( MoveableObjectPtr& child : m_Children )
    {
      if( child->GetName() == name )
      {
        NF_ASSERT( child->m_Parent == this, "Cannot remove child if this is not its parent!" );
        m_Children.Remove( child );
        child->m_Parent = nullptr;
        break;
      }
    }
  }

  void MoveableObject::RemoveChild( ReferenceCounted<MoveableObject> object )
  {
    NF_ASSERT( object->m_Parent == this, "Cannot remove child if this is not its parent!" );
    m_Children.Remove( object );
    object->m_Parent = nullptr;
  }

  void MoveableObject::AddChild( MoveableObjectPtr object )
  {
    m_Children.Add( object );
    object->m_Parent = this;
  }

  void MoveableObject::RemoveAllChildrenRecursive()
  {
    for( auto& child : m_Children )
    {
      child->RemoveAllChildrenRecursive();
    }
    RemoveAllChildren();
  }

  void MoveableObject::RemoveAllChildren()
  {
    for( auto& child : m_Children )
    {
      child->m_Parent = nullptr;
    }
    m_Children.Clear();
  }

  MoveableObject* MoveableObject::Parent() const
  {
    return m_Parent;
  }

  const Transform& MoveableObject::GetTransformation( void ) const
  {
    return m_Transform;
  }

  const Vector<ReferenceCounted<MoveableObject>>& MoveableObject::Children() const
  {
    return m_Children;
  }

}
