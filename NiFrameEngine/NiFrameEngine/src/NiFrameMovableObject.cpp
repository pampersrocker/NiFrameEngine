#include "NiFrameEnginePCH.h"
#include "NiFrameMovableObject.h"

namespace NiFrame
{
	MoveableObject::MoveableObject(
		const String& name,
		MoveableObjectType type,
		const Vector3& pos /*= Vector3( 0.0f )*/,
		const Matrix4x4& orientation /*= Matrix4x4::IDENTITY */,
		const Vector3& scale /* = Vector3( 1.0f )*/ ) :
		m_Name( name ),
		m_Type( type ),
		m_Position( pos ),
		m_Orientation( orientation ),
		m_Scale( scale ),
		m_Transformation( Matrix4x4::IDENTITY )
	{
		UpdateTransformationMatrix();
	}

	MoveableObject::~MoveableObject()
	{
	}

	void MoveableObject::UpdateTransformationMatrix( void )
	{
		m_Transformation = Matrix4x4::CreateTranslationMatrix( m_Position ) * m_Orientation
			* Matrix4x4::CreateScaleMatrix( m_Scale );
	}

	NiFrame::MoveableObject::MoveableObjectType MoveableObject::GetType( void ) const
	{
		return m_Type;
	}

	void MoveableObject::SetPosition( const Vector3& newPos )
	{
		m_Position = newPos;
		UpdateTransformationMatrix();
	}

	const Vector3& MoveableObject::GetPosition( void ) const
	{
		return m_Position;
	}

	void MoveableObject::SetOrientation( const Matrix4x4& newOrientation )
	{
		m_Orientation = newOrientation;
		UpdateTransformationMatrix();
	}

	const Matrix4x4& MoveableObject::GetOrientation( void ) const
	{
		return m_Orientation;
	}

	const String& MoveableObject::GetName( void ) const
	{
		return m_Name;
	}

	void MoveableObject::SetName( const String& name )
	{
		m_Name = name;
	}

	const Matrix4x4& MoveableObject::GetTransformation( void ) const
	{
		return m_Transformation;
	}

	void MoveableObject::SetScale( const Vector3& val )
	{
		m_Scale = val;
		UpdateTransformationMatrix();
	}

	const Vector3& MoveableObject::GetScale( void ) const
	{
		return m_Scale;
	}
}
