#pragma once
#include <Independent/Platform/PreCompileHeader.h>
#include <Rendering/Base/Resource/Buffer/Buffer.h>
#include <Rendering/OpenGL/Resource/OpenGLResource.h>

NAMESPACE_MENGINE_BEGIN

class OpenGLBuffer : public OpenGLResource
{
public:
	OpenGLBuffer(Buffer* a_Buffer,GLenum a_Type);
	~OpenGLBuffer();

	virtual bool Update();
	virtual bool CopyGraphMem2Mem();
	virtual bool CopyMem2GraphMem();

	inline Buffer* GetBuffer() const;
	inline GLenum GetType() const;
	inline GLenum GetUsage() const;

protected:
	GLenum m_Type;
	GLenum m_Usage;
};

inline Buffer* OpenGLBuffer::GetBuffer() const
{
	return static_cast<Buffer*>(m_pGraphicsObject);
}

inline GLenum OpenGLBuffer::GetType() const
{
	return m_Type;
}

inline GLenum OpenGLBuffer::GetUsage() const
{
	return m_Usage;
}

NAMESPACE_MENGINE_END