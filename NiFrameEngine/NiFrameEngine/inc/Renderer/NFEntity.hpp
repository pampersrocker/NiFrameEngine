#pragma once
#ifndef NiFrameEntity_h__
#define NiFrameEntity_h__

#include "NFEnginePCH.hpp"
#include "NFReferenceCounted.hpp"
#include "NFMesh.hpp"
#include "NFMovableObject.hpp"

namespace nfe
{

  class NIFRAME_DLL_EXPORT Entity : public MoveableObject
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

    MeshPtr GetMesh( void ) const;
    void SetMesh( MeshPtr newMesh );

    void Release( void );

  protected:

    void UpdateModelMatrix( void );

    Matrix4x4 m_ModelMatrix;
    Vector3 m_Scale;

    MeshPtr m_MeshPointer;

  private:
  };

  //typedef ReferenceCounted< Entity > EntityPtr;
  TYPEDEF_EXPORT_REFCOUNT_PTR( Entity )

}

#endif // NiFrameEntity_h__
