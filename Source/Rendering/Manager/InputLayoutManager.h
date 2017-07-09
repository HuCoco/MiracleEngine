#pragma once
#include <Independent/Platform/PreCompileHeader.h>
#include <Rendering/Base/Resource/Buffer/VertexBuffer.h>
#include <Rendering/Base/Shaders/Shader.h>

NAMESPACE_MENGINE_BEGIN

class InputLayoutManager
{
public:
	InputLayoutManager() {}
	~InputLayoutManager() {}

	virtual bool Unbind(VertexBuffer*, void*) = 0;
	virtual void UnbindAll() = 0;
};

NAMESPACE_MENGINE_END