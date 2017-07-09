#include "MeshComponent.h"
#include <Rendering/RenderSystem/RenderSystem.h>
#include <Rendering/VisualEffect/GeometryPassEffect.h>
#include <Rendering/VisualEffect/GeometryPassWithNormalEffect.h>
#include <GamePlay/World.h>
#include <GamePlay/GameoObject/GameObject.h>
#include <Core/Engine/MEngine.h>


Miracle::MeshComponent::MeshComponent(Mesh* a_Mesh)
	: m_Mesh(a_Mesh)
{
	SetName(a_Mesh->GetMeshName());
}


Miracle::MeshComponent::~MeshComponent()
{

}

void Miracle::MeshComponent::RenderFunc()
{

	if (m_Mesh->GetNormalTexture() == nullptr)
	{
		auto GeometryEffect =
			std::static_pointer_cast<GeometryPassEffect>(MEngine::Instance()->GetRenderSystem()->GetVisualEffectManager().GetEffect("GeometryPassEffect"));

		AffineMatrixs mat;
		mat.Model = GetTransfomInWorldSpace().ToMartix4f();
		mat.InverseModel = mat.Model.Inverse().Transpose();
		mat.View = m_OwningGameObject->GetOwnedWorld()->GetCameraManager().GetCurrentCamera()->ViewSpaceMatrix;
		mat.Projection = m_OwningGameObject->GetOwnedWorld()->GetCameraManager().GetCurrentCamera()->ProjectionMatrix;


		GeometryEffect->UpdateTextures(m_Mesh->GetDiffuseTextrue(), m_Mesh->GetSpecularTexture());
		GeometryEffect->UpdateAffineMatrixs(&mat);
		MEngine::Instance()->GetRenderSystem()->GetRenderEngine()->DrawPrimitive(m_Mesh->GetVertexBuffer(), m_Mesh->GetIndexBuffer(), GeometryEffect);
	}
	else if (m_Mesh->GetNormalTexture() != nullptr)
	{
		auto GeometryEffect =
			std::static_pointer_cast<GeometryPassWithNormalEffect>(MEngine::Instance()->GetRenderSystem()->GetVisualEffectManager().GetEffect("GeometryPassWithNormal"));

		AffineMatrixs mat;
		mat.Model = GetTransfomInWorldSpace().ToMartix4f();
		mat.InverseModel = mat.Model.Inverse().Transpose();
		mat.View = m_OwningGameObject->GetOwnedWorld()->GetCameraManager().GetCurrentCamera()->ViewSpaceMatrix;
		mat.Projection = m_OwningGameObject->GetOwnedWorld()->GetCameraManager().GetCurrentCamera()->ProjectionMatrix;


		GeometryEffect->UpdateTextures(m_Mesh->GetDiffuseTextrue(), m_Mesh->GetSpecularTexture());
		GeometryEffect->UpdateNormalTexture(m_Mesh->GetNormalTexture());
		GeometryEffect->UpdateAffineMatrixs(&mat);
		MEngine::Instance()->GetRenderSystem()->GetRenderEngine()->DrawPrimitive(m_Mesh->GetVertexBuffer(), m_Mesh->GetIndexBuffer(), GeometryEffect);
	}

}
