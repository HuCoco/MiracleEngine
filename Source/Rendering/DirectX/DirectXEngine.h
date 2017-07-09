#pragma once
#include <Independent/Platform/PreCompileHeader.h>
#include <ThirdParty/GraphicsKit/DirectXPreCompileHeader.h>
#include <Rendering/Base/GraphicsEngine.h>
#include <Rendering/VisualEffect/VisualEffect.h>
#include <Rendering/DirectX/Shaders/DirectXVertexShader.h>
#include <Rendering/DirectX/Shaders/DirectXPixelShader.h>

NAMESPACE_MENGINE_BEGIN

class DirectXEngine : public GraphicsEngine
{
public:
	DirectXEngine(HWND a_Handle, UINT a_XSize, UINT a_YSize, D3D_FEATURE_LEVEL a_MinFeatureLevel = D3D_FEATURE_LEVEL_11_0);
	~DirectXEngine();

	virtual void SetViewport(_I32 a_X, _I32 a_Y, _I32 a_Wdith, _I32 a_Height) override;
	virtual void GetViewport(_I32& a_X, _I32& a_Y, _I32& a_Wdith, _I32& a_Height) const override;
	virtual void SetDepthRange(_F32 a_Near, _F32 a_Far) override;
	virtual void GetDepthRange(_F32& a_Near, _F32& a_Far) const override;

	virtual bool Resize(_U32 a_Wdith, _U32 a_Height);

	virtual void ClearColorBuffer() override;
	virtual void ClearDepthBuffer() override;
	virtual void ClearStencilBuffer() override;
	virtual void ClearBuffers() override;
	virtual void DisplayColorBuffer(unsigned int syncInterval);

	virtual void SetBlendState(const std::shared_ptr<BlendState>& a_State) override;
	virtual void SetDepthStencilState(const std::shared_ptr<DepthStencilState>& a_State) override;
	virtual void SetRasterizerState(const std::shared_ptr<RasterizerState>& a_State);

	virtual void Enable(const std::shared_ptr<RenderTarget>& target) override;
	virtual void Disable(const std::shared_ptr<RenderTarget>& target) override;
	virtual void EnableDepthStencil(const std::shared_ptr<RenderTarget>& target) override;
	virtual void DisableDepthStencil(const std::shared_ptr<RenderTarget>& target) override;

	virtual bool Update(const std::shared_ptr<Buffer>& a_Buffer) override;
	virtual bool Update(const std::shared_ptr<TextureSingle>& a_Texture) override;
	virtual bool Update(const std::shared_ptr<TextureSingle>& a_Texture, _U32 a_Level) override;
	virtual bool Update(const std::shared_ptr<TextureArray>& a_TextureArray) override;
	virtual bool Update(const std::shared_ptr<TextureArray>& a_TextureArray, _U32 a_Item, _U32 a_Level) override;

	virtual bool CopyMem2GraphMem(const std::shared_ptr<Buffer>& a_Buffer) override;
	virtual bool CopyMem2GraphMem(const std::shared_ptr<TextureSingle>& a_Texture) override;
	virtual bool CopyMem2GraphMem(const std::shared_ptr<TextureSingle>& a_Texture, _U32 a_Level) override;
	virtual bool CopyMem2GraphMem(const std::shared_ptr<TextureArray>& textureArray) override;
	virtual bool CopyMem2GraphMem(const std::shared_ptr<TextureArray>& textureArray, _U32 a_Item, _U32 a_Level) override;

	virtual bool CopyGraphMem2Mem(const std::shared_ptr<Buffer>& a_Buffer) override;
	virtual bool CopyGraphMem2Mem(const std::shared_ptr<TextureSingle>& a_Texture) override;
	virtual bool CopyGraphMem2Mem(const std::shared_ptr<TextureSingle>& a_Texture, _U32 a_Level) override;
	virtual bool CopyGraphMem2Mem(const std::shared_ptr<TextureArray>& a_TextureArray) override;
	virtual bool CopyGraphMem2Mem(const std::shared_ptr<TextureArray>& a_TextureArray, _U32 a_Item, _U32 a_Level) override;

	virtual void WaitForFinish() override;

	virtual void Flush() override;

private:
	void Initialize(IDXGIAdapter* a_Adapter, D3D_DRIVER_TYPE a_DriverType, HMODULE a_SoftwareModule, UINT a_Flags, D3D_FEATURE_LEVEL a_MinFeatureLevel);
	bool CreateDevice();
	bool CreateBestMatchingDevice();
	bool CreateSwapChain(HWND a_Handle, UINT a_XSize, UINT a_YSize);
	bool CreateBackBuffer(UINT a_XSize, UINT a_YSize);
	bool DestroyDevice();
	bool DestroySwapChain();
	bool DestroyBackBuffer();

	_U64 DrawPrimitive(VertexBuffer* vbuffer, IndexBuffer* ibuffer);

	bool EnableShaders(const std::shared_ptr<VisualEffect>& a_Effect, DirectXVertexShader*& a_VertexShader, DirectXPixelShader*& a_PixelShader);
	void DisableShaders(const std::shared_ptr<VisualEffect>& a_Effect, DirectXVertexShader*& a_VertexShader, DirectXPixelShader*& a_PixelShader);
	void Enable(Shader* a_Shader, DirectXShader* a_DirectXShader);
	void Disable(Shader* a_Shader, DirectXShader* a_DirectXShader);
	void EnableCBuffers(Shader* a_Shader, DirectXShader* a_DirectXShader);
	void DisableCBuffers(Shader* a_Shader, DirectXShader* a_DirectXShader);
	void EnableTextures(Shader* a_Shader, DirectXShader* a_DirectXShader);
	void DisableTextures(Shader* a_Shader, DirectXShader* a_DirectXShader);
	void EnableTextureArrays(Shader* a_Shader, DirectXShader* a_DirectXShader);
	void DisableTextureArrays(Shader* a_Shader, DirectXShader* a_DirectXShader);
	void EnableSamplers(Shader* a_Shader, DirectXShader* a_DirectXShader);
	void DisableSamplers(Shader* a_Shader, DirectXShader* a_DirectXShader);

public:
	virtual _U64 DrawPrimitive(
		const std::shared_ptr<VertexBuffer>& a_VertexBuffer,
		const std::shared_ptr<IndexBuffer>& a_IndexBuffer,
		const std::shared_ptr<VisualEffect>& a_Effect) override;

public:
	IDXGIAdapter* m_Adapter;
	D3D_DRIVER_TYPE m_DriverType;
	HMODULE m_SoftwareModule;
	UINT m_Flags;
	D3D_FEATURE_LEVEL m_MinFeatureLevel;

	ID3D11Device* m_Device;
	ID3D11DeviceContext* m_Immediate;
	D3D_FEATURE_LEVEL m_FeatureLevel;

	IDXGISwapChain* m_SwapChain;
	ID3D11Texture2D* m_ColorBuffer;
	ID3D11RenderTargetView* m_ColorView;
	ID3D11Texture2D* m_DepthStencilBuffer;
	ID3D11DepthStencilView* m_DepthStencilView;
	D3D11_VIEWPORT m_Viewport;

	_U32 m_NumActiveRenderTargets;
	std::array<ID3D11RenderTargetView*, D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT> m_ActiveRenderTargets;
	ID3D11DepthStencilView* m_ActiveDepthStencil;
	D3D11_VIEWPORT m_SaveViewport;
	std::array<ID3D11RenderTargetView*, D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT> m_SaveRenderTargets;
	ID3D11DepthStencilView* m_SaveDepthStencil;

	ID3D11Query* m_WaitQuery;

protected:

};

NAMESPACE_MENGINE_END

