#include "NiFrameEnginePCH.h"
#include "NiFrameEntity.h"

namespace NiFrame
{
	Entity::Entity(
		const String& name, 
		MeshPtr mesh, const Vector3& translation /*= Vector3(0)*/, const Matrix4x4& rotation /*= Matrix4x4::IDENTITY*/, const Vector3& scale /*= Vector3(1) */ ) :
		m_MeshPointer( mesh ),
		m_Translation( translation ),
		m_Rotation( rotation ),
		m_Scale( scale )
	{
		UpdateModelMatrix();
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
		return MeshPtr( m_MeshPointer );
	}

	void Entity::SetScale( const Vector3& scale )
	{
		m_Scale = scale;
		UpdateModelMatrix();
	}

	void Entity::SetRotation( const Matrix4x4& rotation )
	{
		m_Rotation = rotation;
		UpdateModelMatrix();
	}
	
	void Entity::SetTranslation( const Vector3& translation )
	{
		m_Translation = translation;
		UpdateModelMatrix();
	}

	void Entity::Scale( const Vector3& scale )
	{
		m_Scale = Vector3( scale.GetX() * m_Scale.GetX(),
							scale.GetY() * m_Scale.GetY(),
							scale.GetZ() * m_Scale.GetZ() );
		UpdateModelMatrix();
	}

	void Entity::Rotate( const Matrix4x4& rotation )
	{
		m_Rotation *= rotation;
		UpdateModelMatrix();
	}

	void Entity::Translate( const Vector3& translation )
	{
		m_Translation = translation;
		UpdateModelMatrix();
	}

	void Entity::UpdateModelMatrix( void )
	{
		//TODO: create static method for Scale Rotate Translate matrix
	}


}

