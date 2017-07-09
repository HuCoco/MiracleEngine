#include "HLSLShaderFactory.h"


Miracle::HLSLShader Miracle::HLSLShaderFactory::CreateFromFile(const std::string& a_Filename,
	const std::string& a_Entry, const std::string& a_Target, _U32 a_CompileFlags)
{
	std::ifstream input(a_Filename);
	if (!input)
	{
		MENGINE_ASSERT_MSG(false,"Cannot open file. ");
		return HLSLShader();
	}

	std::string source = "";
	while (!input.eof())
	{
		std::string line;
		getline(input, line);
		source += line + "\n";
	}
	input.close();

	return CompileAndReflect(a_Filename, source, a_Entry, a_Target, a_CompileFlags);
}



Miracle::HLSLShader Miracle::HLSLShaderFactory::CompileAndReflect(const std::string& a_Name,
	const std::string& a_Source, const std::string& a_Entry, const std::string& a_Target, _U32 a_CompileFlags)
{
	std::string type = a_Target.substr(0, 3);
	if (type == "vs_" || type == "gs_" || type == "ps_" || type == "cs_")
	{
		ID3DBlob* compiledCode = CompileShader(a_Name, a_Source, a_Entry, a_Target, a_CompileFlags);
		if (!compiledCode)
		{
			return HLSLShader();
		}
		HLSLShader shader;
		if (!ReflectShader(a_Name, a_Entry, a_Target, compiledCode, shader))
		{
			// Errors are recorded to a logfile by ReflectShader.
			shader = HLSLShader();
		}
		compiledCode->Release();
		return shader;
	}
	else
	{
		MENGINE_ASSERT_MSG(false, "Invalid target. ");
		return HLSLShader();
	}
}

ID3DBlob* Miracle::HLSLShaderFactory::CompileShader(const std::string& a_Filename,
	const std::string& a_Source, const std::string& a_Entry, const std::string& a_Target, _U32 a_CompileFlags)
{
	ID3DInclude* include = D3D_COMPILE_STANDARD_FILE_INCLUDE;
	ID3DBlob* compiledCode = nullptr;
	ID3DBlob* errors = nullptr;

	HRESULT hr = D3DCompile(a_Source.c_str(), a_Source.length(), a_Filename.c_str(),
		nullptr, include, a_Entry.c_str(), a_Target.c_str(),
		a_CompileFlags, 0, &compiledCode, &errors);

	if (SUCCEEDED(hr))
	{
		if (errors)
		{
			char const* message = static_cast<char const*>(errors->GetBufferPointer());
			MENGINE_ASSERT_MSG(false, "D3DCompile warning.");
		}
	}
	else
	{
		if (errors)
		{
			char const* message = static_cast<char const*>(errors->GetBufferPointer());
			MENGINE_ASSERT_MSG(false, "D3DCompile error.");
		}
		else
		{
			MENGINE_ASSERT_MSG(false, "D3DCompile error.");
		}
	}
	if (errors)
	{
		errors->Release();
	}
	return compiledCode;
}

bool Miracle::HLSLShaderFactory::ReflectShader(const std::string& a_Name,
	const std::string& a_Entry, const std::string& a_Target, ID3DBlob* a_CompiledCode, HLSLShader& a_Shader)
{
	void const* buffer = a_CompiledCode->GetBufferPointer();
	size_t numBytes = a_CompiledCode->GetBufferSize();
	ID3D11ShaderReflection* reflector = nullptr;
	HRESULT hr = D3DReflect(buffer, numBytes, IID_ID3D11ShaderReflection, (void**)&reflector);
	if (FAILED(hr))
	{
		MENGINE_ASSERT_MSG(false,"D3DReflect error.");
		return false;
	}

	bool success =
		GetDescription(reflector, a_Shader) &&
		GetCBuffers(reflector, a_Shader) &&
		GetBoundResources(reflector, a_Shader);

	if (success)
	{
		a_Shader.SetName(std::string(a_Name));
		a_Shader.SetEntry(std::string(a_Entry));
		a_Shader.SetTarget(std::string(a_Target));
		a_Shader.SetCompiledCode(numBytes, buffer);
	
		//TODO: COMPUTE SHADER
	}

	reflector->Release();
	return success;
}

bool Miracle::HLSLShaderFactory::GetDescription(ID3D11ShaderReflection* a_Reflector, HLSLShader& a_Shader)
{
	D3D11_SHADER_DESC desc;
	HRESULT hr = a_Reflector->GetDesc(&desc);
	if (FAILED(hr))
	{
		MENGINE_ASSERT_MSG(false,"reflector->GetDesc error.");
		return false;
	}
	a_Shader.SetDescription(desc);
	return true;
}

bool Miracle::HLSLShaderFactory::GetCBuffers(ID3D11ShaderReflection* a_Reflector, HLSLShader& a_Shader)
{
	UINT const numCBuffers = a_Shader.GetDescription().NumConstantBuffers;
	for (UINT i = 0; i < numCBuffers; ++i)
	{
		ID3D11ShaderReflectionConstantBuffer* cbuffer = a_Reflector->GetConstantBufferByIndex(i);

		D3D11_SHADER_BUFFER_DESC cbDesc;
		HRESULT hr = cbuffer->GetDesc(&cbDesc);
		if (FAILED(hr))
		{
			MENGINE_ASSERT_MSG(false, "reflector->GetConstantBufferByIndex error.");
			return false;
		}

		D3D11_SHADER_INPUT_BIND_DESC resDesc;
		hr = a_Reflector->GetResourceBindingDescByName(cbDesc.Name, &resDesc);
		if (FAILED(hr))
		{
			MENGINE_ASSERT_MSG(false, "reflector->GetResourceBindingDescByName error");
			return false;
		}

		if (cbDesc.Type == D3D_CT_CBUFFER)
		{
			std::vector<HLSLBuffer::Member> members;
			if (!GetVariables(cbuffer, cbDesc.Variables, members))
			{
				return false;
			}

			if (resDesc.BindCount == 1)
			{
				a_Shader.Insert(HLSLConstantBuffer(resDesc, cbDesc.Size, members));
			}
			else
			{
				for (UINT j = 0; j < resDesc.BindCount; ++j)
				{
					a_Shader.Insert(HLSLConstantBuffer(resDesc, j, cbDesc.Size, members));
				}
			}
		}
		else if (cbDesc.Type == D3D_CT_RESOURCE_BIND_INFO)
		{
			std::vector<HLSLBuffer::Member> members;
			if (!GetVariables(cbuffer, cbDesc.Variables, members))
			{
				return false;
			}

			if (resDesc.BindCount == 1)
			{
				a_Shader.Insert(HLSLResourceBindInfo(resDesc, cbDesc.Size, members));
			}
			else
			{
				for (UINT j = 0; j < resDesc.BindCount; ++j)
				{
					a_Shader.Insert(HLSLResourceBindInfo(resDesc, j, cbDesc.Size, members));
				}
			}
		}
		else  // cbDesc.Type == D3D_CT_INTERFACE_POINTERS
		{
			MENGINE_ASSERT_MSG(false,"it's not yet supported in GTEngine.");
			return false;
		}
	}
	return true;
}

bool Miracle::HLSLShaderFactory::GetBoundResources(ID3D11ShaderReflection* a_Reflector, HLSLShader& a_Shader)
{

	UINT const numResources = a_Shader.GetDescription().NumBoundResources;
	for (UINT i = 0; i < numResources; ++i)
	{
		D3D11_SHADER_INPUT_BIND_DESC resDesc;
		HRESULT hr = a_Reflector->GetResourceBindingDesc(i, &resDesc);
		if (FAILED(hr))
		{
			MENGINE_ASSERT_MSG(false, "reflector->GetResourceBindingDesc error.");
			return false;
		}

		if (resDesc.Type == D3D_SIT_CBUFFER     // cbuffer
			|| resDesc.Type == D3D_SIT_TBUFFER)    // tbuffer
		{
			// These were processed in the previous loop.
		}
		else if (
			resDesc.Type == D3D_SIT_TEXTURE        // Texture*
			|| resDesc.Type == D3D_SIT_UAV_RWTYPED)   // RWTexture*
		{
			if (IsTextureArray(resDesc.Dimension))
			{
				if (resDesc.BindCount == 1)
				{
					a_Shader.Insert(HLSLTextureArray(resDesc));
				}
				else
				{
					for (UINT j = 0; j < resDesc.BindCount; ++j)
					{
						a_Shader.Insert(HLSLTextureArray(resDesc, j));
					}
				}
			}
			else
			{
				if (resDesc.BindCount == 1)
				{
					a_Shader.Insert(HLSLTexture(resDesc));
				}
				else
				{
					for (UINT j = 0; j < resDesc.BindCount; ++j)
					{
						a_Shader.Insert(HLSLTexture(resDesc, j));
					}
				}
			}
		}
		else if (resDesc.Type == D3D_SIT_SAMPLER)   // SamplerState
		{
			if (resDesc.BindCount == 1)
			{
				a_Shader.Insert(HLSLSamplerState(resDesc));
			}
			else
			{
				for (UINT j = 0; j < resDesc.BindCount; ++j)
				{
					a_Shader.Insert(HLSLSamplerState(resDesc, j));
				}
			}
		}
		else if (
			resDesc.Type == D3D_SIT_BYTEADDRESS         // ByteAddressBuffer
			|| resDesc.Type == D3D_SIT_UAV_RWBYTEADDRESS)  // RWByteAddressBuffer
		{
			if (resDesc.BindCount == 1)
			{
				a_Shader.Insert(HLSLByteAddressBuffer(resDesc));
			}
			else
			{
				for (UINT j = 0; j < resDesc.BindCount; ++j)
				{
					a_Shader.Insert(HLSLByteAddressBuffer(resDesc, j));
				}
			}
		}
		else
		{
			// D3D_SIT_STRUCTURED:  StructuredBuffer
			// D3D_SIT_UAV_RWSTRUCTURED:  RWStructuredBuffer
			// D3D_SIT_UAV_APPEND_STRUCTURED:  AppendStructuredBuffer
			// D3D_SIT_UAV_CONSUME_STRUCTURED:  ConsumeStructuredBuffer
			// D3D_SIT_UAV_RWSTRUCTURED_WITH_COUNTER:  RWStructuredBuffer

			MENGINE_ASSERT_MSG(false, "it's not yet supported in GTEngine.");
			return false;
		}
	}

	return true;
}

bool Miracle::HLSLShaderFactory::GetVariables(ID3D11ShaderReflectionConstantBuffer* a_Cbuffer, _U32 numVariables, std::vector<HLSLBuffer::Member>& a_Members)
{
	for (UINT i = 0; i < numVariables; ++i)
	{
		ID3D11ShaderReflectionVariable* var = a_Cbuffer->GetVariableByIndex(i);
		ID3D11ShaderReflectionType* varType = var->GetType();

		D3D11_SHADER_VARIABLE_DESC varDesc;
		HRESULT hr = var->GetDesc(&varDesc);
		if (FAILED(hr))
		{
			MENGINE_ASSERT_MSG(false, "var->GetDesc error.");
			return false;
		}

		D3D11_SHADER_TYPE_DESC varTypeDesc;
		hr = varType->GetDesc(&varTypeDesc);
		if (FAILED(hr))
		{
			MENGINE_ASSERT_MSG(false, "varType->GetDesc error." );
			return false;
		}

		// Get the top-level information about the shader variable.
		HLSLShaderVariable svar;
		svar.SetDescription(varDesc);

		// Get the type of the variable.  If this is a struct type, the
		// call recurses to build the type tree implied by the struct.
		HLSLShaderType stype;
		stype.SetName(svar.GetName());
		stype.SetDescription(varTypeDesc);
		if (!GetTypes(varType, varTypeDesc.Members, stype))
		{
			return false;
		}

		a_Members.push_back(std::make_pair(svar, stype));
	}
	return true;
}

bool Miracle::HLSLShaderFactory::GetTypes(ID3D11ShaderReflectionType* a_Rtype, _U32 a_NumMembers, HLSLShaderType& a_Stype)
{
	for (UINT i = 0; i < a_NumMembers; ++i)
	{
		ID3D11ShaderReflectionType* memType = a_Rtype->GetMemberTypeByIndex(i);
		char const* memTypeName = a_Rtype->GetMemberTypeName(i);
		std::string memName(memTypeName ? memTypeName : "");
		D3D11_SHADER_TYPE_DESC memTypeDesc;
		HRESULT hr = memType->GetDesc(&memTypeDesc);
		if (FAILED(hr))
		{
			MENGINE_ASSERT_MSG(false,"memType->GetDesc error");
			return false;
		}
		HLSLShaderType& child = a_Stype.GetChild(i);
		child.SetName(memName);
		child.SetDescription(memTypeDesc);
		GetTypes(memType, memTypeDesc.Members, child);
	}
	return true;
}

bool Miracle::HLSLShaderFactory::IsTextureArray(D3D_SRV_DIMENSION a_Dimension)
{
	return a_Dimension == D3D_SRV_DIMENSION_TEXTURE1DARRAY
		|| a_Dimension == D3D_SRV_DIMENSION_TEXTURE2DARRAY
		|| a_Dimension == D3D_SRV_DIMENSION_TEXTURE2DMSARRAY
		|| a_Dimension == D3D_SRV_DIMENSION_TEXTURECUBE
		|| a_Dimension == D3D_SRV_DIMENSION_TEXTURECUBEARRAY;
}

Miracle::HLSLShader Miracle::HLSLShaderFactory::CreateFromString(const std::string& a_Name, const std::string& a_Source, const std::string& a_Entry, const std::string& a_Target, _U32 a_CompileFlags)
{
	return CompileAndReflect(a_Name, a_Source, a_Entry, a_Target, a_CompileFlags);
}

