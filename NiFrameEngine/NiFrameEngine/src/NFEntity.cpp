#include "NFEnginePCH.hpp"
#include "NFEntity.hpp"

namespace nfe
{
	Entity::Entity(
		const String& name,
		MeshPtr mesh,
		const Vector3& translation /*= Vector3(0)*/,
		const Matrix4x4& rotation /*= Matrix4x4::IDENTITY*/,
		const Vector3& scale /*= Vector3(1) */ ) :
		MoveableObject( name, MoveableObject::ENTITIY, translation, rotation, scale ),
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
