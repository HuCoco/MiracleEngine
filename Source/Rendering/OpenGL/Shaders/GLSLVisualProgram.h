#pragma once
#include <Independent/Platform/PreCompileHeader.h>
#include <Rendering/Base/Shaders/VisualProgram.h>

NAMESPACE_MENGINE_BEGIN

class GLSLVisualProgram : public VisualProgram
{
public:
	GLSLVisualProgram(GLuint a_ProgramHandle, GLuint a_VshaderHandle, GLuint a_PshaderHandle, GLuint a_GshaderHandle);
	virtual ~GLSLVisualProgram();

	inline GLuint GetProgramHandle() const;
	inline GLuint GetVShaderHandle() const;
	inline GLuint GetPShaderHandle() const;
	inline GLuint GetGShaderHandle() const;
	inline GLSLReflection const& GetReflector() const;

private:
	GLuint m_ProgramHandle;
	GLuint m_VShaderHandle;
	GLuint m_PShaderHandle;
	GLuint m_GShaderHandle;
	GLSLReflection m_Reflector;
};

inline GLuint GLSLVisualProgram::GetProgramHandle() const
{
	return m_ProgramHandle;
}

inline GLuint GLSLVisualProgram::GetVShaderHandle() const
{
	return m_VShaderHandle;
}

inline GLuint GLSLVisualProgram::GetPShaderHandle() const
{
	return m_PShaderHandle;
}

inline GLuint GLSLVisualProgram::GetGShaderHandle() const
{
	return m_GShaderHandle;
}

inline GLSLReflection const& GLSLVisualProgram::GetReflector() const
{
	return m_Reflector;
}

NAMESPACE_MENGINE_END
