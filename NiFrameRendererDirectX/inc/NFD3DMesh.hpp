#pragma once
#ifndef NiFrameD3DMesh_h__
#define NiFrameD3DMesh_h__

#include "NFRendererPCH.hpp"
#include "NFMesh.hpp"

namespace nfe
{
  struct D3DVertex
  {
    float x,y,z;
    DWORD color;
  };

  #define D3DVertex_FVF (D3DFVF_XYZ|D3DFVF_DIFFUSE)


  class D3DMesh : public Mesh
  {
  public:

    D3DMesh( 
      VertexBuffer* vertexBuffer, 
      IndexBuffer* indexBuffer, 
      IDirect3DVertexBuffer9* GPUvertexBuffer, 
      IDirect3DIndexBuffer9* GPUIndexBuffer );

    virtual ~D3DMesh( void );

    virtual void UpdateGPUBuffers( void ) override;

    virtual void Release( void ) override;

    IDirect3DVertexBuffer9* GetVertexBuffer( void ) const;

    IDirect3DIndexBuffer9* GetIndexBuffer( void ) const;

    IDirect3DVertexBuffer9* m_GPU_vertexBuffer;
    IDirect3DIndexBuffer9* m_GPU_indexBuffer;


  protected:


  private:
  };
}

#endif // NiFrameD3DMesh_h__
