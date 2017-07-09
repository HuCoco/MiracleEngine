#include "DirectionalLightComponent.h"
#include <GamePlay/World.h>
#include <GamePlay/GameoObject/GameObject.h>
#include <GamePlay/World/WorldLightManager.h>

Miracle::DirectionalLightComponent::DirectionalLightComponent()
{
}

Miracle::DirectionalLightComponent::DirectionalLightComponent(const DirectionalLight& a_DirectionalLight)
	: m_DirectionalLight(a_DirectionalLight)
{

}

Miracle::DirectionalLightComponent::~DirectionalLightComponent()
{
}

void Miracle::DirectionalLightComponent::LightUpdateFunc()
{
	if (!IsEnable())
	{
		return;
	}
	m_OwningGameObject->GetOwnedWorld()->GetLightManager().AddDirectionalLight(m_DirectionalLight);
}
