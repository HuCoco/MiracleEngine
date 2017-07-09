#include <Rendering/DirectX/Shaders/HLSL/HLSLShader.h>


Miracle::HLSLShader::HLSLShader()
	: m_Name("")
	, m_Entry("")
	, m_Target("")
{

}

Miracle::HLSLShader::~HLSLShader()
{

}

bool Miracle::HLSLShader::IsValid() const
{
	return m_Name != "" && m_Entry != "" && m_Target != ""
		&& m_CompiledCode.size() > 0;
}

void Miracle::HLSLShader::SetDescription(const D3D11_SHADER_DESC& a_Desc)
{
	m_Desc.Creator = std::string(a_Desc.Creator);
	m_Desc.ShaderType = static_cast<D3D11_SHADER_VERSION_TYPE>(D3D11_SHVER_GET_TYPE(a_Desc.Version));
	m_Desc.MajorVersion = D3D11_SHVER_GET_MAJOR(a_Desc.Version);
	m_Desc.MinorVersion = D3D11_SHVER_GET_MINOR(a_Desc.Version);
	m_Desc.Flags = a_Desc.Flags;
	m_Desc.NumConstantBuffers = a_Desc.ConstantBuffers;
	m_Desc.NumBoundResources = a_Desc.BoundResources;
	m_Desc.NumInputParameters = a_Desc.InputParameters;
	m_Desc.NumOutputParameters = a_Desc.OutputParameters;

	m_Desc.Instructions.NumInstructions = a_Desc.InstructionCount;
	m_Desc.Instructions.NumTemporaryRegisters = a_Desc.TempRegisterCount;
	m_Desc.Instructions.NumTemporaryArrays = a_Desc.TempArrayCount;
	m_Desc.Instructions.NumDefines = a_Desc.DefCount;
	m_Desc.Instructions.NumDeclarations = a_Desc.DclCount;
	m_Desc.Instructions.NumTextureNormal = a_Desc.TextureNormalInstructions;
	m_Desc.Instructions.NumTextureLoad = a_Desc.TextureLoadInstructions;
	m_Desc.Instructions.NumTextureComparison = a_Desc.TextureCompInstructions;
	m_Desc.Instructions.NumTextureBias = a_Desc.TextureBiasInstructions;
	m_Desc.Instructions.NumTextureGradient = a_Desc.TextureGradientInstructions;
	m_Desc.Instructions.NumFloatArithmetic = a_Desc.FloatInstructionCount;
	m_Desc.Instructions.NumSIntArithmetic = a_Desc.IntInstructionCount;
	m_Desc.Instructions.NumUIntArithmetic = a_Desc.UintInstructionCount;
	m_Desc.Instructions.NumStaticFlowControl = a_Desc.StaticFlowControlCount;
	m_Desc.Instructions.NumDynamicFlowControl = a_Desc.DynamicFlowControlCount;
	m_Desc.Instructions.NumMacro = a_Desc.MacroInstructionCount;
	m_Desc.Instructions.NumArray = a_Desc.ArrayInstructionCount;

	m_Desc.gs.NumCutInstructions = a_Desc.CutInstructionCount;
	m_Desc.gs.NumEmitInstructions = a_Desc.EmitInstructionCount;
	m_Desc.gs.InputPrimitive = a_Desc.InputPrimitive;
	m_Desc.gs.OutputTopology = a_Desc.GSOutputTopology;
	m_Desc.gs.MaxOutputVertices = a_Desc.GSMaxOutputVertexCount;
	
	m_Desc.ts.NumPatchConstants = a_Desc.PatchConstantParameters;
	m_Desc.ts.NumGSInstances = a_Desc.cGSInstanceCount;
	m_Desc.ts.NumControlPoints = a_Desc.cControlPoints;
	m_Desc.ts.InputPrimitive = a_Desc.InputPrimitive;
	m_Desc.ts.OutputPrimitive = a_Desc.HSOutputPrimitive;
	m_Desc.ts.Partitioning = a_Desc.HSPartitioning;
	m_Desc.ts.Domain = a_Desc.TessellatorDomain;
	
	m_Desc.cs.NumBarrierInstructions = a_Desc.cBarrierInstructions;
	m_Desc.cs.NumInterlockedInstructions = a_Desc.cInterlockedInstructions;
	m_Desc.cs.NumTextureStoreInstructions = a_Desc.cTextureStoreInstructions;
}

void Miracle::HLSLShader::SetName(const std::string& name)
{
	m_Name = name;
}

void Miracle::HLSLShader::SetEntry(const std::string& entry)
{
	m_Entry = entry;
}

void Miracle::HLSLShader::SetTarget(const std::string& target)
{
	m_Target = target;
}

void Miracle::HLSLShader::Insert(const HLSLConstantBuffer& cbuffer)
{
	m_ConstantBuffers.emplace_back(cbuffer);
}

void Miracle::HLSLShader::Insert(const HLSLByteAddressBuffer& rbuffer)
{
	m_ByteAddressBuffers.emplace_back(rbuffer);
}

void Miracle::HLSLShader::Insert(const HLSLTexture& texture)
{
	m_Textures.emplace_back(texture);
}

void Miracle::HLSLShader::Insert(const HLSLTextureArray& textureArray)
{
	m_TextureArrays.emplace_back(textureArray);
}

void Miracle::HLSLShader::Insert(const HLSLSamplerState& samplerState)
{
	m_SamplerStates.emplace_back(samplerState);
}

void Miracle::HLSLShader::Insert(const HLSLResourceBindInfo& rbinfo)
{
	m_ResourceBindInfo.emplace_back(rbinfo);
}

void Miracle::HLSLShader::SetCompiledCode(size_t numBytes, const void* buffer)
{
	m_CompiledCode.resize(numBytes);
	memcpy(&m_CompiledCode[0], buffer, numBytes);
}

const Miracle::HLSLShader::Description& Miracle::HLSLShader::GetDescription() const
{
	return m_Desc;
}

const std::string& Miracle::HLSLShader::GetName() const
{
	return m_Name;
}

const std::string& Miracle::HLSLShader::GetEntry() const
{
	return m_Entry;
}

const std::string& Miracle::HLSLShader::GetTarget() const
{
	return m_Target;
}

int Miracle::HLSLShader::GetShaderTypeIndex() const
{
	switch (m_Target[0])
	{
	case 'v':
		return 0;
	case 'g':
		return 1;
	case 'p':
		return 2;
	case 'c':
		return 3;
	default:
		MENGINE_ASSERT_MSG(false,"Invalid shader type.");
		return 0;
	}
}

const std::vector<Miracle::HLSLConstantBuffer>& Miracle::HLSLShader::GetCBuffers() const
{
	return m_ConstantBuffers;
}

const std::vector<Miracle::HLSLByteAddressBuffer>& Miracle::HLSLShader::GetRBuffers() const
{
	return m_ByteAddressBuffers;
}

const std::vector<Miracle::HLSLTexture>& Miracle::HLSLShader::GetTextures() const
{
	return m_Textures;
}

const std::vector<Miracle::HLSLTextureArray>& Miracle::HLSLShader::GetTextureArrays() const
{
	return m_TextureArrays;
}

const std::vector<Miracle::HLSLSamplerState>& Miracle::HLSLShader::GetSamplerStates() const
{
	return m_SamplerStates;
}

const std::vector<Miracle::HLSLResourceBindInfo>& Miracle::HLSLShader::GetResourceBindInfos() const
{
	return m_ResourceBindInfo;
}

const std::vector<unsigned char>& Miracle::HLSLShader::GetCompiledCode() const
{
	return m_CompiledCode;
}

