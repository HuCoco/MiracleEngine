#pragma once
#include <Independent/Platform/PreCompileHeader.h>
#include <Rendering/Base/Resource/Buffer/VertexBuffer.h>
#include <Rendering/OpenGL/Resource/Buffer/OpenGLBuffer.h>

NAMESPACE_MENGINE_BEGIN

class OpenGLVertexBuffer : public OpenGLBuffer
{
public:
	OpenGLVertexBuffer(VertexBuffer* a_Buffer);
	~OpenGLVertexBuffer();

	static std::shared_ptr<RenderResource> Create(void* a_Stupid, GraphicsObject* a_GraphicsResource);

	inline VertexBuffer* GetVertexBuffer() const;
};

inline VertexBuffer* OpenGLVertexBuffer::GetVertexBuffer() const
{
	return static_cast<VertexBuffer*>(m_pGraphicsObject);
}

NAMESPACE_MENGINE_END