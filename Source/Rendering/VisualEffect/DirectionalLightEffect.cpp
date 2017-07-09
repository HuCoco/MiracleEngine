#include "DirectionalLightEffect.h"


const std::string Miracle::DirectionalLightEffect::GLSLVertexShaderPath = "D:\\MiracleEngine\\Source\\Shaders\\GLSL\\DirectionalLightEffectVertexShader.glsl";
const std::string Miracle::DirectionalLightEffect::GLSLFragmentShaderPath = "D:\\MiracleEngine\\Source\\Shaders\\GLSL\\DirectionalLightEffectFragment.glsl";
const std::string Miracle::DirectionalLightEffect::HLSLShaderPath = "D:\\MiracleEngine\\Source\\Shaders\\HLSL\\DirectionalLightEffectShader.hlsl";

Miracle::DirectionalLightEffect::DirectionalLightEffect(ProgramFactory* a_Factory,
	SamplerState::Filter a_Filter, SamplerState::Mode a_Mode0, SamplerState::Mode a_Mode1,
	const std::shared_ptr<Texture2D>& a_TexDiffuse, const std::shared_ptr<Texture2D>& a_TexSpecular /*= nullptr*/)
{
	if (a_Factory->GetShaderLanguage() == ProgramFactory::GLSL)
	{
		m_Program = a_Factory->CreateFromFiles(GLSLVertexShaderPath, GLSLFragmentShaderPath);
		if (m_Program)
		{
			m_AffineMatrixsBuffer = std::make_shared<ConstantBuffer>(sizeof(AffineMatrixs), true);
			m_DirectionalLightBuffer = std::make_shared<ConstantBuffer>(sizeof(DirectionalLightBlock), true);
			m_MaterialBuffer = std::make_shared<ConstantBuffer>(sizeof(MaterialBlock::UseSpecularTex), true);
			m_CameraPositionBuffer = std::make_shared<ConstantBuffer>(sizeof(Vector4f), true);

			m_Sampler = std::make_shared<SamplerState>();
			m_Sampler->filter = a_Filter;
			m_Sampler->mode[0] = a_Mode0;
			m_Sampler->mode[1] = a_Mode1;

			m_Program->GetVertexShader()->Set<ConstantBuffer>("AffineMatrixs", m_AffineMatrixsBuffer);
			m_AffineMatrixsBuffer->SetData(&m_AffineMatrixs);

			m_Program->GetPixelShader()->Set<ConstantBuffer>("DirectionalLightBlock", m_DirectionalLightBuffer);
			m_DirectionalLightBuffer->SetData(&m_DirectionalLightBlock);

			m_Program->GetPixelShader()->Set<ConstantBuffer>("Material", m_MaterialBuffer);
			m_MaterialBuffer->SetData(&m_Shininess);

			m_Program->GetPixelShader()->Set<ConstantBuffer>("Camera", m_CameraPositionBuffer);
			m_CameraPositionBuffer->SetData(&m_CameraPosition);

			m_Program->GetPixelShader()->Set<TextureSingle>("TexDiffuse", a_TexDiffuse);
			m_Program->GetPixelShader()->Set<SamplerState>("TexDiffuse", m_Sampler);
			if (a_TexSpecular == nullptr)
			{
				m_Program->GetPixelShader()->Set<TextureSingle>("TexSpecular", a_TexDiffuse);
			}
			else
			{
				m_Program->GetPixelShader()->Set<TextureSingle>("TexSpecular", a_TexSpecular);
			}
			m_Program->GetPixelShader()->Set<SamplerState>("TexSpecular", m_Sampler);


		}
	}
	else
	{
		m_Program = a_Factory->CreateFromFiles(HLSLShaderPath, HLSLShaderPath);
		if (m_Program)
		{
			m_AffineMatrixsBuffer = std::make_shared<ConstantBuffer>(sizeof(m_AffineMatrixs), true);
			m_DirectionalLightBuffer = std::make_shared<ConstantBuffer>(sizeof(DirectionalLightBlock), true);
			m_MaterialBuffer = std::make_shared<ConstantBuffer>(sizeof(MaterialBlock::UseSpecularTex), true);
			m_CameraPositionBuffer = std::make_shared<ConstantBuffer>(sizeof(Vector4f), true);
			m_Sampler = std::make_shared<SamplerState>();
			m_Sampler->filter = a_Filter;
			m_Sampler->mode[0] = a_Mode0;
			m_Sampler->mode[1] = a_Mode1;

			m_Program->GetVertexShader()->Set<ConstantBuffer>("AffineMatrixs", m_AffineMatrixsBuffer);
			m_AffineMatrixsBuffer->SetData(&m_AffineMatrixs);
			m_Program->GetPixelShader()->Set<ConstantBuffer>("AffineMatrixs", m_AffineMatrixsBuffer);
			m_AffineMatrixsBuffer->SetData(&m_AffineMatrixs);

			m_Program->GetPixelShader()->Set<ConstantBuffer>("DirectionalLightBlock", m_DirectionalLightBuffer);
			m_DirectionalLightBuffer->SetData(&m_DirectionalLightBlock);

			m_Program->GetPixelShader()->Set<ConstantBuffer>("Material", m_MaterialBuffer);
			m_MaterialBuffer->SetData(&m_Shininess);

			m_Program->GetPixelShader()->Set<ConstantBuffer>("Camera", m_CameraPositionBuffer);
			m_CameraPositionBuffer->SetData(&m_CameraPosition);

			m_Program->GetPixelShader()->Set<TextureSingle>("TexDiffuse", a_TexDiffuse);
			m_Program->GetPixelShader()->Set<SamplerState>("samLinear", m_Sampler);
			if (a_TexSpecular == nullptr)
			{
				m_Program->GetPixelShader()->Set<TextureSingle>("TexSpecular", a_TexDiffuse);
			}
			else
			{
				m_Program->GetPixelShader()->Set<TextureSingle>("TexSpecular", a_TexSpecular);
			}
		}
	}
}

Miracle::DirectionalLightEffect::~DirectionalLightEffect()
{
}

void Miracle::DirectionalLightEffect::SetAffineMatrixs(AffineMatrixs* a_AffineMatrixs)
{
	m_AffineMatrixs = *a_AffineMatrixs;
}


void Miracle::DirectionalLightEffect::SetDirectionalLight(DirectionalLightBlock* a_DirectionalLight)
{
	m_DirectionalLightBlock = *a_DirectionalLight;
}

void Miracle::DirectionalLightEffect::SetMaterial(MaterialBlock::UseSpecularTex* a_Shininess)
{
	m_Shininess = *a_Shininess;
}

void Miracle::DirectionalLightEffect::SetCameraPosition(Vector4f* a_CameraPosition)
{
	m_CameraPosition = *a_CameraPosition;
}

void Miracle::DirectionalLightEffect::SetTexture(const std::shared_ptr<Texture2D>& a_TexDiffuse, const std::shared_ptr<Texture2D>& a_TexSpecular /*= nullptr*/)
{
	m_Program->GetPixelShader()->Set<TextureSingle>("TexDiffuse", a_TexDiffuse);
	if (a_TexSpecular == nullptr)
	{
		m_Program->GetPixelShader()->Set<TextureSingle>("TexSpecular", a_TexDiffuse);
	}
	else
	{
		m_Program->GetPixelShader()->Set<TextureSingle>("TexSpecular", a_TexSpecular);
	}
}

void Miracle::DirectionalLightEffect::UpdateTextures(std::shared_ptr<Texture2D> a_DiffuseTexture, std::shared_ptr<Texture2D> a_SpecularTexture)
{
	m_Program->GetPixelShader()->Set<TextureSingle>("TexDiffuse", a_DiffuseTexture);
	if (a_SpecularTexture == nullptr)
	{
		m_Program->GetPixelShader()->Set<TextureSingle>("TexSpecular", a_DiffuseTexture);
	}
	else
	{
		m_Program->GetPixelShader()->Set<TextureSingle>("TexSpecular", a_SpecularTexture);
	}
}

void Miracle::DirectionalLightEffect::UpdateAffineMatrixs(AffineMatrixs* a_AffineMatrixs)
{

}
