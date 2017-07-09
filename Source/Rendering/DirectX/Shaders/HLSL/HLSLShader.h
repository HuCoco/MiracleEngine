#pragma once
#include <Independent/Platform/PreCompileHeader.h>
#include <ThirdParty/GraphicsKit/DirectXPreCompileHeader.h>
#include <Rendering/DirectX/Shaders/HLSL/HLSLByteAddressBuffer.h>
#include <Rendering/DirectX/Shaders/HLSL/HLSLConstantBuffer.h>
#include <Rendering/DirectX/Shaders/HLSL/HLSLResourceBindInfo.h>
#include <Rendering/DirectX/Shaders/HLSL/HLSLSamplerState.h>
#include <Rendering/DirectX/Shaders/HLSL/HLSLTexture.h>
#include <Rendering/DirectX/Shaders/HLSL/HLSLTextureArray.h>

NAMESPACE_MENGINE_BEGIN

class HLSLShader
{
public:

	struct Description
	{
		struct InstructionCount
		{
			_U32 NumInstructions;
			_U32 NumTemporaryRegisters;
			_U32 NumTemporaryArrays;
			_U32 NumDefines;
			_U32 NumDeclarations;
			_U32 NumTextureNormal;
			_U32 NumTextureLoad;
			_U32 NumTextureComparison;
			_U32 NumTextureBias;
			_U32 NumTextureGradient;
			_U32 NumFloatArithmetic;
			_U32 NumSIntArithmetic;
			_U32 NumUIntArithmetic;
			_U32 NumStaticFlowControl;
			_U32 NumDynamicFlowControl;
			_U32 NumMacro;
			_U32 NumArray;
		};

		struct GSParameters
		{
			_U32 NumCutInstructions;
			_U32 NumEmitInstructions;
			D3D_PRIMITIVE InputPrimitive;
			D3D_PRIMITIVE_TOPOLOGY OutputTopology;
			_U32 MaxOutputVertices;
		};

		struct TSParameters
		{
			_U32 NumPatchConstants;
			_U32 NumGSInstances;
			_U32 NumControlPoints;
			D3D_PRIMITIVE InputPrimitive;
			D3D_TESSELLATOR_OUTPUT_PRIMITIVE OutputPrimitive;
			D3D_TESSELLATOR_PARTITIONING Partitioning;
			D3D_TESSELLATOR_DOMAIN Domain;
		};

		struct CSParameters
		{
			_U32 NumBarrierInstructions;
			_U32 NumInterlockedInstructions;
			_U32 NumTextureStoreInstructions;
		};

		std::string Creator;
		D3D11_SHADER_VERSION_TYPE ShaderType;
		_U32 MajorVersion;
		_U32 MinorVersion;
		_U32 Flags;
		_U32 NumConstantBuffers;
		_U32 NumBoundResources;
		_U32 NumInputParameters;
		_U32 NumOutputParameters;
		InstructionCount Instructions;
		GSParameters gs;
		TSParameters ts;
		CSParameters cs;
	};

	HLSLShader();
	~HLSLShader();

	bool IsValid() const;
	void SetDescription(const D3D11_SHADER_DESC& a_Desc);
	void SetName(const std::string& name);
	void SetEntry(const std::string& entry);
	void SetTarget(const std::string& target);
	void Insert(const HLSLConstantBuffer& cbuffer);
	void Insert(const HLSLByteAddressBuffer& rbuffer);
	void Insert(const HLSLTexture& texture);
	void Insert(const HLSLTextureArray& textureArray);
	void Insert(const HLSLSamplerState& samplerState);
	void Insert(const HLSLResourceBindInfo& rbinfo);
	void SetCompiledCode(size_t numBytes, const void* buffer);

	const Description& GetDescription() const;
	const std::string& GetName() const;
	const std::string& GetEntry() const;
	const std::string& GetTarget() const;
	int GetShaderTypeIndex() const;
	const std::vector<HLSLConstantBuffer>& GetCBuffers() const;
	const std::vector<HLSLByteAddressBuffer>& GetRBuffers() const;
	const std::vector<HLSLTexture>& GetTextures() const;
	const std::vector<HLSLTextureArray>& GetTextureArrays() const;
	const std::vector<HLSLSamplerState>& GetSamplerStates() const;
	const std::vector<HLSLResourceBindInfo>& GetResourceBindInfos() const;
	const std::vector<unsigned char>& GetCompiledCode() const;

private:
	Description m_Desc;
	std::string m_Name;
	std::string m_Entry;
	std::string m_Target;
	std::vector<HLSLConstantBuffer> m_ConstantBuffers;
	std::vector<HLSLByteAddressBuffer> m_ByteAddressBuffers;
	std::vector<HLSLTexture> m_Textures;
	std::vector<HLSLTextureArray> m_TextureArrays;
	std::vector<HLSLSamplerState> m_SamplerStates;
	std::vector<HLSLResourceBindInfo> m_ResourceBindInfo;
	std::vector<unsigned char> m_CompiledCode;

};

NAMESPACE_MENGINE_END