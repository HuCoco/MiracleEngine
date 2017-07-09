#pragma once
#include <Independent/Platform/PreCompileHeader.h>
#include <Rendering/VisualEffect/VisualEffect.h>
#include <Rendering/Base/Shaders/ProgramFactory.h>
#include <Rendering/Base/Resource/Texture/Texture2D.h>
#include <Rendering/Base/Resource/State/SamplerState.h>
#include <Rendering/Base/DataBlockInShader.h>
NAMESPACE_MENGINE_BEGIN

class DirectionalLightEffect : public VisualEffect
{
public:
	DirectionalLightEffect(ProgramFactory* a_Factory,
		SamplerState::Filter a_Filter, SamplerState::Mode a_Mode0, SamplerState::Mode a_Mode1,
		const std::shared_ptr<Texture2D>& a_TexDiffuse, const std::shared_ptr<Texture2D>& a_TexSpecular = nullptr);
	~DirectionalLightEffect();

	virtual void UpdateAffineMatrixs(AffineMatrixs* a_AffineMatrixs);
	virtual void UpdateTextures(std::shared_ptr<Texture2D> a_DiffuseTexture, std::shared_ptr<Texture2D> a_SpecularTexture);

	void SetAffineMatrixs(AffineMatrixs* a_AffineMatrixs);
	void SetDirectionalLight(DirectionalLightBlock* a_DirectionalLight);
	void SetMaterial(MaterialBlock::UseSpecularTex* a_Shininess);
	void SetCameraPosition(Vector4f* a_CameraPosition);
	void SetTexture(const std::shared_ptr<Texture2D>& a_TexDiffuse, const std::shared_ptr<Texture2D>& a_TexSpecular = nullptr);

private:
	AffineMatrixs m_AffineMatrixs;
	DirectionalLightBlock m_DirectionalLightBlock;
	MaterialBlock::UseSpecularTex m_Shininess;
	Vector4f m_CameraPosition;

	std::shared_ptr<ConstantBuffer> m_AffineMatrixsBuffer;
	std::shared_ptr<ConstantBuffer> m_DirectionalLightBuffer;
	std::shared_ptr<ConstantBuffer> m_MaterialBuffer;
	std::shared_ptr<ConstantBuffer> m_CameraPositionBuffer;
	std::shared_ptr<SamplerState> m_Sampler;
	std::shared_ptr<Texture2D> m_TexDiffuse;
	std::shared_ptr<Texture2D> m_TexSpecular;

	static const std::string GLSLVertexShaderPath;
	static const std::string GLSLFragmentShaderPath;
	static const std::string HLSLShaderPath;
};

NAMESPACE_MENGINE_END