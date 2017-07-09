#include <Rendering/OpenGL/Resource/Buffer/OpenGLVertexBuffer.h>


Miracle::OpenGLVertexBuffer::OpenGLVertexBuffer(VertexBuffer* a_Buffer)
	: OpenGLBuffer(a_Buffer, GL_ARRAY_BUFFER)
{
	glBindBuffer(m_Type, m_Handle);
	auto buffer = GetBuffer();
	glBufferData(m_Type, buffer->GetNumBytes(), buffer->GetData(), m_Usage);
	glBindBuffer(m_Type, 0);
}

Miracle::OpenGLVertexBuffer::~OpenGLVertexBuffer()
{
}

std::shared_ptr<Miracle::RenderResource> Miracle::OpenGLVertexBuffer::Create(void* a_Stupid, GraphicsObject* a_GraphicsResource)
{
	if (a_GraphicsResource->GetType() == GraphicsObject::VERTEX_BUFFER)
	{
		return std::make_shared<OpenGLVertexBuffer>(static_cast<VertexBuffer*>(a_GraphicsResource));
	}
	MENGINE_ASSERT_MSG(false, "Invalid object type.");
	return nullptr;
}
