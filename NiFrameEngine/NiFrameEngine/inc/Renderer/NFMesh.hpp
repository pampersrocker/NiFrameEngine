#pragma once
#ifndef NiFrameMesh_h__
#define NiFrameMesh_h__

#include "NFEnginePCH.hpp"
#include "NFReferenceCounted.hpp"

typedef nfe::vector<nfe::Vector3> VertexBuffer;
typedef nfe::vector<nfe::uint32> IndexBuffer;

namespace nfe
{
  class NIFRAME_API Mesh
  {
  public:

    Mesh( VertexBuffer* vertexBuffer, IndexBuffer* indexBuffer );
    virtual ~Mesh( void );

    NFSize GetVertexCount( void ) const;
    NFSize GetIndexCount( void ) const;

    virtual void UpdateGPUBuffers( void ) = 0;

    virtual void Release( void );

  protected:

    VertexBuffer* m_Vertices;
    IndexBuffer* m_Indices;

  private:


  };

  //typedef ReferenceCounted< Mesh > MeshPtr;
  TYPEDEF_EXPORT_REFCOUNT_PTR( Mesh )

}

#endif // NiFrameMesh_h__
