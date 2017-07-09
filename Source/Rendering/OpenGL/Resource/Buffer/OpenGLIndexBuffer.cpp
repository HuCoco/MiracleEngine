#include <Rendering/OpenGL/Resource/Buffer/OpenGLIndexBuffer.h>


Miracle::OpenGLIndexBuffer::OpenGLIndexBuffer(IndexBuffer* a_IndexBuffer)
	: OpenGLBuffer(a_IndexBuffer,GL_ELEMENT_ARRAY_BUFFER)
	, m_Format(a_IndexBuffer->GetElementSize() == 32 ? GL_UNSIGNED_INT : GL_UNSIGNED_SHORT)
{
	glBindBuffer(m_Type, m_Handle);
	auto buffer = GetBuffer();
	glBufferData(m_Type, buffer->GetNumBytes(), buffer->GetData(), m_Usage);
	glBindBuffer(m_Type, 0);
}

Miracle::OpenGLIndexBuffer::~OpenGLIndexBuffer()
{
}

void Miracle::OpenGLIndexBuffer::Enable()
{
	glBindBuffer(m_Type, m_Handle);
}

void Miracle::OpenGLIndexBuffer::Disable()
{
	glBindBuffer(m_Type, 0);
}

std::shared_ptr<Miracle::RenderResource> Miracle::OpenGLIndexBuffer::Create(void* a_Stupid, GraphicsObject* a_GraphicsResource)
{
	if (a_GraphicsResource->GetType() == GraphicsObject::INDEX_BUFFER)
	{
		return std::make_shared<OpenGLIndexBuffer>(static_cast<IndexBuffer*>(a_GraphicsResource));
	}
	MENGINE_ASSERT_MSG(false, "Invalid object type.");
	return nullptr;
}
