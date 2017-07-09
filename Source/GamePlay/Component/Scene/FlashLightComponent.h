#pragma once
#include <Independent/Platform/PreCompileHeader.h>
#include <GamePlay/Component/Scene/LightComponent.h>
#include <GamePlay/Base/Lights.h>

NAMESPACE_MENGINE_BEGIN

class FlashLightComponent : public LightComponent
{
public:
	FlashLightComponent();
	FlashLightComponent(const SpotLight& a_Light);
	~FlashLightComponent();
	virtual void LightUpdateFunc();

private:
	SpotLight m_SpotLight;
};

NAMESPACE_MENGINE_END