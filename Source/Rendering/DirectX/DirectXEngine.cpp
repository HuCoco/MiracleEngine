#include <Rendering/DirectX/DirectXEngine.h>

#include <Rendering/Base/Resource/Buffer/VertexBuffer.h>
#include <Rendering/Base/Resource/Buffer/IndexBuffer.h>
#include <Rendering/Base/Resource/Buffer/ConstantBuffer.h>

#include <Rendering/Base/Resource/Texture/TextureSingle.h>
#include <Rendering/Base/Resource/Texture/TextureArray.h>
#include <Rendering/Base/Resource/Texture/Texture1D.h>
#include <Rendering/Base/Resource/Texture/Texture2D.h>
#include <Rendering/Base/Resource/Texture/Texture3D.h>

#include <Rendering/DirectX/Resource/Buffer/DirectXConstantBuffer.h>
#include <Rendering/DirectX/Resource/Buffer/DirectXVertexBuffer.h>
#include <Rendering/DirectX/Resource/Buffer/DirectXIndexBuffer.h>
#include <Rendering/DirectX/Resource/Texture/DirectXTextureSingle.h>
#include <Rendering/DirectX/Resource/Texture/DirectXTexture1D.h>
#include <Rendering/DirectX/Resource/Texture/DirectXTexture2D.h>
#include <Rendering/DirectX/Resource/Texture/DirectXTexture3D.h>
#include <Rendering/DirectX/Resource/Texture/DirectXTextureRenderTarget.h>
#include <Rendering/DirectX/Resource/Texture/DirectXTextureDepthStencil.h>
#include <Rendering/DirectX/Resource/Texture/DirectXTextureArray.h>
#include <Rendering/DirectX/Resource/Texture/DirectXTexture1DArray.h>
#include <Rendering/DirectX/Resource/Texture/DirectXTexture2DArray.h>
#include <Rendering/DirectX/Resource/Texture/DirectXTextureCube.h>
#include <Rendering/DirectX/Resource/Texture/DirectXTextureCubeArray.h>
#include <Rendering/DirectX/Resource/Texture/DirectXRenderTarget.h>

#include <Rendering/DirectX/Resource/State/DirectXSamplerState.h>
#include <Rendering/DirectX/Resource/State/DirectXBlendState.h>
#include <Rendering/DirectX/Resource/State/DirectXRasterizerState.h>
#include <Rendering/DirectX/Resource/State/DirectXDepthStencilState.h>

#include <Rendering/DirectX/Shaders/HLSL/HLSLVisualProgram.h>
#include <Rendering/DirectX/InputLayout/DirectXInputLayout.h>
#include <Rendering/DirectX/InputLayout/DirectXInputLayoutManager.h>
#include <Rendering/DirectX/Shaders/HLSL/HLSLProgramFactory.h>

Miracle::DirectXEngine::DirectXEngine(HWND a_Handle, UINT a_XSize, UINT a_YSize, D3D_FEATURE_LEVEL a_MinFeatureLevel)
{
	Initialize(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0, a_MinFeatureLevel);

	if (CreateDevice() && CreateSwapChain(a_Handle, a_XSize, a_YSize) && CreateBackBuffer(a_XSize, a_YSize))
	{
		CreateDefaultGlobalState();
	}
	else
	{
		DestroyBackBuffer();
		DestroySwapChain();
		DestroyDevice();
	}
}

Miracle::DirectXEngine::~DirectXEngine()
{

}

void Miracle::DirectXEngine::Initialize(IDXGIAdapter* a_Adapter,
	D3D_DRIVER_TYPE a_DriverType, HMODULE a_SoftwareModule, UINT a_Flags, D3D_FEATURE_LEVEL a_MinFeatureLevel)
{
	m_Adapter = a_Adapter;
	m_DriverType = a_DriverType;
	m_SoftwareModule = a_SoftwareModule;
	m_Flags = a_Flags;
	m_MinFeatureLevel = a_MinFeatureLevel;
	m_Device = nullptr;
	m_Immediate = nullptr;
	m_FeatureLevel = D3D_FEATURE_LEVEL_9_1;

	m_SwapChain = nullptr;
	m_ColorBuffer = nullptr;
	m_ColorView = nullptr;
	m_DepthStencilBuffer = nullptr;
	m_DepthStencilView = nullptr;
	m_Viewport.TopLeftX = 0.0f;
	m_Viewport.TopLeftY = 0.0f;
	m_Viewport.Width = 0.0f;
	m_Viewport.Height = 0.0f;
	m_Viewport.MinDepth = 0.0f;
	m_Viewport.MaxDepth = 0.0f;

	m_NumActiveRenderTargets = 0;
	m_ActiveRenderTargets.fill(nullptr);
	m_ActiveDepthStencil = nullptr;
	m_SaveViewport = m_Viewport;
	m_SaveRenderTargets.fill(nullptr);
	m_SaveDepthStencil = nullptr;

	m_InputLayoutManager = std::make_unique<DirectXInputLayoutManager>();

	m_RenderResourceCreators =
	{
		nullptr,							//	GRAPHICS_RESOURCE[abstract]
		nullptr,							//	RESOURCE[abstract] 
		nullptr,							//	BUFFER[abstract]  
		&DirectXConstantBuffer::Create,		//	CONSTANT_BUFFER,
		nullptr,							//	TEXTURE_BUFFER,
		&DirectXVertexBuffer::Create,		//	VERTEX_BUFFER,
		&DirectXIndexBuffer::Create,			//	INDEX_BUFFER,
		nullptr, 							//	TEXTURE[abstract]  
		nullptr, 							//	TEXTURE_SINGLE[abstract] 
		&DirectXTexture1D::Create,			//	TEXTURE1D,
		&DirectXTexture2D::Create,			//	TEXTURE2D,
		&DirectXTextureRenderTarget::Create,	//	TEXTURE_RENDER_TARGET,
		&DirectXTextureDepthStencil::Create,	//	TEXTURE_DEPTH_STENCIL,
		&DirectXTexture3D::Create,			//	TEXTURE3D,
		nullptr, 							//	TEXTURE_ARRAY[abstract] 
		&DirectXTexture1DArray::Create,		//	TEXTURE1D_ARRAY,
		&DirectXTexture2DArray::Create,		//	TEXTURE2D_ARRAY,
		&DirectXTextureCube::Create,			//	TEXTURE_CUBE,
		&DirectXTextureCubeArray::Create,	//	TEXTURE_CUBE_ARRAY,
		nullptr, 							//	SHADER, 
		&DirectXVertexShader::Create, 		//	VERTEX_SHADER,
		nullptr, 							//	GEOMETRY_SHADER,
		&DirectXPixelShader::Create,		//	PIXEL_SHADER,
		nullptr, 							//	COMPUTE_SHADER,
		nullptr, 							//	STATE[abstract] 
		&DirectXSamplerState::Create,		//	SAMPLER_STATE,
		&DirectXBlendState::Create,			//	BLEND_STATE,
		&DirectXDepthStencilState::Create,	//	DEPTH_STENCIL_STATE,
		&DirectXRasterizerState::Create		//	RASTERIZER_STATE,
	};

	m_RenderTargetResourceCreator = &DirectXRenderTarget::Create;
}

bool Miracle::DirectXEngine::CreateDevice()
{
	if (m_Adapter)
	{
		m_DriverType = D3D_DRIVER_TYPE_UNKNOWN;
		return CreateBestMatchingDevice();
	}

	IDXGIFactory1* factory = nullptr;
	HRESULT hr = CreateDXGIFactory1(IID_PPV_ARGS(&factory));
	if (FAILED(hr))
	{
		factory->Release();
		return false;
	}

	if (m_DriverType == D3D_DRIVER_TYPE_HARDWARE)
	{
		for (uint32_t i = 0; /**/; ++i)
		{
			IDXGIAdapter1* adapter = nullptr;
			if (factory->EnumAdapters1(i, &adapter) == DXGI_ERROR_NOT_FOUND)
			{
				factory->Release();
				return false;
			}

			DXGI_ADAPTER_DESC1 desc;
			hr = adapter->GetDesc1(&desc);
			if (FAILED(hr))
			{
				factory->Release();
				adapter->Release();
				return false;
			}

			if (desc.Flags != DXGI_ADAPTER_FLAG_SOFTWARE)
			{
				if (CreateBestMatchingDevice())
				{
					m_Adapter = adapter;
					factory->Release();
					adapter->Release();
					return true;
				}
			}
			else
			{
				m_DriverType = D3D_DRIVER_TYPE_WARP;
				if (CreateBestMatchingDevice())
				{
					m_Adapter = adapter;
					factory->Release();
					adapter->Release();
					return true;
				}
				else
				{
					return false;
				}
			}
		}
	}

	factory->Release();
	return false;
}

bool Miracle::DirectXEngine::CreateBestMatchingDevice()
{
	UINT const maxFeatureLevels = 7;
	D3D_FEATURE_LEVEL const featureLevels[maxFeatureLevels] =
	{
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
		D3D_FEATURE_LEVEL_9_3,
		D3D_FEATURE_LEVEL_9_2,
		D3D_FEATURE_LEVEL_9_1
	};

	UINT numFeatureLevels = 0;
	for (UINT i = 0; i < maxFeatureLevels; ++i)
	{
		if (m_MinFeatureLevel == featureLevels[i])
		{
			numFeatureLevels = i + 1;
			break;
		}
	}
	if (numFeatureLevels == 0)
	{
		MENGINE_ASSERT_MSG(false, "Unsupported minimum feature level.");
		return false;
	}

	for (UINT i = 0; i < numFeatureLevels; ++i)
	{
		HRESULT hr = D3D11CreateDevice(m_Adapter, m_DriverType, m_SoftwareModule,
			m_Flags, &featureLevels[i], 1, D3D11_SDK_VERSION,
			&m_Device, &m_FeatureLevel, &m_Immediate);
		if (SUCCEEDED(hr))
		{
			m_CreatorDevice = m_Device;
			if (i == 0 || i == 1)
			{
				HLSLProgramFactory::DefaultVersion = "5_0";
			}
			else if (i == 2 || i == 3)
			{
				HLSLProgramFactory::DefaultVersion = "4_0";
			}
			else if (i == 4)
			{
				HLSLProgramFactory::DefaultVersion = "4_0_level_9_3";
			}
			else
			{
				HLSLProgramFactory::DefaultVersion = "4_0_level_9_1";
			}
			return true;
		}
	}

	MENGINE_ASSERT_MSG(false, "Failed to create device");
	return false;
}

bool Miracle::DirectXEngine::CreateSwapChain(HWND a_Handle, UINT a_XSize, UINT a_YSize)
{
	m_Width = a_XSize;
	m_Height = a_YSize;

	struct DXGIInterfaces
	{
		DXGIInterfaces()
			:
			device(nullptr),
			adapter(nullptr),
			factory(nullptr)
		{
		}

		~DXGIInterfaces()
		{
			SafeRelease(factory);
			SafeRelease(adapter);
			SafeRelease(device);
		}

		IDXGIDevice* device;
		IDXGIAdapter* adapter;
		IDXGIFactory1* factory;
	};


	DXGIInterfaces dxgi;
	HRESULT hr = m_Device->QueryInterface(__uuidof(IDXGIDevice), reinterpret_cast<void**>(&dxgi.device));
	CHECK_HR_RETURN("Failed to get DXGI device interface", false);

	hr = dxgi.device->GetAdapter(&dxgi.adapter);
	CHECK_HR_RETURN("Failed to get DXGI adapter", false);

	hr = dxgi.adapter->GetParent(__uuidof(IDXGIFactory1), reinterpret_cast<void**>(&dxgi.factory));
	CHECK_HR_RETURN("Failed to get DXGI factory", false);

	DXGI_SWAP_CHAIN_DESC desc;
	desc.BufferDesc.Width = m_Width;
	desc.BufferDesc.Height = m_Height;
	desc.BufferDesc.RefreshRate.Numerator = 60;
	desc.BufferDesc.RefreshRate.Denominator = 1;
	desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	desc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.BufferUsage = DXGI_USAGE_BACK_BUFFER | DXGI_USAGE_RENDER_TARGET_OUTPUT;
	desc.BufferCount = 2;
	desc.OutputWindow = a_Handle;
	desc.Windowed = TRUE;
	desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	desc.Flags = 0;

	hr = dxgi.factory->CreateSwapChain(dxgi.device, &desc, &m_SwapChain);
	CHECK_HR_RETURN("Failed to create swap chain", false);

	return true;
}

bool Miracle::DirectXEngine::CreateBackBuffer(UINT a_XSize, UINT a_YSize)
{
	struct BackBuffer
	{
		BackBuffer()
		{
			SetToNull();
		}

		~BackBuffer()
		{
			SafeRelease(depthStencilView);
			SafeRelease(depthStencilBuffer);
			SafeRelease(colorView);
			SafeRelease(colorBuffer);
		}

		void SetToNull()
		{
			colorBuffer = nullptr;
			colorView = nullptr;
			depthStencilBuffer = nullptr;
			depthStencilView = nullptr;
		}

		ID3D11Texture2D* colorBuffer;
		ID3D11RenderTargetView* colorView;
		ID3D11Texture2D* depthStencilBuffer;
		ID3D11DepthStencilView* depthStencilView;
	};

	BackBuffer bb;

	HRESULT hr = m_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&bb.colorBuffer));
	CHECK_HR_RETURN("Failed to get color buffer", false);

	hr = m_Device->CreateRenderTargetView(bb.colorBuffer, nullptr, &bb.colorView);
	CHECK_HR_RETURN("Failed to create color view", false);

	D3D11_TEXTURE2D_DESC desc;
	desc.Width = m_Width;
	desc.Height = m_Height;
	desc.MipLevels = 1;
	desc.ArraySize = 1;
	desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_NONE;
	desc.MiscFlags = D3D11_RESOURCE_MISC_NONE;

	hr = m_Device->CreateTexture2D(&desc, nullptr, &bb.depthStencilBuffer);
	CHECK_HR_RETURN("Failed to create depth-stencil buffer", false);


	hr = m_Device->CreateDepthStencilView(bb.depthStencilBuffer, nullptr,
		&bb.depthStencilView);
	CHECK_HR_RETURN("Failed to create depth-stencil view", false);

	m_ColorBuffer = bb.colorBuffer;
	m_ColorView = bb.colorView;
	m_DepthStencilBuffer = bb.depthStencilBuffer;
	m_DepthStencilView = bb.depthStencilView;
	bb.SetToNull();

	m_Viewport.Width = static_cast<float>(a_XSize);
	m_Viewport.Height = static_cast<float>(a_YSize);
	m_Viewport.TopLeftX = 0.0f;
	m_Viewport.TopLeftY = 0.0f;
	m_Viewport.MinDepth = 0.0f;
	m_Viewport.MaxDepth = 1.0f;
	m_Immediate->RSSetViewports(1, &m_Viewport);

	m_NumActiveRenderTargets = 1;
	m_ActiveRenderTargets[0] = m_ColorView;
	m_ActiveDepthStencil = m_DepthStencilView;
	m_Immediate->OMSetRenderTargets(1, m_ActiveRenderTargets.data(), m_ActiveDepthStencil);
	return true;
}


bool Miracle::DirectXEngine::DestroyDevice()
{
	return FinalRelease(m_Immediate) == 0 && FinalRelease(m_Device) == 0;
}

bool Miracle::DirectXEngine::DestroySwapChain()
{
	bool successful = true;
	ULONG refs;

	if (m_SwapChain)
	{
		refs = m_SwapChain->Release();
		if (refs > 0)
		{
			MENGINE_ASSERT_MSG(false, "Swap chain not released.");
			successful = false;
		}
		m_SwapChain = nullptr;
	}

	return successful;
}

bool Miracle::DirectXEngine::DestroyBackBuffer()
{
	if (m_Immediate)
	{
		ID3D11RenderTargetView* rtView = nullptr;
		ID3D11DepthStencilView* dsView = nullptr;
		m_Immediate->OMSetRenderTargets(1, &rtView, dsView);
	}

	m_ActiveRenderTargets[0] = nullptr;
	m_ActiveDepthStencil = nullptr;

	return FinalRelease(m_ColorView) == 0
		&& FinalRelease(m_ColorBuffer) == 0
		&& FinalRelease(m_DepthStencilView) == 0
		&& FinalRelease(m_DepthStencilBuffer) == 0;
}

void Miracle::DirectXEngine::SetViewport(_I32 a_X, _I32 a_Y, _I32 a_Wdith, _I32 a_Height)
{
	UINT numViewports = 1;
	m_Immediate->RSGetViewports(&numViewports, &m_Viewport);
	MENGINE_ASSERT_MSG(1 == numViewports, "Failed to get viewport.");

	m_Viewport.TopLeftX = static_cast<float>(a_X);
	m_Viewport.TopLeftY = static_cast<float>(a_Y);
	m_Viewport.Width = static_cast<float>(a_Wdith);
	m_Viewport.Height = static_cast<float>(a_Height);
	m_Immediate->RSSetViewports(1, &m_Viewport);
}

void Miracle::DirectXEngine::GetViewport(_I32& a_X, _I32& a_Y, _I32& a_Wdith, _I32& a_Height) const
{
	UINT numViewports = 1;
	D3D11_VIEWPORT viewport;
	m_Immediate->RSGetViewports(&numViewports, &viewport);
	MENGINE_ASSERT_MSG(1 == numViewports, "Failed to get viewport.");

	a_X = static_cast<unsigned int>(viewport.TopLeftX);
	a_Y = static_cast<unsigned int>(viewport.TopLeftY);
	a_Wdith = static_cast<unsigned int>(viewport.Width);
	a_Height = static_cast<unsigned int>(viewport.Height);
}

void Miracle::DirectXEngine::SetDepthRange(_F32 a_Near, _F32 a_Far)
{
	UINT numViewports = 1;
	m_Immediate->RSGetViewports(&numViewports, &m_Viewport);
	MENGINE_ASSERT_MSG(1 == numViewports, "Failed to get viewport.");

	m_Viewport.MinDepth = a_Near;
	m_Viewport.MaxDepth = a_Far;
	m_Immediate->RSSetViewports(1, &m_Viewport);
}

void Miracle::DirectXEngine::GetDepthRange(_F32& a_Near, _F32& a_Far) const
{
	UINT numViewports = 1;
	D3D11_VIEWPORT viewport;
	m_Immediate->RSGetViewports(&numViewports, &viewport);
	MENGINE_ASSERT_MSG(1 == numViewports, "Failed to get viewport.");

	a_Near = viewport.MinDepth;
	a_Far = viewport.MaxDepth;
}

bool Miracle::DirectXEngine::Resize(_U32 a_Wdith, _U32 a_Height)
{
	// Release the previous back buffer before resizing.
	if (DestroyBackBuffer())
	{
		// Attempt to resize the back buffer to the incoming width and height.
		DXGI_SWAP_CHAIN_DESC desc;
		m_SwapChain->GetDesc(&desc);
		HRESULT hr = m_SwapChain->ResizeBuffers(desc.BufferCount, a_Wdith, a_Height,
			DXGI_FORMAT_R8G8B8A8_UNORM, 0);
		if (SUCCEEDED(hr))
		{
			// The attempt succeeded, so create new color and depth-stencil
			// objects.
			return CreateBackBuffer(a_Wdith, a_Height);
		}

		// The attempt to resize failed, so restore the back buffer to its
		// previous width and height.
		a_Wdith = desc.BufferDesc.Width;
		a_Height = desc.BufferDesc.Height;
		hr = m_SwapChain->ResizeBuffers(desc.BufferCount, a_Wdith, a_Height,
			DXGI_FORMAT_R8G8B8A8_UNORM, 0);
		if (SUCCEEDED(hr))
		{
			return CreateBackBuffer(a_Wdith, a_Height);
		}
	}
	return false;
}

void Miracle::DirectXEngine::ClearColorBuffer()
{
	ID3D11RenderTargetView* rtViews[D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT] = { nullptr };
	ID3D11DepthStencilView* dsView = nullptr;

	m_Immediate->OMGetRenderTargets(m_NumActiveRenderTargets, rtViews, &dsView);
	SafeRelease(dsView);
	for (unsigned int i = 0; i < m_NumActiveRenderTargets; ++i)
	{
		if (rtViews[i])
		{
			m_Immediate->ClearRenderTargetView(rtViews[i], &m_ClearColor[0]);
			rtViews[i]->Release();
		}
	}
}

void Miracle::DirectXEngine::ClearDepthBuffer()
{
	ID3D11DepthStencilView* dsView = nullptr;
	ID3D11RenderTargetView* rtView = nullptr;
	m_Immediate->OMGetRenderTargets(1, &rtView, &dsView);
	SafeRelease(rtView);
	if (dsView)
	{
		m_Immediate->ClearDepthStencilView(dsView, D3D11_CLEAR_DEPTH, m_ClearDepth, 0);
		dsView->Release();
	}
}

void Miracle::DirectXEngine::ClearStencilBuffer()
{
	ID3D11DepthStencilView* dsView = nullptr;
	ID3D11RenderTargetView* rtView = nullptr;
	m_Immediate->OMGetRenderTargets(1, &rtView, &dsView);
	SafeRelease(rtView);
	if (dsView)
	{
		m_Immediate->ClearDepthStencilView(dsView, D3D11_CLEAR_STENCIL, 0.0f,
			static_cast<UINT8>(m_ClearStencil));
		dsView->Release();
	}
}

void Miracle::DirectXEngine::ClearBuffers()
{
	ID3D11RenderTargetView* rtViews[D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT] = { nullptr };
	ID3D11DepthStencilView* dsView = nullptr;

	m_Immediate->OMGetRenderTargets(m_NumActiveRenderTargets, rtViews, &dsView);
	for (unsigned int i = 0; i < m_NumActiveRenderTargets; ++i)
	{
		if (rtViews[i])
		{
			m_Immediate->ClearRenderTargetView(rtViews[i], &m_ClearColor[0]);
			rtViews[i]->Release();
		}
	}
	if (dsView)
	{
		m_Immediate->ClearDepthStencilView(dsView,
			D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, m_ClearDepth,
			static_cast<UINT8>(m_ClearStencil));
		dsView->Release();
	}
}

void Miracle::DirectXEngine::SetBlendState(const std::shared_ptr<BlendState>& a_State)
{
	if (a_State)
	{
		if (a_State != m_ActiveBlendState)
		{
			DirectXBlendState* dxState = static_cast<DirectXBlendState*>(Bind(a_State));
			if (dxState)
			{
				dxState->Enable(m_Immediate);
				m_ActiveBlendState = a_State;
			}
			else
			{
				MENGINE_ASSERT_MSG(false, "Failed to bind blend state.");
			}
		}
	}
	else
	{
		MENGINE_ASSERT_MSG(false, "Input state is null.");
	}
}

void Miracle::DirectXEngine::SetDepthStencilState(const std::shared_ptr<DepthStencilState>& a_State)
{
	if (a_State)
	{
		if (a_State != m_ActiveDepthStencilState)
		{
			DirectXDepthStencilState* dxState = static_cast<DirectXDepthStencilState*>(Bind(a_State));
			if (dxState)
			{
				dxState->Enable(m_Immediate);
				m_ActiveDepthStencilState = a_State;
			}
			else
			{
				MENGINE_ASSERT_MSG(false, "Failed to bind depth-stencil state.");
			}
		}
	}
	else
	{
		MENGINE_ASSERT_MSG(false, "Input state is null.");
	}
}

void Miracle::DirectXEngine::SetRasterizerState(const std::shared_ptr<RasterizerState>& a_State)
{
	if (a_State)
	{
		if (a_State != m_ActiveRasterizerState)
		{
			DirectXRasterizerState* dxState = static_cast<DirectXRasterizerState*>(Bind(a_State));
			if (dxState)
			{
				dxState->Enable(m_Immediate);
				m_ActiveRasterizerState = a_State;
			}
			else
			{
				MENGINE_ASSERT_MSG(false, "Failed to bind rasterizer state.");
			}
		}
	}
	else
	{
		MENGINE_ASSERT_MSG(false, "Input state is null.");
	}
}

void Miracle::DirectXEngine::Enable(const std::shared_ptr<RenderTarget>& target)
{
	DirectXRenderTarget* dxTarget = static_cast<DirectXRenderTarget*>(Bind(target));
	dxTarget->Enable(m_Immediate);
	m_NumActiveRenderTargets = target->GetNumTargets();
}

void Miracle::DirectXEngine::Disable(const std::shared_ptr<RenderTarget>& target)
{
	DirectXRenderTarget* dxTarget = static_cast<DirectXRenderTarget*>(Bind(target));
	if (dxTarget)
	{
		dxTarget->Disable(m_Immediate);
		m_NumActiveRenderTargets = 1;

		// The assumption is that Disable is called after you have written
		// the draw target outputs.  If the render targets want automatic
		// mipmap generation, we do so here.
		if (target->WantAutogenerateRTMipmaps())
		{
			unsigned int const numTargets = target->GetNumTargets();
			for (unsigned int i = 0; i < numTargets; ++i)
			{
				DirectXTexture* dxTexture = static_cast<DirectXTexture*>(Get(target->GetRTTexture(i)));
				ID3D11ShaderResourceView* srView = dxTexture->GetShaderResourceView();
				if (srView)
				{
					m_Immediate->GenerateMips(dxTexture->GetShaderResourceView());
				}
			}
		}
	}
}

void Miracle::DirectXEngine::EnableDepthStencil(const std::shared_ptr<RenderTarget>& target)
{
	DirectXRenderTarget* dxTarget = static_cast<DirectXRenderTarget*>(Bind(target));
	dxTarget->EnableDepthStencilBuffer(m_Immediate);
}

void Miracle::DirectXEngine::DisableDepthStencil(const std::shared_ptr<RenderTarget>& target)
{
	DirectXRenderTarget* dxTarget = static_cast<DirectXRenderTarget*>(Bind(target));
	dxTarget->DisableDepthStencilBuffer(m_Immediate);
}

bool Miracle::DirectXEngine::Update(const std::shared_ptr<Buffer>& a_Buffer)
{
	if (!a_Buffer->GetData())
	{
		MENGINE_ASSERT_MSG(false, "Buffer does not have system memory, creating it.");
	}

	DirectXBuffer* dxBuffer = static_cast<DirectXBuffer*>(Bind(a_Buffer));
	return dxBuffer->Update(m_Immediate);
}

bool Miracle::DirectXEngine::Update(const std::shared_ptr<TextureSingle>& a_Texture)
{
	if (!a_Texture->GetData())
	{
		MENGINE_ASSERT_MSG(false, "Texture does not have system memory, creating it.");
	}

	DirectXTexture* dxTexture = static_cast<DirectXTexture*>(Bind(a_Texture));
	return dxTexture->Update(m_Immediate);
}

bool Miracle::DirectXEngine::Update(const std::shared_ptr<TextureSingle>& a_Texture, _U32 a_Level)
{
	if (!a_Texture->GetData())
	{
		MENGINE_ASSERT_MSG(false, "Texture does not have system memory, creating it.");
	}

	DirectXTexture* dxTexture = static_cast<DirectXTexture*>(Bind(a_Texture));
	unsigned int sri = a_Texture->GetIndex(0, a_Level);
	return dxTexture->Update(m_Immediate, sri);
}

bool Miracle::DirectXEngine::Update(const std::shared_ptr<TextureArray>& a_TextureArray)
{
	if (!a_TextureArray->GetData())
	{
		MENGINE_ASSERT_MSG(false, "Texture array does not have system memory, creating it.");
	}

	DirectXTextureArray* dxTextureArray = static_cast<DirectXTextureArray*>(Bind(a_TextureArray));
	return dxTextureArray->Update(m_Immediate);
}

bool Miracle::DirectXEngine::Update(const std::shared_ptr<TextureArray>& a_TextureArray, _U32 a_Item, _U32 a_Level)
{
	if (!a_TextureArray->GetData())
	{
		MENGINE_ASSERT_MSG(false, "Texture array does not have system memory, creating it.");
	}

	DirectXTextureArray* dxTextureArray = static_cast<DirectXTextureArray*>(Bind(a_TextureArray));
	unsigned int sri = a_TextureArray->GetIndex(a_Item, a_Level);
	return dxTextureArray->Update(m_Immediate, sri);
}

bool Miracle::DirectXEngine::CopyMem2GraphMem(const std::shared_ptr<Buffer>& a_Buffer)
{
	if (!a_Buffer->GetData())
	{
		MENGINE_ASSERT_MSG(false, "Buffer does not have system memory, creating it.");
	}

	DirectXBuffer* dxBuffer = static_cast<DirectXBuffer*>(Bind(a_Buffer));
	return dxBuffer->CopyMem2GraphMem(m_Immediate);
}

bool Miracle::DirectXEngine::CopyMem2GraphMem(const std::shared_ptr<TextureSingle>& a_Texture)
{
	if (!a_Texture->GetData())
	{
		MENGINE_ASSERT_MSG(false,  "Texture does not have system memory, creating it.");
	}

	DirectXTexture* dxTexture = static_cast<DirectXTexture*>(Bind(a_Texture));
	return dxTexture->CopyMem2GraphMem(m_Immediate);
}

bool Miracle::DirectXEngine::CopyMem2GraphMem(const std::shared_ptr<TextureSingle>& a_Texture, _U32 a_Level)
{
	if (!a_Texture->GetData())
	{
		MENGINE_ASSERT_MSG(false, "Texture does not have system memory, creating it.");
	}

	DirectXTexture* dxTexture = static_cast<DirectXTexture*>(Bind(a_Texture));
	unsigned int sri = a_Texture->GetIndex(0, a_Level);
	return dxTexture->CopyMem2GraphMem(m_Immediate, sri);
}

bool Miracle::DirectXEngine::CopyMem2GraphMem(const std::shared_ptr<TextureArray>& a_TextureArray, _U32 a_Item, _U32 a_Level)
{
	if (!a_TextureArray->GetData())
	{
		MENGINE_ASSERT_MSG(false,  "Texture array does not have system memory, creating it.");
	}

	DirectXTextureArray* dxTextureArray = static_cast<DirectXTextureArray*>(
		Bind(a_TextureArray));
	unsigned int sri = a_TextureArray->GetIndex(a_Item, a_Level);
	return dxTextureArray->CopyMem2GraphMem(m_Immediate, sri);
}

bool Miracle::DirectXEngine::CopyMem2GraphMem(const std::shared_ptr<TextureArray>& a_TextureArray)
{
	if (!a_TextureArray->GetData())
	{
		MENGINE_ASSERT_MSG(false, "Texture array does not have system memory, creating it.");
	}

	DirectXTextureArray* dxTextureArray = static_cast<DirectXTextureArray*>(Bind(a_TextureArray));
	return dxTextureArray->CopyMem2GraphMem(m_Immediate);
}

bool Miracle::DirectXEngine::CopyGraphMem2Mem(const std::shared_ptr<Buffer>& a_Buffer)
{
	if (!a_Buffer->GetData())
	{
		MENGINE_ASSERT_MSG(false, "Buffer does not have system memory, creating it.");
	}

	DirectXBuffer* dxBuffer = static_cast<DirectXBuffer*>(Bind(a_Buffer));
	return dxBuffer->CopyGraphMem2Mem(m_Immediate);
}

bool Miracle::DirectXEngine::CopyGraphMem2Mem(const std::shared_ptr<TextureSingle>& a_Texture)
{
	if (!a_Texture->GetData())
	{
		MENGINE_ASSERT_MSG(false,  "Texture does not have system memory, creating it.");
	}

	DirectXTexture* dxTexture = static_cast<DirectXTexture*>(Bind(a_Texture));
	return dxTexture->CopyGraphMem2Mem(m_Immediate);
}

bool Miracle::DirectXEngine::CopyGraphMem2Mem(const std::shared_ptr<TextureSingle>& a_Texture, _U32 a_Level)
{
	if (!a_Texture->GetData())
	{
		MENGINE_ASSERT_MSG(false, "Texture does not have system memory, creating it.");
	}

	DirectXTexture* dxTexture = static_cast<DirectXTexture*>(Bind(a_Texture));
	unsigned int sri = a_Texture->GetIndex(0, a_Level);
	return dxTexture->CopyGraphMem2Mem(m_Immediate, sri);
}

bool Miracle::DirectXEngine::CopyGraphMem2Mem(const std::shared_ptr<TextureArray>& a_TextureArray)
{
	if (!a_TextureArray->GetData())
	{
		MENGINE_ASSERT_MSG(false, "Texture array does not have system memory, creating it.");
	}

	DirectXTextureArray* dxTextureArray = static_cast<DirectXTextureArray*>(Bind(a_TextureArray));
	return dxTextureArray->CopyGraphMem2Mem(m_Immediate);
}

bool Miracle::DirectXEngine::CopyGraphMem2Mem(const std::shared_ptr<TextureArray>& a_TextureArray, _U32 a_Item, _U32 a_Level)
{
	if (!a_TextureArray->GetData())
	{
		MENGINE_ASSERT_MSG(false,  "Texture array does not have system memory, creating it.");
	}

	DirectXTextureArray* dxTextureArray = static_cast<DirectXTextureArray*>(Bind(a_TextureArray));
	unsigned int sri = a_TextureArray->GetIndex(a_Item, a_Level);
	return dxTextureArray->CopyGraphMem2Mem(m_Immediate, sri);
}

void Miracle::DirectXEngine::WaitForFinish()
{
	if (!m_WaitQuery)
	{
		D3D11_QUERY_DESC desc;
		desc.Query = D3D11_QUERY_EVENT;
		desc.MiscFlags = D3D11_QUERY_MISC_NONE;
		HRESULT hr = m_Device->CreateQuery(&desc, &m_WaitQuery);
		CHECK_HR_RETURN_NONE("CreateQuery failed in WaitForFinish");
	}

	m_Immediate->End(m_WaitQuery);
	BOOL data = 0;
	UINT size = sizeof(BOOL);
	while (S_OK != m_Immediate->GetData(m_WaitQuery, &data, size, 0))
	{
		// Wait for end of query.
	}
}

void Miracle::DirectXEngine::Flush()
{
	m_Immediate->Flush();
}

_U64 Miracle::DirectXEngine::DrawPrimitive(const std::shared_ptr<VertexBuffer>& a_VertexBuffer,
	const std::shared_ptr<IndexBuffer>& a_IndexBuffer, const std::shared_ptr<VisualEffect>& a_Effect)
{
	uint64_t numPixelsDrawn = 0;
	DirectXVertexShader* dxVShader;
	DirectXPixelShader* dxPShader;

	if (EnableShaders(a_Effect, dxVShader, dxPShader))
	{
		DirectXVertexBuffer* dxVBuffer = nullptr;
		DirectXInputLayout* dxLayout = nullptr;
		dxVBuffer = static_cast<DirectXVertexBuffer*>(Bind(a_VertexBuffer));
		DirectXInputLayoutManager* manager = static_cast<DirectXInputLayoutManager*>(m_InputLayoutManager.get());
		dxLayout = manager->Bind(m_Device, a_VertexBuffer.get(), a_Effect->GetVertexShader().get());
		dxVBuffer->Enable(m_Immediate);
		dxLayout->Enable(m_Immediate);

		DirectXIndexBuffer* dxIBuffer = nullptr;
		if (a_IndexBuffer->IsIndexed())
		{
			dxIBuffer = static_cast<DirectXIndexBuffer*>(Bind(a_IndexBuffer));
			dxIBuffer->Enable(m_Immediate);
		}

		DrawPrimitive(a_VertexBuffer.get(), a_IndexBuffer.get());

		dxVBuffer->Disable(m_Immediate);
		dxLayout->Disable(m_Immediate);
		if (dxIBuffer)
		{
			dxIBuffer->Disable(m_Immediate);
		}
		DisableShaders(a_Effect, dxVShader, dxPShader);
	}
	return 0;
}

_U64 Miracle::DirectXEngine::DrawPrimitive(VertexBuffer* vbuffer, IndexBuffer* ibuffer)
{
	UINT numActiveVertices = vbuffer->GetNumActiveElements();
	UINT vertexOffset = vbuffer->GetOffset();

	UINT numActiveIndices = ibuffer->GetNumActiveIndices();
	PrimitiveType type = ibuffer->GetPrimitiveType();

	switch (type)
	{
	case PrimitiveType::POLYPOINT:
		m_Immediate->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);
		break;
	case PrimitiveType::POLYSEGMENT_DISJOINT:
		m_Immediate->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
		break;
	case PrimitiveType::POLYSEGMENT_CONTIGUOUS:
		m_Immediate->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);
		break;
	case PrimitiveType::TRIMESH:
		m_Immediate->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		break;
	case PrimitiveType::TRISTRIP:
		m_Immediate->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
		break;
	case PrimitiveType::POLYSEGMENT_DISJOINT_ADJ:
		m_Immediate->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST_ADJ);
		break;
	case PrimitiveType::POLYSEGMENT_CONTIGUOUS_ADJ:
		m_Immediate->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP_ADJ);
		break;
	case PrimitiveType::TRIMESH_ADJ:
		m_Immediate->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST_ADJ);
		break;
	case PrimitiveType::TRISTRIP_ADJ:
		m_Immediate->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP_ADJ);
		break;
	default:
		MENGINE_ASSERT_MSG(false, "Unknown primitive topology.");
		return 0;
	}
	ID3D11Query* occlusionQuery = nullptr;
	uint64_t numPixelsDrawn = 0;


	if (ibuffer->IsIndexed())
	{
		if (numActiveIndices > 0)
		{
			m_Immediate->DrawIndexed(numActiveIndices, 0, vertexOffset);
		}
	}
	else
	{
		if (numActiveVertices > 0)
		{
			m_Immediate->Draw(numActiveVertices, vertexOffset);
		}
	}
	return 0;
}

void Miracle::DirectXEngine::DisplayColorBuffer(unsigned int syncInterval)
{
	m_SwapChain->Present(syncInterval, 0);
}

bool Miracle::DirectXEngine::EnableShaders(const std::shared_ptr<VisualEffect>& a_Effect,
	DirectXVertexShader*& a_VertexShader, DirectXPixelShader*& a_PixelShader)
{
	a_VertexShader = nullptr;
	a_PixelShader = nullptr;

	// Get the active vertex shader.
	if (!a_Effect->GetVertexShader())
	{
		MENGINE_ASSERT_MSG(false, "Effect does not have a vertex shader.");
		return false;
	}
	a_VertexShader = static_cast<DirectXVertexShader*>(Bind(a_Effect->GetVertexShader()));


	// Get the active pixel shader.
	if (!a_Effect->GetPixelShader())
	{
		MENGINE_ASSERT_MSG(false, "Effect does not have a pixel shader.");
		return false;
	}
	a_PixelShader = static_cast<DirectXPixelShader*>(Bind(a_Effect->GetPixelShader()));

	// Enable the shaders and resources.
	Enable(a_Effect->GetVertexShader().get(), a_VertexShader);
	Enable(a_Effect->GetPixelShader().get(), a_PixelShader);


	return true;
}

void Miracle::DirectXEngine::DisableShaders(const std::shared_ptr<VisualEffect>& a_Effect, DirectXVertexShader*& a_VertexShader, DirectXPixelShader*& a_PixelShader)
{
	Disable(a_Effect->GetPixelShader().get(), a_VertexShader);
	Disable(a_Effect->GetVertexShader().get(), a_PixelShader);
}

void Miracle::DirectXEngine::Enable(Shader* a_Shader, DirectXShader* a_DirectXShader)
{
	a_DirectXShader->Enable(m_Immediate);
	EnableCBuffers(a_Shader, a_DirectXShader);
	EnableTextures(a_Shader, a_DirectXShader);
	EnableTextureArrays(a_Shader, a_DirectXShader);
	EnableSamplers(a_Shader, a_DirectXShader);
}

void Miracle::DirectXEngine::Disable(Shader* a_Shader, DirectXShader* a_DirectXShader)
{
	DisableSamplers(a_Shader, a_DirectXShader);
	DisableTextureArrays(a_Shader, a_DirectXShader);
	DisableTextures(a_Shader, a_DirectXShader);
	DisableCBuffers(a_Shader, a_DirectXShader);
	a_DirectXShader->Disable(m_Immediate);
}


void Miracle::DirectXEngine::EnableCBuffers(Shader* a_Shader, DirectXShader* a_DirectXShader)
{
	int const index = ConstantBuffer::ShaderDataIndex;
	for each (auto const& cb in a_Shader->GetData(index))
	{
		if (cb.GraphicsResourceObject)
		{
			DirectXConstantBuffer* dxCB = static_cast<DirectXConstantBuffer*>(Bind(cb.GraphicsResourceObject));
			if (dxCB)
			{
				dxCB->Update(m_Immediate);
				a_DirectXShader->EnableConstantBuffer(m_Immediate, cb.BindPoint, dxCB->GetDirectXBuffer());
			}
			else
			{
				MENGINE_ASSERT_MSG(false, "Failed to bind constant buffer.");
			}
		}
		else
		{
			MENGINE_ASSERT_MSG(false, "constant buffer is null.");
		}
	}
}

void Miracle::DirectXEngine::DisableCBuffers(Shader* a_Shader, DirectXShader* a_DirectXShader)
{
	int const index = ConstantBuffer::ShaderDataIndex;
	for each (auto const& cb in a_Shader->GetData(index))
	{
		a_DirectXShader->DisableConstantBuffer(m_Immediate, cb.BindPoint);
	}
}

void Miracle::DirectXEngine::EnableTextures(Shader* a_Shader, DirectXShader* a_DirectXShader)
{
	int const index = TextureSingle::ShaderDataIndex;
	for each(auto const& tex in a_Shader->GetData(index))
	{
		if (tex.GraphicsResourceObject)
		{
			DirectXTextureSingle* dxTX = static_cast<DirectXTextureSingle*>(Bind(tex.GraphicsResourceObject));
			if (dxTX)
			{
				if (tex.IsGpuWritable)
				{
					a_DirectXShader->EnableUnorderedAccessView(m_Immediate, tex.BindPoint, dxTX->GetUnorderedAccessView(), 0xFFFFFFFFu);
				}
				else
				{
					a_DirectXShader->EnableShaderResourceView(m_Immediate, tex.BindPoint, dxTX->GetShaderResourceView());
				}
			}
			else
			{
				MENGINE_ASSERT_MSG(false, "Failed to bind texture.");
			}
		}
		else
		{
			MENGINE_ASSERT_MSG(false, "texture is null.");
		}
	}
}

void Miracle::DirectXEngine::DisableTextures(Shader* a_Shader, DirectXShader* a_DirectXShader)
{
	int const index = TextureSingle::ShaderDataIndex;
	for each(auto const& tex in a_Shader->GetData(index))
	{
		if (tex.IsGpuWritable)
		{
			a_DirectXShader->DisableUnorderedAccessView(m_Immediate, tex.BindPoint);
		}
		else
		{
			a_DirectXShader->DisableShaderResourceView(m_Immediate, tex.BindPoint);
		}
	}
}

void Miracle::DirectXEngine::EnableTextureArrays(Shader* a_Shader, DirectXShader* a_DirectXShader)
{
	int const index = TextureArray::ShaderDataIndex;
	for each(auto const& texs in a_Shader->GetData(index))
	{
		if (texs.GraphicsResourceObject)
		{
			DirectXTextureArray* dxTA = static_cast<DirectXTextureArray*>(Bind(texs.GraphicsResourceObject));
			if (dxTA)
			{
				if (texs.IsGpuWritable)
				{
					a_DirectXShader->EnableUnorderedAccessView(m_Immediate, texs.BindPoint, dxTA->GetUnorderedAccessView(), 0xFFFFFFFFu);
				}
				else
				{
					a_DirectXShader->EnableShaderResourceView(m_Immediate, texs.BindPoint, dxTA->GetShaderResourceView());
				}
			}
			else
			{
				MENGINE_ASSERT_MSG(false, "Failed to bind texture array.");
			}
		}
		else
		{
			MENGINE_ASSERT_MSG(false, "texture array is null.");
		}
	}
}

void Miracle::DirectXEngine::DisableTextureArrays(Shader* a_Shader, DirectXShader* a_DirectXShader)
{
	int const index = TextureArray::ShaderDataIndex;
	for each(auto const& texs in a_Shader->GetData(index))
	{
		if (texs.IsGpuWritable)
		{
			a_DirectXShader->DisableUnorderedAccessView(m_Immediate, texs.BindPoint);
		}
		else
		{
			a_DirectXShader->DisableShaderResourceView(m_Immediate, texs.BindPoint);
		}
	}
}

void Miracle::DirectXEngine::EnableSamplers(Shader* a_Shader, DirectXShader* a_DirectXShader)
{
	int const index = SamplerState::ShaderDataIndex;
	for each(auto const& sampler in a_Shader->GetData(index))
	{
		if (sampler.GraphicsResourceObject)
		{
			DirectXSamplerState* dxSS = static_cast<DirectXSamplerState*>(Bind(sampler.GraphicsResourceObject));
			if (dxSS)
			{
				a_DirectXShader->EnableSampler(m_Immediate, sampler.BindPoint, dxSS->GetD3DSamplerState());
			}
			else
			{
				MENGINE_ASSERT_MSG(false, "Failed to bind sampler state.");
			}
		}
		else
		{
			MENGINE_ASSERT_MSG(false, "sampler state is null.");
		}
	}
}

void Miracle::DirectXEngine::DisableSamplers(Shader* a_Shader, DirectXShader* a_DirectXShader)
{
	int const index = SamplerState::ShaderDataIndex;
	for each(auto const& sampler in a_Shader->GetData(index))
	{
		a_DirectXShader->DisableSampler(m_Immediate, sampler.BindPoint);
	}
}

