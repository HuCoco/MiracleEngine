#include <Rendering/OpenGL/Resource/OpenGLResource.h>


Miracle::OpenGLResource::OpenGLResource(GraphicsObject* a_GraphicsResource)
	: OpenGLResourceChild(a_GraphicsResource)
{

}

Miracle::OpenGLResource::~OpenGLResource()
{

}

void* Miracle::OpenGLResource::Map(GLenum target)
{
	glBindBuffer(target, m_Handle);
	GLvoid* mapped = glMapBuffer(target, GL_WRITE_ONLY);
	glBindBuffer(target, 0);
	return mapped;
}

void Miracle::OpenGLResource::Unmap(GLenum target)
{
	glBindBuffer(target, m_Handle);
	glUnmapBuffer(target);
	glBindBuffer(target, 0);
}

bool Miracle::OpenGLResource::PreparedForCopy(GLenum access) const
{
	if (m_Handle == 0)
	{
		MENGINE_ASSERT_MSG(false,"Resource does not exist.");
		return false;
	}

	GraphicsResource::AccessFlag AccessType = GetGraphicsResource()->GetAccessFlag();
	if (AccessType == GraphicsResource::AccessFlag::WRITE_ONLY)
	{
		if (access == GL_WRITE_ONLY)
		{
			return true;
		}
	}
	else if (AccessType == GraphicsResource::AccessFlag::READ_ONLY)
	{
		if (access == GL_READ_ONLY)
		{
			return true;
		}
	}
	else if (AccessType == GraphicsResource::AccessFlag::READ_WIRTE)
	{
		if (access == GL_WRITE_ONLY)
		{
			return true;
		}
		if (access == GL_READ_ONLY)
		{
			return true;
		}
		if (access == GL_READ_WRITE)
		{
			return true;
		}
	}
	MENGINE_ASSERT_MSG(false, "Resource has incorrect copy type.");
	return false;
}

