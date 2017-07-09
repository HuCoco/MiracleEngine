#include "FlashLightComponent.h"
#include <GamePlay/World.h>
#include <GamePlay/GameoObject/GameObject.h>
#include <GamePlay/World/WorldLightManager.h>


Miracle::FlashLightComponent::FlashLightComponent()
{
}


Miracle::FlashLightComponent::FlashLightComponent(const SpotLight& a_Light)
	: m_SpotLight(a_Light)
{

}

Miracle::FlashLightComponent::~FlashLightComponent()
{
}

void Miracle::FlashLightComponent::LightUpdateFunc()
{
	if (!IsEnable())
	{
		return;
	}
	m_SpotLight.Position = Vector4f(GetTransfomInWorldSpace().GetTranslate(), 0.0f);
	m_SpotLight.Direction = Vector4f(GetTransfomInWorldSpace().GetDirection(), 0.0f);
	m_OwningGameObject->GetOwnedWorld()->GetLightManager().AddSpotLight(m_SpotLight);
}
