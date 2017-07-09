#pragma once
#include <Independent/Platform/PreCompileHeader.h>
#include <ThirdParty/GraphicsKit/OpenGLPreCompileHeader.h>
#include <Rendering/Base/Resource/RenderResource.h>

NAMESPACE_MENGINE_BEGIN

class OpenGLResourceChild : public RenderResource
{
public:
	OpenGLResourceChild(GraphicsObject* a_GraphicsObject);
	~OpenGLResourceChild();

	inline GLuint GetHandle() const;
protected:
	GLuint m_Handle;
};


inline GLuint OpenGLResourceChild::GetHandle() const
{
	return m_Handle;
}

NAMESPACE_MENGINE_END