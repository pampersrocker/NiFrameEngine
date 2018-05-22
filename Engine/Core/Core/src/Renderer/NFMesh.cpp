#include "NFEnginePCH.hpp"
#include "Renderer/NFMesh.hpp"

namespace nfe
{

  Mesh::Mesh( VertexBuffer* vertexBuffer, IndexBuffer* indexBuffer ) :
    m_Vertices( vertexBuffer ),
    m_Indices( indexBuffer )
  {
  }

  Mesh::~Mesh( void )
  {
    Release();
  }

  void Mesh::Release( void )
  {
    SAFE_DELETE( m_Vertices )
    SAFE_DELETE( m_Indices )
  }

  nfe::NFSize Mesh::GetIndexCount( void ) const
  {
    return m_Indices->Size();
  }

  nfe::NFSize Mesh::GetVertexCount( void ) const
  {
    return m_Vertices->Size();
  }

}

