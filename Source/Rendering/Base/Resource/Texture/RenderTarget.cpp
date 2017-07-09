#include <Rendering/Base/Resource/Texture/RenderTarget.h>


Miracle::RenderTarget::RenderTarget(_U32 a_NumRenderTarget, DataFormat a_RTFormat, _U32 a_Width, _U32 a_Height, bool a_HasRTMipmap, DataFormat a_DSFormat)
{
	if (a_NumRenderTarget > 0)
	{
		m_RenderTargetTextures.resize(a_NumRenderTarget);
		for(_U32 i = 0 ; i < a_NumRenderTarget; ++i)
		{
			m_RenderTargetTextures[i] = std::make_shared<TextureRenderTarget>(a_RTFormat, a_Width, a_Height, a_HasRTMipmap);
			void* data = malloc(m_RenderTargetTextures[i]->GetNumBytes());
			m_RenderTargetTextures[i]->SetData(data);
		}

		if (a_DSFormat != MENGINE_UNKNOWN)
		{
			if (DataFormatUtils::IsDepth(a_DSFormat))
			{
				m_DepthStencilTexture = std::make_shared<TextureDepthStencil>(a_DSFormat, a_Width, a_Height);
				void* data = malloc(m_DepthStencilTexture->GetNumBytes());
				m_DepthStencilTexture->SetData(data);
			}
			else
			{
				MENGINE_ASSERT_MSG(false, "Invalid depth-stencil format.");
			}
		}
	}
	else
	{
		MENGINE_ASSERT_MSG(false, "Number of targets must be at least one.");
	}
}


Miracle::RenderTarget::~RenderTarget()
{
}

_U32 Miracle::RenderTarget::GetNumTargets() const
{
	return static_cast<_U32>(m_RenderTargetTextures.size());
}

Miracle::DataFormat Miracle::RenderTarget::GetRenderTargetFormat() const
{
	if (m_RenderTargetTextures.size() > 0)
	{
		return m_RenderTargetTextures[0]->GetDataFormat();
	}

	MENGINE_ASSERT_MSG(false, "Unexpected condition.");
	return MENGINE_UNKNOWN;
}

_U32 Miracle::RenderTarget::GetWidth() const
{
	if (m_RenderTargetTextures.size() > 0)
	{
		return m_RenderTargetTextures[0]->GetWidth();
	}

	MENGINE_ASSERT_MSG(false, "Unexpected condition.");
	return 0;
}

_U32 Miracle::RenderTarget::GetHeight() const
{
	if (m_RenderTargetTextures.size() > 0)
	{
		return m_RenderTargetTextures[0]->GetHeight();
	}

	MENGINE_ASSERT_MSG(false, "Unexpected condition.");
	return 0;
}

bool Miracle::RenderTarget::HasRenderTargetMipmaps() const
{
	if (m_RenderTargetTextures.size() > 0)
	{
		return m_RenderTargetTextures[0]->HasMipmaps();
	}

	MENGINE_ASSERT_MSG(false, "Unexpected condition.");
	return false;
}

Miracle::DataFormat Miracle::RenderTarget::GetDepthStencilFormat() const
{
	if (m_DepthStencilTexture)
	{
		return m_DepthStencilTexture->GetDataFormat();
	}

	MENGINE_ASSERT_MSG(false, "Unexpected condition.");
	return MENGINE_UNKNOWN;
}

std::shared_ptr<Miracle::TextureRenderTarget> const Miracle::RenderTarget::GetRTTexture(_U32 i) const
{
	if (i < static_cast<int>(m_RenderTargetTextures.size()))
	{
		return m_RenderTargetTextures[i];
	}

	MENGINE_ASSERT_MSG(false,"Invalid index.");
	return nullptr;
}

std::shared_ptr<Miracle::TextureDepthStencil> const Miracle::RenderTarget::GetDSTexture() const
{
	return m_DepthStencilTexture;
}

void Miracle::RenderTarget::AutogenerateRTMipmaps()
{
	if (HasRenderTargetMipmaps())
	{
		for each (auto& texture in m_RenderTargetTextures)
		{
			texture->AutogenerateMipmaps();
		}
	}
}

bool Miracle::RenderTarget::WantAutogenerateRTMipmaps() const
{
	if (m_RenderTargetTextures.size() > 0)
	{
		return m_RenderTargetTextures[0]->WantAutogenerateMipmaps();
	}

	MENGINE_ASSERT_MSG(false,"Unexpected condition.");
	return false;
}
