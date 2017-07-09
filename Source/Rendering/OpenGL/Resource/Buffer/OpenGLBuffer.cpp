#include "OpenGLBuffer.h"


Miracle::OpenGLBuffer::OpenGLBuffer(Buffer* a_Buffer, GLenum a_Type)
	: OpenGLResource(a_Buffer)
	, m_Type(a_Type)
{
	glGenBuffers(1, &m_Handle);

	GraphicsResource::Usage usage = a_Buffer->GetUsage();
	if (usage == GraphicsResource::Usage::IMMUTABLE)
	{
		m_Usage = GL_STATIC_DRAW;
	}
	else if (usage == GraphicsResource::Usage::DYNAMIC)
	{
		m_Usage = GL_DYNAMIC_DRAW;
	}
	else
	{
		if (m_Type == GL_ARRAY_BUFFER)
		{
			m_Usage = GL_STATIC_DRAW;
		}
		else if (m_Type == GL_SHADER_STORAGE_BUFFER)
		{
			m_Usage = GL_DYNAMIC_DRAW;
		}
		else
		{
			MENGINE_ASSERT_MSG(false, "Usage ?  output ?");
			m_Usage = GL_STATIC_DRAW;
		}
	}
}

Miracle::OpenGLBuffer::~OpenGLBuffer()
{
	glDeleteBuffers(1, &m_Handle);
}

bool Miracle::OpenGLBuffer::Update()
{
	Buffer* buffer = GetBuffer();
	if (buffer->GetUsage() != GraphicsResource::Usage::DYNAMIC)
	{
		MENGINE_ASSERT_MSG(false, "Buffer is not Dynamic.");
		return false;
	}
	_U32 numActiveBytes = buffer->GetNumActiveBytes();
	if (numActiveBytes > 0)
	{
		GLintptr offsetInBytes = buffer->GetOffset() * buffer->GetElementSize();
		void* source = (char*)buffer->GetData() + offsetInBytes;
		glBindBuffer(m_Type, m_Handle);
		glBufferSubData(m_Type, offsetInBytes, numActiveBytes, source);
		glBindBuffer(m_Type, 0);
	}
	else
	{
		MENGINE_ASSERT_MSG(false, "Buffer has zero active bytes.");
	}
	return true;
}

bool Miracle::OpenGLBuffer::CopyMem2GraphMem()
{
	if (!PreparedForCopy(GL_WRITE_ONLY))
	{
		return false;
	}
	Buffer* buffer = GetBuffer();
	GLuint numActiveBytes = buffer->GetNumActiveBytes();
	if (numActiveBytes > 0)
	{
		GLintptr offsetInBytes = buffer->GetOffset() * buffer->GetElementSize();
		void* source = (char*)buffer->GetData() + offsetInBytes;
		glBindBuffer(m_Type, m_Handle);
		glBufferSubData(m_Type, offsetInBytes, numActiveBytes, source);
		glBindBuffer(m_Type, 0);
	}
	else
	{
		MENGINE_ASSERT_MSG(false,"Buffer has zero active bytes.");
	}
	return true;
}


bool Miracle::OpenGLBuffer::CopyGraphMem2Mem()
{
	if (!PreparedForCopy(GL_READ_ONLY))
	{
		return false;
	}

	Buffer* buffer = GetBuffer();
	GLuint numActiveBytes = buffer->GetNumActiveBytes();
	if (numActiveBytes > 0)
	{
		// Copy from GPU memory to CPU memory.
		GLintptr offsetInBytes = buffer->GetOffset() * buffer->GetElementSize();
		void* target = (char*)buffer->GetData() + offsetInBytes;
		glBindBuffer(m_Type, m_Handle);
		glGetBufferSubData(m_Type, offsetInBytes, numActiveBytes, target);
		glBindBuffer(m_Type, 0);
	}
	else
	{
		MENGINE_ASSERT_MSG(false,"Buffer has zero active bytes.");
	}
	return true;
}

