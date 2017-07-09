#pragma once
#include <Independent/Platform/PreCompileHeader.h>
#include <Rendering/VisualEffect/VisualEffect.h>
#include <Rendering/OpenGL/Shaders/GLSLProgramFactory.h>

#include <Rendering/Base/Resource/Buffer/ConstantBuffer.h>
#include <Rendering/Base/Resource/Texture/Texture2D.h>
#include <Rendering/Base/Resource/State/SamplerState.h>

NAMESPACE_MENGINE_BEGIN


class _declspec(align(16)) GeometryPassEffect : public VisualEffect
{
public:

	virtual void UpdateAffineMatrixs(AffineMatrixs* a_AffineMatrixs);
	virtual void UpdateTextures(std::shared_ptr<Texture2D> a_DiffuseTexture, std::shared_ptr<Texture2D> a_SpecularTexture);

	GeometryPassEffect(ProgramFactory* a_Factory,
		SamplerState::Filter a_DiffuseTextureFilter,
		SamplerState::Mode a_DiffuseTextureMode0,
		SamplerState::Mode a_DiffuseTextureMode1);

	~GeometryPassEffect();
private:
	AffineMatrixs mvp;
	std::shared_ptr<ConstantBuffer> MVPMatrixConstant;
	std::shared_ptr<Texture2D> m_DiffuseTexture;
	std::shared_ptr<Texture2D> m_SpecularTexture;
	std::shared_ptr<SamplerState> m_TextureSampler;
	bool m_IsNeedTranspose;
};

NAMESPACE_MENGINE_END