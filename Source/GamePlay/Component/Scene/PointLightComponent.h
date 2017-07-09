#pragma once
#include <Independent/Platform/PreCompileHeader.h>
#include <GamePlay/Component/Scene/LightComponent.h>
#include <GamePlay/Base/Lights.h>

NAMESPACE_MENGINE_BEGIN

class PointLightComponent : public LightComponent
{
public:
	PointLightComponent();
	PointLightComponent(const PointLight& a_Light);
	~PointLightComponent();
	virtual void LightUpdateFunc();

private:
	PointLight m_PointLight;
};

NAMESPACE_MENGINE_END