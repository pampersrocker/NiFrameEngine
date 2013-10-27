#pragma once
#ifndef NiFrameMovableObject_h__
	#define NiFrameMovableObject_h__

	#include "NFEnginePCH.hpp"
	#include "NFReferenceCounted.hpp"

namespace nfe
{
	class NIFRAME_DLL_EXPORT MoveableObject
	{
	public:

		enum MoveableObjectType
		{
			ENTITIY,
			LIGHT,
			SCENENODE
		};


		MoveableObject( 
			const String& name,
			MoveableObjectType type,
			const Vector3& pos = Vector3( 0.0f ),
			const Matrix4x4& orientation = Matrix4x4::IDENTITY,
			const Vector3& scale = Vector3( 1.0f ) );
		~MoveableObject();

		MoveableObjectType GetType( void ) const;

		void SetPosition( const Vector3& newPos );
		const Vector3& GetPosition( void ) const;

		void SetOrientation( const Matrix4x4& newOrientation );
		const Matrix4x4& GetOrientation( void ) const;

		const Vector3& GetScale( void ) const;
		void SetScale( const Vector3& val );

		const String& GetName( void ) const;
		void SetName( const String& name );

		const Matrix4x4& GetTransformation( void ) const;

	protected:

		String m_Name;

		Matrix4x4 m_Transformation;
		Vector3 m_Position, m_Scale;
		Matrix4x4 m_Orientation;
		MoveableObjectType m_Type;

		void UpdateTransformationMatrix( void );

	private:
	};

	NIFRAME_TPL_EXPORT template class NIFRAME_DLL_EXPORT ReferenceCounted< MoveableObject >;

	typedef ReferenceCounted< MoveableObject > MoveableObjectPtr;
}

#endif	// NiFrameMovableObject_h__
