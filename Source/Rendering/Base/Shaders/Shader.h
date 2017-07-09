#pragma once
#include <Independent/Platform/PreCompileHeader.h>
#include <Rendering/Base/GraphicsObject.h>
#include <Rendering/OpenGL/Shaders/GLSLReflection.h>
#include <Rendering/DirectX/Shaders/HLSL/HLSLShader.h>
#include <Rendering/Base/Resource/Buffer/ConstantBuffer.h>
#include <Rendering/Base/Resource/Texture/TextureSingle.h>
#include <Rendering/Base/Resource/Texture/TextureArray.h>
#include <Rendering/Base/Resource/State/SamplerState.h>
NAMESPACE_MENGINE_BEGIN



class Shader : public GraphicsObject
{
public:
	Shader(const GLSLReflection& a_Reflector,GLint a_Type);
	Shader(const HLSLShader& a_Program);
	~Shader();

	template<typename T>
	int Set(const std::string& name, const std::shared_ptr<T>& a_mobject);


protected:

	struct ShaderData
	{
		std::shared_ptr<GraphicsObject> GraphicsResourceObject;
		_U32 Type;
		std::string Name;
		_U32 BindPoint;
		_U32 NumBytes;
		_U32 Extra;
		bool IsGpuWritable;

		ShaderData(_U32 a_Type, const std::string& a_Name, _U32 a_BindPoint, _U32 a_NumBytes, _U32 a_Extra, bool a_IsGpuWritable)
			: Type(a_Type)
			, Name(a_Name)
			, BindPoint(a_BindPoint)
			, NumBytes(a_NumBytes)
			, Extra(a_Extra)
			, IsGpuWritable(a_IsGpuWritable)
		{

		}


	};

	bool IsValid(const ShaderData& goal, ConstantBuffer* resource) const;
	bool IsValid(const ShaderData& goal, TextureSingle* resource) const;
	bool IsValid(const ShaderData& goal, TextureArray* resource) const;
	bool IsValid(const ShaderData& goal, SamplerState* resource) const;


	std::vector<ShaderData> m_Data[NUM_SHADER_DATA_INDEX];
	std::vector<unsigned char> m_CompiledCode;

public:
	inline const std::vector<unsigned char>&  GetCompiledCode() const;
	inline const std::vector<ShaderData>& GetData(_I32 a_Index) const;
};


template<typename T>
int Miracle::Shader::Set(const std::string& name, const std::shared_ptr<T>& a_mobject)
{
	_U32 handle = 0;
	for each (const auto& data in m_Data[T::ShaderDataIndex])
	{
		if (name == data.Name)
		{
			if (IsValid(data, a_mobject.get()))
			{
				const_cast<ShaderData&>(data).GraphicsResourceObject = a_mobject;
				return handle;
			}
			return -1;
		}
		++handle;
	}
	return -1;
}

inline const std::vector<Shader::ShaderData>& Shader::GetData(_I32 a_Index) const
{
	return m_Data[a_Index];
}

inline const std::vector<unsigned char>& Miracle::Shader::GetCompiledCode() const
{
	return m_CompiledCode;
}

NAMESPACE_MENGINE_END