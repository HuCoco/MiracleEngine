#include <Rendering/Base/Shaders/PixelShader.h>



Miracle::PixelShader::PixelShader(const GLSLReflection& a_Reflector)
	: Shader(a_Reflector,GLSLReflection::PIXEL)
{

}

Miracle::PixelShader::PixelShader(const HLSLShader& a_Program)
	: Shader(a_Program)
{

}

Miracle::PixelShader::~PixelShader()
{
}
