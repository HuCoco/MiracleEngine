#pragma once
#include <Independent/Platform/PreCompileHeader.h>
#include <ThirdParty/GraphicsKit/DirectXPreCompileHeader.h>
#include <Rendering/DirectX/Shaders/HLSL/HLSLShader.h>

NAMESPACE_MENGINE_BEGIN

class HLSLShaderFactory
{
public:
	static HLSLShader CreateFromFile(const std::string& a_Filename, const std::string& a_Entry, const std::string& a_Target, _U32 a_CompileFlags);
	static HLSLShader CreateFromString(const std::string& a_Name,const std::string& a_Source, const std::string& a_Entry, const std::string& a_Target, _U32 a_CompileFlags);
	//static HLSLShader CreateFromByteCode(const std::string& a_Name, const std::string& a_Entry, const std::string& a_Target, _U32 a_CompileFlags);

private:
	static HLSLShader CompileAndReflect(const std::string& a_Name, const std::string& a_Source, const std::string& a_Entry, const std::string& a_Target, _U32 a_CompileFlags);
	static ID3DBlob* CompileShader(const std::string& a_Name, const std::string& a_Source, const std::string& a_Entry, const std::string& a_Target, _U32 a_CompileFlags);
	static bool ReflectShader(const std::string& a_Name, const std::string& a_Entry, const std::string& a_Target, ID3DBlob* a_CompiledCode, HLSLShader& a_Shader);

	static bool GetDescription(ID3D11ShaderReflection* a_Reflector, HLSLShader& a_Shader);
	static bool GetCBuffers(ID3D11ShaderReflection* a_Reflector, HLSLShader& a_Shader);
	static bool GetBoundResources(ID3D11ShaderReflection* a_Reflector, HLSLShader& a_Shader);
	static bool GetVariables(ID3D11ShaderReflectionConstantBuffer* a_Cbuffer, _U32 numVariables, std::vector<HLSLBuffer::Member>& a_Members);

	static bool GetTypes(ID3D11ShaderReflectionType* a_Rtype, _U32 a_NumMembers, HLSLShaderType& a_Stype);

	static bool IsTextureArray(D3D_SRV_DIMENSION a_Dimension);
};

NAMESPACE_MENGINE_END