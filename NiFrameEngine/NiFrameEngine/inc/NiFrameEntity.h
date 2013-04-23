#pragma once
#ifndef NiFrameEntity_h__
#define NiFrameEntity_h__

#include "NiFrameEnginePCH.h"

namespace NiFrame
{
	class Mesh;

	class NIFRAME_DLL_EXPORT Entity
	{
	public:

		Entity( 
		Mesh* mesh, 
		const Vector3& translation = Vector3(0), 
		const Matrix4x4& rotation = Matrix4x4::IDENTITY, 
		const Vector3& scale = Vector3(1) );

		~Entity( void );

		void Translate( const Vector3& translation );
		void Rotate( const Matrix4x4& rotation );
		void Scale( const Vector3& scale );

		void SetTranslation( const Vector3& translation );
		void SetRotation( const Matrix4x4& rotation );
		void SetScale( const Vector3& scale );

		Mesh* GetMesh( void ) const;
		void SetMesh( Mesh* newMesh );

		void Release( void );

	protected:

		void UpdateModelMatrix( void );

		Matrix4x4 m_ModelMatrix, m_Rotation;
		Vector3 m_Translation, m_Scale;

		Mesh* m_MeshPointer;

	private:
	};

}

#endif // NiFrameEntity_h__
