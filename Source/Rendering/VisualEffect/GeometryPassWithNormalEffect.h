#pragma once
#include <Independent/Platform/PreCompileHeader.h>
#include <Rendering/VisualEffect/VisualEffect.h>
#include <Rendering/OpenGL/Shaders/GLSLProgramFactory.h>

#include <Rendering/Base/Resource/Buffer/ConstantBuffer.h>
#include <Rendering/Base/Resource/Texture/Texture2D.h>
#include <Rendering/Base/Resource/State/SamplerState.h>

NAMESPACE_MENGINE_BEGIN

class GeometryPassWithNormalEffect : public VisualEffect
{
public:

	virtual void UpdateAffineMatrixs(AffineMatrixs* a_AffineMatrixs);
	virtual void UpdateTextures(std::shared_ptr<Texture2D> a_DiffuseTexture, std::shared_ptr<Texture2D> a_SpecularTexture);
	void UpdateNormalTexture(std::shared_ptr<Texture2D> a_DiffuseTexture);

	GeometryPassWithNormalEffect(ProgramFactory* a_Factory,
		SamplerState::Filter a_DiffuseTextureFilter,
		SamplerState::Mode a_DiffuseTextureMode0,
		SamplerState::Mode a_DiffuseTextureMode1);

	~GeometryPassWithNormalEffect();



private:
	AffineMatrixs mvp;
	std::shared_ptr<ConstantBuffer> MVPMatrixConstant;
	std::shared_ptr<Texture2D> m_DiffuseTexture;
	std::shared_ptr<Texture2D> m_SpecularTexture;
	std::shared_ptr<Texture2D> m_NormalTexture;
	std::shared_ptr<SamplerState> m_TextureSampler;
	bool m_IsNeedTranspose;
};

NAMESPACE_MENGINE_END