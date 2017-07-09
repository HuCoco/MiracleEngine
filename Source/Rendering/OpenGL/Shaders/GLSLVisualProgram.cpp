#include <Rendering/OpenGL/Shaders/GLSLVisualProgram.h>

Miracle::GLSLVisualProgram::GLSLVisualProgram(GLuint a_ProgramHandle, GLuint a_VshaderHandle, GLuint a_PshaderHandle, GLuint a_GshaderHandle)
	: m_ProgramHandle(a_ProgramHandle)
	, m_VShaderHandle(a_VshaderHandle)
	, m_PShaderHandle(a_PshaderHandle)
	, m_GShaderHandle(a_GshaderHandle)
	, m_Reflector(a_ProgramHandle)
{

}

Miracle::GLSLVisualProgram::~GLSLVisualProgram()
{
	if (glIsProgram(m_ProgramHandle))
	{
		if (glIsShader(m_VShaderHandle))
		{
			glDetachShader(m_ProgramHandle, m_VShaderHandle);
			glDeleteShader(m_VShaderHandle);
		}

		if (glIsShader(m_PShaderHandle))
		{
			glDetachShader(m_ProgramHandle, m_PShaderHandle);
			glDeleteShader(m_PShaderHandle);
		}

		if (glIsShader(m_GShaderHandle))
		{
			glDetachShader(m_ProgramHandle, m_GShaderHandle);
			glDeleteShader(m_GShaderHandle);
		}

		glDeleteProgram(m_ProgramHandle);
	}
}

