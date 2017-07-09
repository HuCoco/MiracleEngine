#pragma once
#include <Independent/Platform/PreCompileHeader.h>
#include <GamePlay/Component/Scene/LightComponent.h>
#include <GamePlay/Base/Lights.h>
NAMESPACE_MENGINE_BEGIN

class DirectionalLightComponent : public LightComponent
{
public:
	DirectionalLightComponent();
	DirectionalLightComponent(const DirectionalLight& a_DirectionalLight);
	~DirectionalLightComponent();

	virtual void LightUpdateFunc();

	
	
private:
	DirectionalLight m_DirectionalLight;
};

NAMESPACE_MENGINE_END