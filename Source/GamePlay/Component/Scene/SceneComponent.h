#pragma once
#include <Independent/Platform/PreCompileHeader.h>
#include <Independent/DataStructure/MSet.h>
#include <GamePlay/Component/Component.h>
#include <GamePlay/Component/Scene/MTransform.h>

NAMESPACE_MENGINE_BEGIN

class SceneComponent : public Component
{
public:
	SceneComponent();
	~SceneComponent();

	// Transfom Function
	MTransform GetTransfomInWorldSpace();
	MTransform GetTransfomInModelSpace();

	// Component Managerment Function
	void AppendComponent(const std::shared_ptr<SceneComponent>& a_SceneComponent);
	void AttachToComponent(SceneComponent* a_ParentSceneComponent);
	virtual void AddUpdateFuncToUpdateManager(World* a_World);


	inline MTransform* GetTransfrom()
	{
		return &m_Transform;
	}

protected:
	MSet<HName, std::shared_ptr<Component>> m_OwnedComponets;
	SceneComponent* m_Parent;
	MTransform m_Transform;
};

NAMESPACE_MENGINE_END