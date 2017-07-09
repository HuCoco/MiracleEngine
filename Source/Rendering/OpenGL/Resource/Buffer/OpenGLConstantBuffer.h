#pragma once
#include <Independent/Platform/PreCompileHeader.h>
#include <Rendering/Base/Resource/Buffer/ConstantBuffer.h>
#include <Rendering/OpenGL/Resource/Buffer/OpenGLBuffer.h>

NAMESPACE_MENGINE_BEGIN

class OpenGLConstantBuffer : public OpenGLBuffer
{
public:
	OpenGLConstantBuffer(ConstantBuffer* a_ConstantBuffer);
	~OpenGLConstantBuffer();

	static std::shared_ptr<RenderResource> Create(void* a_Stupid, GraphicsObject* a_GraphicsResource);

	void AttachToUnit(GLint a_Unit);

	inline ConstantBuffer* GetConstantBuffer() const;
};

inline ConstantBuffer* OpenGLConstantBuffer::GetConstantBuffer() const
{
	return static_cast<ConstantBuffer*>(m_pGraphicsObject);
}

NAMESPACE_MENGINE_END