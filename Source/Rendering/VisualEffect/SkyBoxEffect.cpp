#include <Rendering/VisualEffect/SkyBoxEffect.h>


Miracle::SkyBoxEffect::SkyBoxEffect(ProgramFactory* a_Factory)
{
	std::string GLSLVertexShaderPath = "D:/MiracleEngine/Source/Shaders/GLSL/SkyBoxEffectVertexShader.glsl";
	std::string GLSLFragmentShaderPath = "D:/MiracleEngine/Source/Shaders/GLSL/SkyBoxEffectFragmentShader.glsl";
	std::string HLSLShaderPath = "D:/MiracleEngine/Source/Shaders/HLSL/SkyBoxEffect.hlsl";

	if (a_Factory->GetShaderLanguage() == ProgramFactory::GLSL)
	{
		m_Program = a_Factory->CreateFromFiles(GLSLVertexShaderPath, GLSLFragmentShaderPath);
		if (m_Program)
		{
			m_SamplerCube = std::make_shared<SamplerState>();
			m_SamplerCube->filter = SamplerState::Filter::MIN_L_MAG_L_MIP_L;
			m_SamplerCube->mode[0] = SamplerState::Mode::CLAMP;
			m_SamplerCube->mode[1] = SamplerState::Mode::CLAMP;
			m_SamplerCube->mode[2] = SamplerState::Mode::CLAMP;
			m_Program->GetPixelShader()->Set<SamplerState>("TexSkyBox", m_SamplerCube);

			m_SkyBoxMatrixsBuffer = std::make_shared<ConstantBuffer>(sizeof(SkyBoxMatrixs),true);
			m_SkyBoxMatrixsBuffer->SetData(&m_SkyBoxMatrixs);
			m_Program->GetVertexShader()->Set<ConstantBuffer>("SkyBoxMatrixs",m_SkyBoxMatrixsBuffer);
		}
	}
	else
	{
		m_Program = a_Factory->CreateFromFiles(HLSLShaderPath, HLSLShaderPath);
		if (m_Program)
		{
			m_SamplerCube = std::make_shared<SamplerState>();
			m_SamplerCube->filter = SamplerState::Filter::MIN_L_MAG_L_MIP_L;
			m_SamplerCube->mode[0] = SamplerState::Mode::CLAMP;
			m_SamplerCube->mode[1] = SamplerState::Mode::CLAMP;
			m_SamplerCube->mode[2] = SamplerState::Mode::CLAMP;
			m_Program->GetPixelShader()->Set<SamplerState>("SkyBoxSampler", m_SamplerCube);

			m_SkyBoxMatrixsBuffer = std::make_shared<ConstantBuffer>(sizeof(SkyBoxMatrixs), true);
			m_SkyBoxMatrixsBuffer->SetData(&m_SkyBoxMatrixs);
			m_Program->GetVertexShader()->Set<ConstantBuffer>("SkyBoxMatrixs", m_SkyBoxMatrixsBuffer);
			m_Program->GetPixelShader()->Set<ConstantBuffer>("SkyBoxMatrixs", m_SkyBoxMatrixsBuffer);
		}
	}
}

Miracle::SkyBoxEffect::~SkyBoxEffect()
{
}

void Miracle::SkyBoxEffect::UpdateAffineMatrixs(AffineMatrixs* a_AffineMatrixs)
{

}

void Miracle::SkyBoxEffect::UpdateTextures(std::shared_ptr<Texture2D> a_DiffuseTexture, std::shared_ptr<Texture2D> a_SpecularTexture)
{

}

void Miracle::SkyBoxEffect::Update(SkyBoxMatrixs* a_SkyboxMatrixs)
{
	m_SkyBoxMatrixs = *a_SkyboxMatrixs;
}

void Miracle::SkyBoxEffect::Update(std::shared_ptr<TextureCube> a_TextureCube)
{
	m_TextureCube = a_TextureCube;
	m_Program->GetPixelShader()->Set<TextureArray>("TexSkyBox", m_TextureCube);
}
