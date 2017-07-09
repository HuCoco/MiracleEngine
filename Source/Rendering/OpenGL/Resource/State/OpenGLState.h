#pragma once
#include <Independent/Platform/PreCompileHeader.h>
#include <Rendering/OpenGL/Resource/OpenGLResourceChild.h>
#include <Rendering/Base/Resource/State/State.h>

NAMESPACE_MENGINE_BEGIN

class OpenGLState : public OpenGLResourceChild
{
protected:
	OpenGLState(State* a_State);

public:
	virtual ~OpenGLState();
};

NAMESPACE_MENGINE_END