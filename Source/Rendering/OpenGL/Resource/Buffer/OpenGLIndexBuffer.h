#pragma once
#include <Independent/Platform/PreCompileHeader.h>
#include <Rendering/Base/Resource/Buffer/IndexBuffer.h>
#include <Rendering/OpenGL/Resource/Buffer/OpenGLBuffer.h>

NAMESPACE_MENGINE_BEGIN

class OpenGLIndexBuffer : public OpenGLBuffer
{
public:
	OpenGLIndexBuffer(IndexBuffer* a_IndexBuffer);
	~OpenGLIndexBuffer();

	static std::shared_ptr<RenderResource> Create(void* a_Stupid, GraphicsObject* a_GraphicsResource);

	void Enable();
	void Disable();

	inline IndexBuffer* GetIndexBuffer() const;
	inline GLenum GetDataFormat() const;
private:
	GLenum m_Format;
};

inline IndexBuffer* OpenGLIndexBuffer::GetIndexBuffer() const
{
	return static_cast<IndexBuffer*>(m_pGraphicsObject);
}

inline GLenum OpenGLIndexBuffer::GetDataFormat() const
{
	return m_Format;
}

NAMESPACE_MENGINE_END