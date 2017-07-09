#include <Rendering/Base/Shaders/VertexShader.h>


Miracle::VertexShader::VertexShader(const GLSLReflection& a_Reflector)
	: Shader(a_Reflector, GLSLReflection::VERTEX)
{

}

Miracle::VertexShader::VertexShader(const HLSLShader& a_Program)
	: Shader(a_Program)
{

}

Miracle::VertexShader::~VertexShader()
{
}
