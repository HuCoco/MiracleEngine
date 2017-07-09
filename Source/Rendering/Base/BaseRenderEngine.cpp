#include <Rendering/Base/BaseRenderEngine.h>



Miracle::BaseRenderEngine::BaseRenderEngine()
	: m_Width(0)
	, m_Height(0)
	, m_ClearDepth(1.0f)
	, m_ClearStencil(0)
	, m_ClearColor()
{
}


Miracle::BaseRenderEngine::~BaseRenderEngine()
{
	DestroyDefaultGlobalState();
}

void Miracle::BaseRenderEngine::CreateDefaultGlobalState()
{
	m_DefaultBlendState = std::make_shared<BlendState>();
	m_DefaultDepthStencilState = std::make_shared<DepthStencilState>();
	m_DefaultRasterizerState = std::make_shared<RasterizerState>();

	m_DefaultBlendState->SetName("BaseEngine::m_DefaultBlendState");
	m_DefaultDepthStencilState->SetName("BaseEngine::m_DefaultDepthStencilState");
	m_DefaultRasterizerState->SetName("BaseEngine::m_DefaultRasterizerState");

	SetDefaultBlendState();	
	SetDefaultDepthStencilState();
	SetDefaultRasterizerState();
}

void Miracle::BaseRenderEngine::DestroyDefaultGlobalState()
{
	m_DefaultBlendState = nullptr;
	m_DefaultDepthStencilState = nullptr;
	m_DefaultRasterizerState = nullptr;
	m_ActiveBlendState = nullptr;
	m_ActiveDepthStencilState = nullptr;
	m_ActiveRasterizerState = nullptr;
}
