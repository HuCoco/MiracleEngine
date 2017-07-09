#include <Rendering/DirectX/Resource/Texture/DirectXRenderTarget.h>

Miracle::DirectXRenderTarget::DirectXRenderTarget(RenderTarget* a_RenderTarget,
	std::vector<DirectXTextureRenderTarget*>& a_RenderTargetTexures,
	DirectXTextureDepthStencil* a_DepthTargetTexure)
	: RenderTargetResource(a_RenderTarget)
	, m_RenderTargetTextures(a_RenderTargetTexures)
	, m_DepthStencilTexture(a_DepthTargetTexure)
	, m_RenderTargetViews(a_RenderTarget->GetNumTargets())
	, m_DepthStencilView(nullptr)
	, m_SaveRenderTargetViews(a_RenderTarget->GetNumTargets())
	, m_SaveDepthStencilView(nullptr)
{
	_U32 numTargets = a_RenderTarget->GetNumTargets();
	for (_U32 i = 0; i < numTargets; ++i)
	{
		m_RenderTargetViews[i] = m_RenderTargetTextures[i]->GetRenderTargetView();
		m_SaveRenderTargetViews[i] = nullptr;
	}

	if (m_DepthStencilTexture)
	{
		m_DepthStencilView = m_DepthStencilTexture->GetDepthStencilView();
	}
}

std::shared_ptr<Miracle::RenderTargetResource> Miracle::DirectXRenderTarget::Create(RenderTarget* a_RenderTarget,
	std::vector<RenderResource*>& a_RenderTargetTextures, RenderResource* a_DepthTargetTextures)
{
	std::vector<DirectXTextureRenderTarget*> dxRTTextures(a_RenderTargetTextures.size());
	for (size_t i = 0; i < a_RenderTargetTextures.size(); ++i)
	{
		dxRTTextures[i] = static_cast<DirectXTextureRenderTarget*>(a_RenderTargetTextures[i]);
	}
	DirectXTextureDepthStencil* dxDSTexture = static_cast<DirectXTextureDepthStencil*>(a_DepthTargetTextures);

	return std::make_shared<DirectXRenderTarget>(a_RenderTarget, dxRTTextures, dxDSTexture);
}

Miracle::DirectXRenderTarget::~DirectXRenderTarget()
{

}

void Miracle::DirectXRenderTarget::Enable(ID3D11DeviceContext* context)
{
	UINT numViewports = 1;
	context->RSGetViewports(&numViewports, &m_SaveViewport);

	UINT const numTargets = (UINT)m_Target->GetNumTargets();
	context->OMGetRenderTargets(numTargets, &m_SaveRenderTargetViews[0], &m_SaveDepthStencilView);

	D3D11_VIEWPORT viewport;
	viewport.Width = static_cast<float>(m_Target->GetWidth());
	viewport.Height = static_cast<float>(m_Target->GetHeight());
	viewport.TopLeftX = 0.0f;
	viewport.TopLeftY = 0.0f;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	context->RSSetViewports(1, &viewport);

	context->OMSetRenderTargets(numTargets, &m_RenderTargetViews[0], m_DepthStencilView);
}

void Miracle::DirectXRenderTarget::Disable(ID3D11DeviceContext* context)
{

	context->RSSetViewports(1, &m_SaveViewport);

	const _U32 numTargets = (_U32)m_Target->GetNumTargets();
	context->OMSetRenderTargets(numTargets, &m_SaveRenderTargetViews[0], m_SaveDepthStencilView);
	for (_U32 i = 0; i < numTargets; ++i)
	{
		if (m_SaveRenderTargetViews[i])
		{
			SafeRelease(m_SaveRenderTargetViews[i]);
		}
	}
	if (m_SaveDepthStencilView)
	{
		SafeRelease(m_SaveDepthStencilView);
	}
	context->Flush();
}

void Miracle::DirectXRenderTarget::EnableDepthStencilBuffer(ID3D11DeviceContext* context)
{
	context->Flush();
	UINT numViewports = 1;
	context->RSGetViewports(&numViewports, &m_SaveViewport);

	UINT const numTargets = (UINT)m_Target->GetNumTargets();
	context->OMGetRenderTargets(numTargets, &m_SaveRenderTargetViews[0], &m_SaveDepthStencilView);

	D3D11_VIEWPORT viewport;
	viewport.Width = static_cast<float>(m_Target->GetWidth());
	viewport.Height = static_cast<float>(m_Target->GetHeight());
	viewport.TopLeftX = 0.0f;
	viewport.TopLeftY = 0.0f;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	context->RSSetViewports(1, &viewport);

	context->OMSetRenderTargets(numTargets, &m_SaveRenderTargetViews[0], m_DepthStencilView);

}

void Miracle::DirectXRenderTarget::DisableDepthStencilBuffer(ID3D11DeviceContext* context)
{
	ID3D11RenderTargetView* rtViews[D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT] = { nullptr };
	ID3D11DepthStencilView* dsView = nullptr;
	context->OMSetRenderTargets(D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT, &m_SaveRenderTargetViews[0], m_SaveDepthStencilView);

	for (_U32 i = 0; i < D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT; ++i)
	{
		if (m_SaveRenderTargetViews[i])
		{
			SafeRelease(m_SaveRenderTargetViews[i]);
		}
	}
	if (m_SaveDepthStencilView)
	{
		SafeRelease(m_SaveDepthStencilView);
	}
}
