#pragma once
#ifndef NiFrameEntity_h__
#define NiFrameEntity_h__

#include "NiFrameEnginePCH.h"
#include "NiFrameReferenceCounted.h"
#include "NiFrameMesh.h"

namespace NiFrame
{

	class NIFRAME_DLL_EXPORT Entity
	{
	public:

		Entity( 
			const String& name, 
			MeshPtr mesh, 
			const Vector3& translation = Vector3(0), 
			const Matrix4x4& rotation = Matrix4x4::IDENTITY, 
			const Vector3& scale = Vector3(1) 
		);

		~Entity( void );

		void Translate( const Vector3& translation );
		void Rotate( const Matrix4x4& rotation );
		void Scale( const Vector3& scale );

		void SetTranslation( const Vector3& translation );
		void SetRotation( const Matrix4x4& rotation );
		void SetScale( const Vector3& scale );

		MeshPtr GetMesh( void ) const;
		void SetMesh( MeshPtr newMesh );

		void Release( void );

	protected:

		void UpdateModelMatrix( void );

		Matrix4x4 m_ModelMatrix, m_Rotation;
		Vector3 m_Translation, m_Scale;

		MeshPtr m_MeshPointer;

	private:
	};

	typedef ReferenceCounted< Entity > EntityPtr;

}

#endif // NiFrameEntity_h__
