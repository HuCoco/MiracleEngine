#pragma once
#include <Independent/Platform/PreCompileHeader.h>
#include <Rendering/Base/Resource/Buffer/VertexBuffer.h>

NAMESPACE_MENGINE_BEGIN

class OpenGLInputLayout
{
public:
	OpenGLInputLayout(GLuint a_ProgramHandle, GLuint a_VertexBufferHandle,VertexBuffer* a_Buffer);
	~OpenGLInputLayout();

	void Enable();
	void Disable();
private:

	struct Attribute
	{
		VertexSemantic semantic;
		GLint numChannels;
		GLint channelType;
		GLboolean normalize;
		GLint location;
		GLintptr offset;
		GLsizei stride;
	};

	GLuint m_ProgramHandle;
	GLuint m_VertexBufferHandle;
	GLuint m_VertexArrayHandle;

	_U32 m_NumAttributes;
	Attribute* m_Attributes;
};

NAMESPACE_MENGINE_END