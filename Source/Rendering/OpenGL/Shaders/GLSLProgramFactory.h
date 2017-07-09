#pragma once
#include <Independent/Platform/PreCompileHeader.h>
#include <Rendering/Base/Shaders/ProgramFactory.h>

NAMESPACE_MENGINE_BEGIN

class GLSLProgramFactory : public ProgramFactory
{
public:

	static std::string DefaultVersion;  
	static std::string DefaultVSEntry;  
	static std::string DefaultPSEntry;  
	static std::string DefaultGSEntry;  

	GLSLProgramFactory();
	virtual ~GLSLProgramFactory();

	virtual _U32 GetShaderLanguage() const override;

private:
	std::shared_ptr<Miracle::VisualProgram> CreateFromNamedSources(
		const std::string& a_vsName, const std::string& a_vsSource,
		const std::string& a_psName, const std::string& a_psSource,
		const std::string& a_gsName, const std::string& a_gsSource);

	GLuint GLSLProgramFactory::Compile(GLenum a_shaderType, const std::string& a_source);
	bool Link(GLuint a_programHandle);
};

NAMESPACE_MENGINE_END