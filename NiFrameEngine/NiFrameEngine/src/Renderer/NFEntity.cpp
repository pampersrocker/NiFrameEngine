#include "NFEnginePCH.hpp"
#include "Renderer/NFEntity.hpp"

namespace nfe
{
  Entity::Entity(
    IAllocator* allocator,
    const String& name,
    MeshPtr mesh,
    const Transform& transform) :
    MoveableObject(allocator, name, MoveableObject::ENTITIY, transform ),
    m_MeshPointer( mesh )
  {
  }

  Entity::~Entity( void )
  {
    Release();
  }

  void Entity::Release( void )
  {
    m_MeshPointer = nullptr;
  }

  void Entity::SetMesh( MeshPtr newMesh )
  {
    m_MeshPointer = newMesh;
  }

  MeshPtr Entity::GetMesh( void ) const
  {
    return m_MeshPointer;
  }
}
