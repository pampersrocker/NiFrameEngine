#pragma once
#ifndef NiFrameMesh_h__
#define NiFrameMesh_h__

#include "NiFrameEnginePCH.h"

typedef NiFrame::vector<NiFrame::Vector3> VertexBuffer;
typedef NiFrame::vector<NiFrame::uint32> IndexBuffer;

namespace NiFrame
{
	class NIFRAME_DLL_EXPORT Mesh
	{
	public:
		
		Mesh( VertexBuffer::type* vertexBuffer, IndexBuffer::type* indexBuffer );
		~Mesh( void );

		NFSize GetVertexCount( void ) const;
		NFSize GetIndexCount( void ) const;

		virtual void UpdateGPUBuffers( void ) = 0;

		virtual void Release( void );

	protected:

		VertexBuffer::type* m_Vertices;
		IndexBuffer::type* m_Indices; 
	
	private:
		

	};

}

#endif // NiFrameMesh_h__
