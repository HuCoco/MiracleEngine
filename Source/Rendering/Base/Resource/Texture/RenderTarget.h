#pragma once
#include <Independent/Platform/PreCompileHeader.h>
#include <Rendering/Base/Resource/Texture/TextureRenderTarget.h>
#include <Rendering/Base/Resource/Texture/TextureDepthStencil.h>

NAMESPACE_MENGINE_BEGIN

class RenderTarget
{
public:
	RenderTarget(_U32 a_NumRenderTarget, DataFormat a_RTFormat, _U32 a_Width, _U32 a_Height, 
		bool a_HasRTMipmap, DataFormat a_DSFormat = MENGINE_UNKNOWN);
	~RenderTarget();

	_U32 GetNumTargets() const;
	DataFormat GetRenderTargetFormat() const;
	_U32 GetWidth() const;
	_U32 GetHeight() const;
	bool HasRenderTargetMipmaps() const;
	DataFormat GetDepthStencilFormat() const;
	std::shared_ptr<TextureRenderTarget> const GetRTTexture(_U32 i) const;
	std::shared_ptr<TextureDepthStencil> const GetDSTexture() const;

	void AutogenerateRTMipmaps();
	bool WantAutogenerateRTMipmaps() const;

protected:
	std::vector<std::shared_ptr<TextureRenderTarget>> m_RenderTargetTextures;
	std::shared_ptr<TextureDepthStencil> m_DepthStencilTexture;
};

NAMESPACE_MENGINE_END