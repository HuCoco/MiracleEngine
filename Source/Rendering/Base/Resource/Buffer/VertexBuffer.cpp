#include <Rendering/Base/Resource/Buffer/VertexBuffer.h>



Miracle::VertexBuffer::VertexBuffer(const VertexFormat& a_VertexFormat, _U32 a_NumVertices)
	: Buffer(a_NumVertices, a_VertexFormat.GetByteSize(), GraphicsObject::VERTEX_BUFFER)
	, m_VertexFormat(a_VertexFormat)
{

}

Miracle::VertexBuffer::~VertexBuffer()
{

}
