#include <Rendering/Base/Shaders/Shader.h>
#include <ThirdParty/GraphicsKit/OpenGLPreCompileHeader.h>
#include <Rendering/OpenGL/Shaders/GLSLReflection.h>
#include <Rendering/Base/Resource/Texture/TextureSingle.h>
#include <Rendering/Base/Resource/State/SamplerState.h>
#include <Rendering/Base/Resource/Buffer/ConstantBuffer.h>

Miracle::Shader::Shader(const GLSLReflection& a_Reflector, GLint a_Type)
	: GraphicsObject(GraphicsObject::SHADER + a_Type + 1)
{
	const auto& uniforms = a_Reflector.GetUniforms();
	for each (auto uniform in uniforms)
	{
		if (uniform.referencedBy[a_Type])
		{
			switch (uniform.Type)
			{
			case GL_SAMPLER_1D:
			case GL_INT_SAMPLER_1D:
			case GL_UNSIGNED_INT_SAMPLER_1D:
			{
				m_Data[TextureSingleShaderDataIndex].push_back(ShaderData(
					GraphicsObject::TEXTURE_SINGLE,
					uniform.Name,
					uniform.Location,
					0,
					1,
					false));
				m_Data[SamplerStateShaderDataIndex].push_back(ShaderData(
					GraphicsObject::SAMPLER_STATE,
					uniform.Name,
					uniform.Location,
					0,
					GraphicsObject::TEXTURE1D,
					false));
				break;
			}
			case GL_SAMPLER_2D:
			case GL_INT_SAMPLER_2D:
			case GL_UNSIGNED_INT_SAMPLER_2D:
			{
				m_Data[TextureSingleShaderDataIndex].push_back(ShaderData(
					GraphicsObject::TEXTURE_SINGLE,
					uniform.Name,
					uniform.Location,
					0,
					2,
					false));
				m_Data[SamplerStateShaderDataIndex].push_back(ShaderData(
					GraphicsObject::SAMPLER_STATE,
					uniform.Name,
					uniform.Location,
					0,
					GraphicsObject::TEXTURE2D,
					false));
				break;
			}
			case GL_SAMPLER_3D:
			case GL_INT_SAMPLER_3D:
			case GL_UNSIGNED_INT_SAMPLER_3D:
			{
				m_Data[TextureSingleShaderDataIndex].push_back(ShaderData(
					GraphicsObject::TEXTURE_SINGLE,
					uniform.Name,
					uniform.Location,
					0,
					3,
					false));
				m_Data[SamplerStateShaderDataIndex].push_back(ShaderData(
					GraphicsObject::SAMPLER_STATE,
					uniform.Name,
					uniform.Location,
					0,
					GraphicsObject::TEXTURE3D,
					false));
				break;
			}
			case GL_SAMPLER_1D_ARRAY:
			case GL_INT_SAMPLER_1D_ARRAY:
			case GL_UNSIGNED_INT_SAMPLER_1D_ARRAY:
			{
				m_Data[TextureArrayShaderDataIndex].push_back(ShaderData(
					GraphicsObject::TEXTURE_ARRAY,
					uniform.Name,
					uniform.Location,
					0,
					1,
					false));
				m_Data[SamplerStateShaderDataIndex].push_back(ShaderData(
					GraphicsObject::SAMPLER_STATE,
					uniform.Name,
					uniform.Location,
					0,
					GraphicsObject::TEXTURE1D_ARRAY,
					false));
				break;
			}
			case GL_SAMPLER_2D_ARRAY:
			case GL_INT_SAMPLER_2D_ARRAY:
			case GL_UNSIGNED_INT_SAMPLER_2D_ARRAY:
			{
				m_Data[TextureArrayShaderDataIndex].push_back(ShaderData(
					GraphicsObject::TEXTURE_ARRAY,
					uniform.Name,
					uniform.Location,
					0,
					2,
					false));
				m_Data[SamplerStateShaderDataIndex].push_back(ShaderData(
					GraphicsObject::SAMPLER_STATE,
					uniform.Name,
					uniform.Location,
					0,
					GraphicsObject::TEXTURE2D_ARRAY,
					false));
				break;
			}
			case GL_SAMPLER_CUBE:
			case GL_INT_SAMPLER_CUBE:
			case GL_UNSIGNED_INT_SAMPLER_CUBE:
			{
				m_Data[TextureArrayShaderDataIndex].push_back(ShaderData(
					GraphicsObject::TEXTURE_ARRAY,
					uniform.Name,
					uniform.Location,
					0,
					2,
					false));
				m_Data[SamplerStateShaderDataIndex].push_back(ShaderData(
					GraphicsObject::SAMPLER_STATE,
					uniform.Name,
					uniform.Location,
					0,
					GraphicsObject::TEXTURE_CUBE,
					false));
				break;
			}
			case GL_SAMPLER_CUBE_MAP_ARRAY:
			case GL_INT_SAMPLER_CUBE_MAP_ARRAY:
			case GL_UNSIGNED_INT_SAMPLER_CUBE_MAP_ARRAY:
			{
				m_Data[TextureArrayShaderDataIndex].push_back(ShaderData(
					GraphicsObject::TEXTURE_ARRAY,
					uniform.Name,
					uniform.Location,
					0,
					3,
					false));
				m_Data[SamplerStateShaderDataIndex].push_back(ShaderData(
					GraphicsObject::SAMPLER_STATE,
					uniform.Name,
					uniform.Location, 
					0,
					GraphicsObject::TEXTURE_CUBE_ARRAY,
					false));
				break;
			}

			}
		}
	}

	const auto& uniformblocks = a_Reflector.GetUniformBlocks();
	for each (auto uniformblock in uniformblocks)
	{
		if (uniformblock.referencedBy[a_Type])
		{
			m_Data[ConstantBuffer::ShaderDataIndex].push_back(ShaderData(
				GraphicsObject::CONSTANT_BUFFER,
				uniformblock.name,
				uniformblock.bufferBinding,
				uniformblock.bufferDataSize,
				0,
				false));
		}
	}

}

Miracle::Shader::Shader(const HLSLShader& a_Program)
	: GraphicsObject(GraphicsObject::SHADER + a_Program.GetShaderTypeIndex() + 1)
	, m_CompiledCode(a_Program.GetCompiledCode())
{
	for each (auto const& cb in a_Program.GetCBuffers())
	{
		m_Data[ConstantBuffer::ShaderDataIndex].push_back(ShaderData(
			GraphicsObject::CONSTANT_BUFFER,
			cb.GetName(),
			cb.GetBindPoint(),
			cb.GetNumBytes(),
			0,
			false));
	}

	for each (auto const& tx in a_Program.GetTextures())
	{
		m_Data[TextureSingle::ShaderDataIndex].push_back(ShaderData(
			GraphicsObject::TEXTURE_SINGLE,
			tx.GetName(),
			tx.GetBindPoint(),
			0,
			tx.GetNumDimensions(),
			tx.IsGpuWritable()));
	}

	for each (auto const& ta in a_Program.GetTextureArrays())
	{
		m_Data[TextureArray::ShaderDataIndex].push_back(ShaderData(
			GraphicsObject::TEXTURE_ARRAY,
			ta.GetName(),
			ta.GetBindPoint(),
			0,
			ta.GetNumDimensions(),
			ta.IsGpuWritable()));
	}

	for (auto const& s : a_Program.GetSamplerStates())
	{
		m_Data[SamplerState::ShaderDataIndex].push_back(ShaderData(
			GraphicsObject::SAMPLER_STATE,
			s.GetName(),
			s.GetBindPoint(),
			0,
			0,
			false));
	}
}

Miracle::Shader::~Shader()
{
}


bool Miracle::Shader::IsValid(const ShaderData& goal, ConstantBuffer* resource) const
{
	if (!resource)
	{
		MENGINE_ASSERT_MSG(false, "Resource is null.");
		return nullptr;
	}

	if (goal.Type != GraphicsObject::CONSTANT_BUFFER)
	{
		MENGINE_ASSERT_MSG(false,"Mismatch of buffer type.");
		return false;
	}

	if (resource->GetNumBytes() >= goal.NumBytes)
	{
		return true;
	}

	MENGINE_ASSERT_MSG(false,"Invalid number of bytes.");
	return false;
}
bool Miracle::Shader::IsValid(const ShaderData& goal, TextureSingle* resource) const
{
	if (!resource)
	{
		MENGINE_ASSERT_MSG(false, "Resource is null.");
		return nullptr;
	}

	if (goal.Type != GraphicsObject::TEXTURE_SINGLE)
	{
		MENGINE_ASSERT_MSG(false, "Mismatch of texture type.");
		return false;
	}

	if (goal.IsGpuWritable && resource->GetUsage() != GraphicsResource::Usage::DEFAULT)
	{
		MENGINE_ASSERT_MSG(false,"Mismatch of GPU write flag.");
		return false;
	}
	
	if (goal.Extra != resource->GetNumDimensions())
	{
		MENGINE_ASSERT_MSG(false,"Mismatch of texture dimensions.");
		return false;
	}

	return true;
}

bool Miracle::Shader::IsValid(const ShaderData& goal, TextureArray* resource) const
{
	if (!resource)
	{
		MENGINE_ASSERT_MSG(false, "Resource is null.");
		return nullptr;
	}

	if (goal.Type != GraphicsObject::TEXTURE_ARRAY)
	{
		MENGINE_ASSERT_MSG(false, "Mismatch of texture type.");
		return false;
	}

	if (goal.IsGpuWritable && resource->GetUsage() != GraphicsResource::Usage::DEFAULT)
	{
		MENGINE_ASSERT_MSG(false, "Mismatch of GPU write flag.");
		return false;
	}

	if (goal.Extra != resource->GetNumDimensions())
	{
		MENGINE_ASSERT_MSG(false, "Mismatch of texture dimensions.");
		return false;
	}

	return true;
}

bool Miracle::Shader::IsValid(const ShaderData& goal, SamplerState* resource) const
{
	if (!resource)
	{
		MENGINE_ASSERT_MSG(false,"Resource is null.");
		return false;
	}

	if (goal.Type != GraphicsObject::SAMPLER_STATE)
	{
		MENGINE_ASSERT_MSG(false,"Mismatch of state.");
		return false;
	}

	return true;
}

