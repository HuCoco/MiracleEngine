#include "HLSLProgramFactory.h"
#include <Rendering/DirectX/Shaders/HLSL/HLSLShader.h>
#include <Rendering/DirectX/Shaders/HLSL/HLSLShaderFactory.h>
#include <Rendering/DirectX/Shaders/HLSL/HLSLVisualProgram.h>

std::string Miracle::HLSLProgramFactory::DefaultVersion = "5_0";
std::string Miracle::HLSLProgramFactory::DefaultVSEntry = "VS_Main";
std::string Miracle::HLSLProgramFactory::DefaultPSEntry = "PS_Main";
std::string Miracle::HLSLProgramFactory::DefaultGSEntry = "GS_Main";
std::string Miracle::HLSLProgramFactory::DefaultCSEntry = "CS_Main";
_U32 Miracle::HLSLProgramFactory::DefaultFlags = ( D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_IEEE_STRICTNESS | D3DCOMPILE_OPTIMIZATION_LEVEL3);

Miracle::HLSLProgramFactory::HLSLProgramFactory()
{
	Version = DefaultVersion;
	VertexShaderEntry = DefaultVSEntry;
	PixelShaderEntry = DefaultPSEntry;
	GeometryShaderEntry = DefaultGSEntry;
	Flags = DefaultFlags;
}


Miracle::HLSLProgramFactory::~HLSLProgramFactory()
{
}


std::shared_ptr<Miracle::VisualProgram> Miracle::HLSLProgramFactory::CreateFromNamedSources(
	const std::string& vsName, const std::string& vsSource,
	const std::string& psName, const std::string& psSource,
	const std::string& gsName, const std::string& gsSource)
{
	if (vsSource == "" || psSource == "")
	{
		MENGINE_ASSERT_MSG(false, "A program must have a vertex shader and a pixel shader.");
		return nullptr;
	}

	std::shared_ptr<VertexShader> vshader;
	std::shared_ptr<PixelShader> pshader;

	HLSLShader hlslVShader = HLSLShaderFactory::CreateFromString(vsName,
		vsSource, VertexShaderEntry, std::string("vs_") + Version, Flags);
	if (hlslVShader.IsValid())
	{
		vshader = std::static_pointer_cast<VertexShader>(std::make_shared<Shader>(hlslVShader));
	}
	else
	{
		return nullptr;
	}

	HLSLShader hlslPShader = HLSLShaderFactory::CreateFromString(psName,
		psSource, PixelShaderEntry, std::string("ps_") + Version, Flags);
	if (hlslPShader.IsValid())
	{
		pshader =
			std::static_pointer_cast<PixelShader>(std::make_shared<Shader>(hlslPShader));
	}
	else
	{
		return nullptr;
	}
	std::shared_ptr<HLSLVisualProgram> program = std::make_shared<HLSLVisualProgram>();
	program->SetVertexShader(vshader);
	program->SetPixelShader(pshader);
	return program;
}

_U32 Miracle::HLSLProgramFactory::GetShaderLanguage() const
{
	return ProgramFactory::HLSL;
}

