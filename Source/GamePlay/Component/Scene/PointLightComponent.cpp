#include "PointLightComponent.h"
#include <GamePlay/World.h>
#include <GamePlay/GameoObject/GameObject.h>
#include <GamePlay/World/WorldLightManager.h>


Miracle::PointLightComponent::PointLightComponent()
{
}


Miracle::PointLightComponent::PointLightComponent(const PointLight& a_Light)
	: m_PointLight(a_Light)
{

}

Miracle::PointLightComponent::~PointLightComponent()
{
}

void Miracle::PointLightComponent::LightUpdateFunc()
{
	if (!IsEnable())
	{
		return;
	}
	m_PointLight.Position = Vector4f(GetTransfomInWorldSpace().GetTranslate(), 0.0f);
	m_OwningGameObject->GetOwnedWorld()->GetLightManager().AddPointLight(m_PointLight);
}
