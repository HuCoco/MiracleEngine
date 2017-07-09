#include "GeometryPassEffect.h"


Miracle::GeometryPassEffect::GeometryPassEffect(ProgramFactory* a_Factory,
	SamplerState::Filter a_TextureFilter,
	SamplerState::Mode a_TextureMode0,
	SamplerState::Mode a_TextureMode1)
	: m_IsNeedTranspose(false)
{
	m_NeedUpdateAffineMatrixs = true;
	m_NeedUpdateTextures = true; 

	const std::string vs_path = "./Resource/ShaderFiles/GLSL/GeometryPassVertexShader.glsl";
	const std::string fs_path = "./Resource/ShaderFiles/GLSL/GeometryPassFragmentShader.glsl";
	const std::string path = "./Resource/ShaderFiles/HLSL/GeometryPassEffect.hlsl";
	if (a_Factory->GetShaderLanguage() == ProgramFactory::GLSL)
	{
		m_Program = a_Factory->CreateFromFiles(vs_path, fs_path);
		if (m_Program)
		{
			MVPMatrixConstant = std::make_shared<ConstantBuffer>(sizeof(AffineMatrixs), true);
			m_Program->GetVertexShader()->Set<ConstantBuffer>("AffineMatrixs", MVPMatrixConstant);

			m_TextureSampler = std::make_shared<SamplerState>();
			m_TextureSampler->filter = a_TextureFilter;
			m_TextureSampler->mode[0] = a_TextureMode0;
			m_TextureSampler->mode[1] = a_TextureMode1;

			m_Program->GetPixelShader()->Set<SamplerState>("TexDiffuse", m_TextureSampler);
			m_Program->GetPixelShader()->Set<SamplerState>("TexSpecular", m_TextureSampler);

			m_IsNeedTranspose = false;
		}
	}
	else
	{
		m_Program = a_Factory->CreateFromFiles(path, path);
		if (m_Program)
		{
			MVPMatrixConstant = std::make_shared<ConstantBuffer>(sizeof(AffineMatrixs), true);
			m_Program->GetVertexShader()->Set<ConstantBuffer>("AffineMatrixs", MVPMatrixConstant);
			m_Program->GetPixelShader()->Set<ConstantBuffer>("AffineMatrixs", MVPMatrixConstant);

			m_TextureSampler = std::make_shared<SamplerState>();
			m_TextureSampler->filter = a_TextureFilter;
			m_TextureSampler->mode[0] = a_TextureMode0;
			m_TextureSampler->mode[1] = a_TextureMode1;

			m_Program->GetPixelShader()->Set<SamplerState>("samLinear", m_TextureSampler);
			m_Program->GetPixelShader()->Set<SamplerState>("samLinear", m_TextureSampler);

			m_IsNeedTranspose = true;
		}
	}

}

Miracle::GeometryPassEffect::~GeometryPassEffect()
{

}



void Miracle::GeometryPassEffect::UpdateTextures(std::shared_ptr<Texture2D> a_DiffuseTexture, std::shared_ptr<Texture2D> a_SpecularTexture)
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

void Miracle::GeometryPassEffect::UpdateAffineMatrixs(AffineMatrixs* a_AffineMatrixs)
{
	mvp = *a_AffineMatrixs;
	if (m_IsNeedTranspose == true)
	{
		mvp.Transpose();
	}
	MVPMatrixConstant->SetData(&mvp);
	m_Program->GetVertexShader()->Set<ConstantBuffer>("AffineMatrixs", MVPMatrixConstant);
}
