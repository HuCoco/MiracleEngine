#pragma once
#include <Independent/Platform/PreCompileHeader.h>
#include <GamePlay/Component/Scene/SceneComponent.h>

NAMESPACE_MENGINE_BEGIN
class World;
class LightComponent : public SceneComponent
{
public:
	LightComponent();
	~LightComponent();

	virtual void LightUpdateFunc();
	virtual void AddUpdateFuncToUpdateManager(World* a_World);

	inline void Enable()
	{
		m_Enable = true;
	}

	inline void Disable()
	{
		m_Enable = false;
	}

	inline bool IsEnable()
	{
		return m_Enable;
	}

private:
	bool m_Enable;
};

NAMESPACE_MENGINE_END