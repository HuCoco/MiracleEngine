#include "DeferredRenderer.h"
#include <Core/Engine/MEngine.h>
#include <Rendering/RenderSystem/RenderSystem.h>
#include <Rendering/VisualEffect/GeometryPassEffect.h>
#include <Rendering/VisualEffect/GeometryPassWithNormalEffect.h>
#include <Rendering/VisualEffect/LightingPassEffect.h>

_F32 Miracle::DeferredRenderer::s_QuadVertices[] = {
	1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
	1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
	-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
	-1.0f,  1.0f, 0.0f, 0.0f, 1.0f
};

_U32 Miracle::DeferredRenderer::s_QuadIndices[] = {
	0, 1, 3,
	1, 2, 3
};

Miracle::DeferredRenderer::DeferredRenderer(GraphicsEngine* a_RenderEngine)
	: BaseRenderer(a_RenderEngine)
{
	Initialze();
}


Miracle::DeferredRenderer::~DeferredRenderer()
{
}

void Miracle::DeferredRenderer::DoRender(World* a_World)
{
	GeometryPass(a_World);
	LightingPass(a_World);
}

void Miracle::DeferredRenderer::Initialze()
{
	m_MainRenderTarget = std::make_shared<RenderTarget>(
		3,
		MENGINE_R16G16B16A16_FLOAT,
		1920,
		1080,
		true,
		MENGINE_D32_FLOAT);

	VertexFormat QuatVertexFormat;
	QuatVertexFormat.AddAttribute(VertexSemantic::POSITION, MENGINE_R32G32B32_FLOAT);
	QuatVertexFormat.AddAttribute(VertexSemantic::TEXCOORD, MENGINE_R32G32_FLOAT);

	m_QuadVertexBuffer = std::make_shared<VertexBuffer>(QuatVertexFormat, 4);
	m_QuadVertexBuffer->SetData(s_QuadVertices);

	m_QuadIndexBuffer = std::make_shared<IndexBuffer>(TRIMESH, 2, sizeof(_U32));
	m_QuadIndexBuffer->SetData(s_QuadIndices);

	std::shared_ptr<GeometryPassEffect> GeometryPass = std::make_shared<GeometryPassEffect>(
		MEngine::Instance()->GetRenderSystem()->GetProgramFactory(),
		SamplerState::Filter::MIN_P_MAG_L_MIP_L,
		SamplerState::Mode::WRAP,
		SamplerState::Mode::WRAP);

	MEngine::Instance()->GetRenderSystem()->GetVisualEffectManager().AddEffect("GeometryPassEffect", GeometryPass);

	std::shared_ptr<GeometryPassWithNormalEffect> GeometryPassWithNormal = std::make_shared<GeometryPassWithNormalEffect>(
		MEngine::Instance()->GetRenderSystem()->GetProgramFactory(),
		SamplerState::Filter::MIN_P_MAG_L_MIP_L,
		SamplerState::Mode::WRAP,
		SamplerState::Mode::WRAP);

	MEngine::Instance()->GetRenderSystem()->GetVisualEffectManager().AddEffect("GeometryPassWithNormal", GeometryPassWithNormal);

	std::shared_ptr<LightingPassEffect> LightingPass = std::make_shared<LightingPassEffect>(
		MEngine::Instance()->GetRenderSystem()->GetProgramFactory(),
		m_MainRenderTarget->GetRTTexture(0),
		m_MainRenderTarget->GetRTTexture(1),
		m_MainRenderTarget->GetRTTexture(2),
		SamplerState::Filter::MIN_P_MAG_L_MIP_L,
		SamplerState::Mode::WRAP,
		SamplerState::Mode::WRAP);

	MEngine::Instance()->GetRenderSystem()->GetVisualEffectManager().AddEffect("LightingPassEffect", LightingPass);
}

void Miracle::DeferredRenderer::GeometryPass(World* a_World)
{
	m_RenderEngine->Enable(m_MainRenderTarget);
	m_RenderEngine->ClearBuffers();
	{
		a_World->GetUpdateManager().DoRender();
	}
	m_RenderEngine->Disable(m_MainRenderTarget);
}

void Miracle::DeferredRenderer::LightingPass(World* a_World)
{
	std::shared_ptr<LightingPassEffect> LightingPass = 
		std::static_pointer_cast<LightingPassEffect>(MEngine::Instance()->GetRenderSystem()->GetVisualEffectManager().GetEffect("LightingPassEffect"));

	LightingPass->SetDirectionalLightData(a_World->GetLightManager().GetDirectionalLightsData());
	LightingPass->SetNumDirectionLights(a_World->GetLightManager().GetNumActiveDirectionalLights());

	LightingPass->SetPointLightData(a_World->GetLightManager().GetPointLightsData());
	LightingPass->SetNumPointLights(a_World->GetLightManager().GetNumActivePointLights());

	LightingPass->SetSpotLightData(a_World->GetLightManager().GetSpotLightsData());
	LightingPass->SetNumSpotLights(a_World->GetLightManager().GetNumActiveSpotLights());

	LightingPass->SetViewPosition(a_World->GetCameraManager().GetCurrentCamera()->Position);

	m_RenderEngine->ClearBuffers();
	m_RenderEngine->DrawPrimitive(m_QuadVertexBuffer, m_QuadIndexBuffer, LightingPass); //TODO
	m_RenderEngine->DisplayColorBuffer(0);
}
