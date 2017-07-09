#pragma once
#include <Independent/Platform/PreCompileHeader.h>
#include <Rendering/VisualEffect/VisualEffect.h>
#include <Rendering/OpenGL/Shaders/GLSLProgramFactory.h>
#include <Rendering/Base/Resource/Buffer/ConstantBuffer.h>
#include <Rendering/Base/Resource/Texture/Texture2D.h>
#include <Rendering/Base/Resource/State/SamplerState.h>
#include <GamePlay/Base/Lights.h>

NAMESPACE_MENGINE_BEGIN

class LightingPassEffect : public VisualEffect
{
public:

	LightingPassEffect(ProgramFactory* a_Factory,
		const std::shared_ptr<Texture2D>& a_PositionTexture,
		const std::shared_ptr<Texture2D>& a_NormalTexture,
		const std::shared_ptr<Texture2D>& a_AlbedoSpecTexture,
		SamplerState::Filter a_TextureFilter,
		SamplerState::Mode a_TextureMode0,
		SamplerState::Mode a_TextureMode1);

	~LightingPassEffect();

	virtual void UpdateAffineMatrixs(AffineMatrixs* a_AffineMatrixs);
	virtual void UpdateTextures(std::shared_ptr<Texture2D> a_DiffuseTexture, std::shared_ptr<Texture2D> a_SpecularTexture);

	inline void SetDirectionalLightData(const void* a_Data)
	{
		m_DirectionalLightConstantBuffer->SetData(const_cast<void*>(a_Data));
	}

	inline void SetPointLightData(const void* a_Data)
	{
		m_PointLightConstantBuffer->SetData(const_cast<void*>(a_Data));
	}

	inline void SetSpotLightData(const void* a_Data)
	{
		m_SpotLightConstantBuffer->SetData(const_cast<void*>(a_Data));
	}

	inline void SetNumDirectionLights(_U32 a_Num)
	{
		m_NumDirectionalLight = a_Num;
	}

	inline void SetNumPointLights(_U32 a_Num)
	{
		m_NumPointLight = a_Num;
	}

	inline void SetNumSpotLights(_U32 a_Num)
	{
		m_NumSpotLight = a_Num;
	}

	inline void SetViewPosition(Vector3f a_Position)
	{
		m_ViewPosition = a_Position;
	}

private:
	// Light Constant Buffer
	_U32 m_NumDirectionalLight;
	_U32 m_NumPointLight;
	_U32 m_NumSpotLight;

	std::shared_ptr<ConstantBuffer> m_DirectionalLightConstantBuffer;
	std::shared_ptr<ConstantBuffer> m_NumDirectionalLightConstantBuffer;
	std::shared_ptr<ConstantBuffer> m_PointLightConstantBuffer;
	std::shared_ptr<ConstantBuffer> m_NumPointLightConstantBuffer;
	std::shared_ptr<ConstantBuffer> m_SpotLightConstantBuffer;
	std::shared_ptr<ConstantBuffer> m_NumSpotLightConstantBuffer;

	// View Position Constant Buffer
	Vector3f m_ViewPosition;
	std::shared_ptr<ConstantBuffer> m_ViewPosConstant;

	// Texture & Sampler
	std::shared_ptr<Texture2D> m_PositionTexture;
	std::shared_ptr<Texture2D> m_NormalTexture;
	std::shared_ptr<Texture2D> m_AlbedoSpecTexture;
	std::shared_ptr<SamplerState> m_TextureSampler;

};

NAMESPACE_MENGINE_END
