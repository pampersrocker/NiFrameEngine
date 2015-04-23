#include "NFRendererPCH.hpp"
#include "NFD3DMesh.hpp"

namespace nfe
{

	D3DMesh::D3DMesh( 
		VertexBuffer::type* vertexBuffer, 
		IndexBuffer::type* indexBuffer, 
		IDirect3DVertexBuffer9* GPUvertexBuffer, 
		IDirect3DIndexBuffer9* GPUIndexBuffer ) :
		Mesh(vertexBuffer, indexBuffer),
		m_GPU_indexBuffer( GPUIndexBuffer ),
		m_GPU_vertexBuffer( GPUvertexBuffer )
	{
		D3DVertex vertex;
		void * pData = nullptr;
		m_GPU_vertexBuffer->Lock(0, (UINT) vertexBuffer->size()* sizeof(D3DVertex),&pData,0);
		for(uint32 i = 0 ; i < vertexBuffer->size(); ++i)
		{
			vertex.x = ((*vertexBuffer)[i]).GetX();
			vertex.y = ((*vertexBuffer)[i]).GetY();
			vertex.z = ((*vertexBuffer)[i]).GetZ();
			vertex.color = D3DCOLOR_XRGB(255,255,255);
			memcpy( (void *)(&(reinterpret_cast<D3DVertex*>(pData)[i])), &vertex, sizeof(D3DVertex));
		}
		m_GPU_vertexBuffer->Unlock();

		m_GPU_indexBuffer->Lock(0, (UINT) indexBuffer->size()*sizeof(uint32), &pData, 0);
		memcpy(pData,indexBuffer->data(),sizeof(uint32)*indexBuffer->size());
		m_GPU_indexBuffer->Unlock();
	}

	D3DMesh::~D3DMesh( void )
	{
		Release();
	}

	void D3DMesh::Release( void )
	{
	}

	void D3DMesh::UpdateGPUBuffers( void )
	{
	}

	IDirect3DVertexBuffer9* D3DMesh::GetVertexBuffer( void ) const
	{
		return m_GPU_vertexBuffer;
	}

	IDirect3DIndexBuffer9* D3DMesh::GetIndexBuffer( void ) const
	{
		return m_GPU_indexBuffer;
	}


}

