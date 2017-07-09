#pragma once
#include <Independent/Platform/PreCompileHeader.h>
#include <ThirdParty/GraphicsKit/OpenGLPreCompileHeader.h>
#include <Rendering/OpenGL/Resource/OpenGLResourceChild.h>

NAMESPACE_MENGINE_BEGIN

class OpenGLResource : public OpenGLResourceChild
{
public:
	OpenGLResource(GraphicsObject* a_GraphicsResource);
	~OpenGLResource();

	virtual bool Update() = 0;
	virtual bool CopyGraphMem2Mem() = 0;
	virtual bool CopyMem2GraphMem() = 0;

	void* Map(GLenum target);
	void Unmap(GLenum target);
protected:
	bool PreparedForCopy(GLenum access) const;


};


NAMESPACE_MENGINE_END