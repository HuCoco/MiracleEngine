#pragma once
#include <Independent/Platform/PreCompileHeader.h>
#include <ThirdParty/GraphicsKit/DirectXPreCompileHeader.h>
#include <Rendering/Base/Shaders/ProgramFactory.h>

NAMESPACE_MENGINE_BEGIN

class HLSLProgramFactory : public ProgramFactory
{
public:
	static std::string DefaultVersion;  // "5_0" (Shader Model 5)
	static std::string DefaultVSEntry;  // "VSMain"
	static std::string DefaultPSEntry;  // "PSMain"
	static std::string DefaultGSEntry;  // "GSMain"
	static std::string DefaultCSEntry;  // "CSMain"
	static unsigned int DefaultFlags;

	HLSLProgramFactory();
	~HLSLProgramFactory();

	virtual _U32 GetShaderLanguage() const override;
private:
	virtual std::shared_ptr<VisualProgram> CreateFromNamedSources(
		const std::string& vsName, const std::string& vsSource,
		const std::string& psName, const std::string& psSource,
		const std::string& gsName, const std::string& gsSource);
};

NAMESPACE_MENGINE_END