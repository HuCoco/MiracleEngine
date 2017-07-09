#pragma once
#include <Independent/Platform/PreCompileHeader.h>
#include <Rendering/Base/Shaders/VisualProgram.h>

NAMESPACE_MENGINE_BEGIN

class ProgramFactory
{
public:
	ProgramFactory();
	virtual ~ProgramFactory();

	std::string Version;
	std::string VertexShaderEntry;
	std::string PixelShaderEntry;
	std::string GeometryShaderEntry;
	_U32 Flags;

	enum
	{
		GLSL,
		HLSL
	};

	virtual _U32 GetShaderLanguage() const = 0;

	std::shared_ptr<VisualProgram> CreateFromFiles(std::string const& a_vsFile, std::string const& a_psFile, std::string const& a_gsFile = "");

	std::shared_ptr<VisualProgram> CreateFromSources( std::string const& a_vsSource, std::string const& a_psSource, std::string const& a_gsSource = "");

private:
	std::string ReadFromFile(const std::string& a_filename);

	virtual std::shared_ptr<VisualProgram> CreateFromNamedSources(
		const std::string& a_vsName, const std::string& a_vsSource,
		const std::string& a_psName, const std::string& a_psSource,
		const std::string& a_gsName, const std::string& a_gsSource) = 0;
};

NAMESPACE_MENGINE_END