#include <Rendering/OpenGL/Resource/Buffer/OpenGLConstantBuffer.h>

Miracle::OpenGLConstantBuffer::OpenGLConstantBuffer(ConstantBuffer* a_ConstantBuffer)
	: OpenGLBuffer(a_ConstantBuffer,GL_UNIFORM_BUFFER)
{
	glBindBuffer(m_Type, m_Handle);
	auto buffer = GetBuffer();
	glBufferData(m_Type, buffer->GetNumBytes(), buffer->GetData(), m_Usage);
	glBindBuffer(m_Type, 0);
}

Miracle::OpenGLConstantBuffer::~OpenGLConstantBuffer()
{
}

void Miracle::OpenGLConstantBuffer::AttachToUnit(GLint a_Unit)
{
	glBindBufferBase(GL_UNIFORM_BUFFER, a_Unit, m_Handle);
}

std::shared_ptr<Miracle::RenderResource> Miracle::OpenGLConstantBuffer::Create(void* a_Stupid, GraphicsObject* a_GraphicsResource)
{
	if (a_GraphicsResource->GetType() == GraphicsObject::CONSTANT_BUFFER)
	{
		return std::make_shared<OpenGLConstantBuffer>(static_cast<ConstantBuffer*>(a_GraphicsResource));
	}
	MENGINE_ASSERT_MSG(false,"Invalid object type.");
	return nullptr;
}
