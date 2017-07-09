#pragma once
#include <Independent/Platform/PreCompileHeader.h>
#include <ThirdParty/GraphicsKit/OpenGLPreCompileHeader.h>

NAMESPACE_MENGINE_BEGIN

class GLSLReflection
{
public:

	GLSLReflection(GLuint a_Handle);
	~GLSLReflection();

	enum 
	{
		VERTEX,
		GEOMETRY,
		PIXEL,
		COMPUTE,
		NUM_SHADER
	};

	struct Uniform
	{
		std::string FullName;
		std::string Name;
		GLint Type;
		GLint Location;
		GLint ArraySize;
		GLint Offset;
		GLint BlockIndex;
		GLint ArrayStride;
		GLint MatrixStride;
		GLint IsRowMajor;
		GLint AtomicCounterBufferIndex;
		GLint referencedBy[NUM_SHADER];
	};

	struct DataBlock
	{
		std::string name;
		GLint bufferBinding;
		GLint bufferDataSize;
		GLint referencedBy[NUM_SHADER];
		std::vector<GLint> activeVariables;
	};


	inline const std::vector<Uniform>& GetUniforms() const;
	inline const std::vector<DataBlock>& GetUniformBlocks() const;
private:
	void ReflectUniforms();
	void ReflectDataBlocks(GLenum programInterface, std::vector<DataBlock>& blocks);

private:
	GLuint m_Handle;
	std::vector<Uniform> m_Uniforms;
	std::vector<DataBlock> m_UniformBlocks;
};

inline const std::vector<GLSLReflection::Uniform>& GLSLReflection::GetUniforms() const
{
	return m_Uniforms;
}

inline const std::vector<GLSLReflection::DataBlock>& GLSLReflection::GetUniformBlocks() const
{
	return m_UniformBlocks;
}

NAMESPACE_MENGINE_END