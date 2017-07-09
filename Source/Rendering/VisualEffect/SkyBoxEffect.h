#pragma once
#include <Independent/Platform/PreCompileHeader.h>
#include <Rendering/VisualEffect/VisualEffect.h>
#include <Rendering/Base/DataBlockInShader.h>
#include <Rendering/Base/Resource/Buffer/ConstantBuffer.h>
#include <Rendering/Base/Resource/Texture/TextureCube.h>
#include <Rendering/Base/Resource/State/SamplerState.h>
NAMESPACE_MENGINE_BEGIN

class SkyBoxEffect : public VisualEffect
{
public:
	SkyBoxEffect(ProgramFactory* a_Factory);
	~SkyBoxEffect();

	virtual void UpdateAffineMatrixs(AffineMatrixs* a_AffineMatrixs);
	virtual void UpdateTextures(std::shared_ptr<Texture2D> a_DiffuseTexture, std::shared_ptr<Texture2D> a_SpecularTexture);

	virtual void Update(SkyBoxMatrixs* a_SkyboxMatrixs);
	virtual void Update(std::shared_ptr<TextureCube> m_TextureCube);

private:
	SkyBoxMatrixs m_SkyBoxMatrixs;
	std::shared_ptr<ConstantBuffer> m_SkyBoxMatrixsBuffer;
	std::shared_ptr<SamplerState> m_SamplerCube;
	std::shared_ptr<TextureCube> m_TextureCube;
};

NAMESPACE_MENGINE_END