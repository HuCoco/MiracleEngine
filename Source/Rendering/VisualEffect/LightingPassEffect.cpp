#include "LightingPassEffect.h"



Miracle::LightingPassEffect::LightingPassEffect(ProgramFactory* a_Factory,
	const std::shared_ptr<Texture2D>& a_PositionTexture,
	const std::shared_ptr<Texture2D>& a_NormalTexture,
	const std::shared_ptr<Texture2D>& a_AlbedoSpecTexture,
	SamplerState::Filter a_TextureFilter,
	SamplerState::Mode a_TextureMode0,
	SamplerState::Mode a_TextureMode1)
{
	const std::string vs_path = "./Resource/ShaderFiles/GLSL/LightingPassVertexShader.glsl";
	const std::string fs_path = "./Resource/ShaderFiles/GLSL/LightingPassFragmentShader.glsl";
	const std::string path = "./Resource/ShaderFiles/HLSL/LightPassEffect.hlsl";
	if (a_Factory->GetShaderLanguage() == ProgramFactory::GLSL)
	{
		m_Program = a_Factory->CreateFromFiles(vs_path, fs_path);
		if (m_Program)
		{
			m_TextureSampler = std::make_shared<SamplerState>();
			m_TextureSampler->filter = a_TextureFilter;
			m_TextureSampler->mode[0] = a_TextureMode0;
			m_TextureSampler->mode[1] = a_TextureMode1;

			m_Program->GetPixelShader()->Set<TextureSingle>("gPosition", a_PositionTexture);
			m_Program->GetPixelShader()->Set<SamplerState>("gPosition", m_TextureSampler);


			m_Program->GetPixelShader()->Set<TextureSingle>("gNormal", a_NormalTexture);
			m_Program->GetPixelShader()->Set<SamplerState>("gNormal", m_TextureSampler);


			m_Program->GetPixelShader()->Set<TextureSingle>("gAlbedoSpec", a_AlbedoSpecTexture);
			m_Program->GetPixelShader()->Set<SamplerState>("gAlbedoSpec", m_TextureSampler);


			m_DirectionalLightConstantBuffer = std::make_shared<ConstantBuffer>(sizeof(DirectionalLight) * MAX_NUM_OF_DIRECTIONAL_LIGHTS, true);
			m_Program->GetPixelShader()->Set<ConstantBuffer>("DirectionalLight", m_DirectionalLightConstantBuffer);
			m_NumDirectionalLightConstantBuffer = std::make_shared<ConstantBuffer>(sizeof(_U32), true);
			m_NumDirectionalLightConstantBuffer->SetData(&m_NumDirectionalLight);
			m_Program->GetPixelShader()->Set<ConstantBuffer>("NumActiveDirectionalLights", m_NumDirectionalLightConstantBuffer);

			m_PointLightConstantBuffer = std::make_shared<ConstantBuffer>(sizeof(PointLight) * MAX_NUM_OF_POINT_LIGHTS, true);
			m_Program->GetPixelShader()->Set<ConstantBuffer>("PointLight", m_PointLightConstantBuffer);
			m_NumPointLightConstantBuffer = std::make_shared<ConstantBuffer>(sizeof(_U32), true);
			m_NumPointLightConstantBuffer->SetData(&m_NumPointLight);
			m_Program->GetPixelShader()->Set<ConstantBuffer>("NumActivePointLights", m_NumPointLightConstantBuffer);

			m_SpotLightConstantBuffer = std::make_shared<ConstantBuffer>(sizeof(SpotLight) * MAX_NUM_OF_SPOT_LIGHTS, true);
			m_Program->GetPixelShader()->Set<ConstantBuffer>("SpotLight", m_SpotLightConstantBuffer);
			m_NumSpotLightConstantBuffer = std::make_shared<ConstantBuffer>(sizeof(_U32), true);
			m_NumSpotLightConstantBuffer->SetData(&m_NumSpotLight);
			m_Program->GetPixelShader()->Set<ConstantBuffer>("NumActiveSpotLights", m_NumSpotLightConstantBuffer);


			m_ViewPosConstant = std::make_shared<ConstantBuffer>(sizeof(Vector3f), true);
			m_ViewPosConstant->SetData(&m_ViewPosition);
			m_Program->GetPixelShader()->Set<ConstantBuffer>("Camera", m_ViewPosConstant);
		}
	}
	else
	{
		m_Program = a_Factory->CreateFromFiles(path, path);
		if (m_Program)
		{
			m_TextureSampler = std::make_shared<SamplerState>();
			m_TextureSampler->filter = a_TextureFilter;
			m_TextureSampler->mode[0] = a_TextureMode0;
			m_TextureSampler->mode[1] = a_TextureMode1;

			m_Program->GetPixelShader()->Set<TextureSingle>("gPosition", a_PositionTexture);

			m_Program->GetPixelShader()->Set<TextureSingle>("gNormal", a_NormalTexture);

			m_Program->GetPixelShader()->Set<TextureSingle>("gAlbedoSpec", a_AlbedoSpecTexture);
			m_Program->GetPixelShader()->Set<SamplerState>("samLinear", m_TextureSampler);


			m_DirectionalLightConstantBuffer = std::make_shared<ConstantBuffer>(sizeof(DirectionalLight) * MAX_NUM_OF_DIRECTIONAL_LIGHTS, true);
			m_Program->GetPixelShader()->Set<ConstantBuffer>("DirectionalLight", m_DirectionalLightConstantBuffer);
			m_NumDirectionalLightConstantBuffer = std::make_shared<ConstantBuffer>(sizeof(_U32), true);
			m_NumDirectionalLightConstantBuffer->SetData(&m_NumDirectionalLight);
			m_Program->GetPixelShader()->Set<ConstantBuffer>("NumActiveDirectionalLights", m_NumDirectionalLightConstantBuffer);

			m_PointLightConstantBuffer = std::make_shared<ConstantBuffer>(sizeof(PointLight) * MAX_NUM_OF_POINT_LIGHTS, true);
			m_Program->GetPixelShader()->Set<ConstantBuffer>("PointLight", m_PointLightConstantBuffer);
			m_NumPointLightConstantBuffer = std::make_shared<ConstantBuffer>(sizeof(_U32), true);
			m_NumPointLightConstantBuffer->SetData(&m_NumPointLight);
			m_Program->GetPixelShader()->Set<ConstantBuffer>("NumActivePointLights", m_NumPointLightConstantBuffer);

			m_SpotLightConstantBuffer = std::make_shared<ConstantBuffer>(sizeof(SpotLight) * MAX_NUM_OF_SPOT_LIGHTS, true);
			m_Program->GetPixelShader()->Set<ConstantBuffer>("SpotLight", m_SpotLightConstantBuffer);
			m_NumSpotLightConstantBuffer = std::make_shared<ConstantBuffer>(sizeof(_U32), true);
			m_NumSpotLightConstantBuffer->SetData(&m_NumSpotLight);
			m_Program->GetPixelShader()->Set<ConstantBuffer>("NumActiveSpotLights", m_NumSpotLightConstantBuffer);


			m_ViewPosConstant = std::make_shared<ConstantBuffer>(sizeof(Vector3f), true);
			m_ViewPosConstant->SetData(&m_ViewPosition);
			m_Program->GetPixelShader()->Set<ConstantBuffer>("Camera", m_ViewPosConstant);

		}
	}
}

Miracle::LightingPassEffect::~LightingPassEffect()
{
}

void Miracle::LightingPassEffect::UpdateAffineMatrixs(AffineMatrixs* a_AffineMatrixs)
{

}

void Miracle::LightingPassEffect::UpdateTextures(std::shared_ptr<Texture2D> a_DiffuseTexture, std::shared_ptr<Texture2D> a_SpecularTexture)
{

}
