#pragma once
#include <Independent/Platform/PreCompileHeader.h>
#include <Rendering/Base/Shaders/Shader.h>

NAMESPACE_MENGINE_BEGIN

class PixelShader : public Shader
{
public:
	PixelShader(const GLSLReflection& a_Reflector);
	PixelShader(const HLSLShader& a_Program);
	~PixelShader();
};

NAMESPACE_MENGINE_END