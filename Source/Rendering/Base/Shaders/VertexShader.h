#pragma once
#include <Independent/Platform/PreCompileHeader.h>
#include <Rendering/Base/Shaders/Shader.h>

NAMESPACE_MENGINE_BEGIN

class VertexShader : public Shader
{
public:
	VertexShader(const GLSLReflection& a_Reflector);
	VertexShader(const HLSLShader& a_Program);
	virtual ~VertexShader();
};

NAMESPACE_MENGINE_END