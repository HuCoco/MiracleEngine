#pragma once
#include <Independent/Platform/PreCompileHeader.h>
#include <Independent/DataStructure/MSet.h>
#include <Core/Foundation/HObject.h>
#include <GamePlay/Component/Scene/MTransform.h>
NAMESPACE_MENGINE_BEGIN

class World;
class Component;
class SceneComponent;
class GameObject : public HObject
{
public:
	GameObject();
	~GameObject();

	virtual void Load();
	virtual void Update(_F32 a_DeltaTime);

	// Component managerment function
	void AppendComponent(const std::shared_ptr<Component>& a_Component);
	void AppendGameObject(const std::shared_ptr<GameObject>& a_GameObject);

	void AttachToGameObject(GameObject* a_GameObject);


	// World Update Funciton
	void AddUpdateFuncToUpdateManager(World* a_World);

	inline World* GetOwnedWorld()
	{
		return m_OwnedWorld;
	}

	inline void SetOwnedWorld(World* a_World)
	{
		m_OwnedWorld = a_World;
	}

	//Controll RootSceneComponent if it has 
	MTransform* GetTransform();

private:
	void AppendSceneComponent(const std::shared_ptr<SceneComponent>& a_Component);
	void AppendNonSceneComponent(const std::shared_ptr<Component>& a_Component);
private:
	bool m_IsHaveSceneComponent;
	SceneComponent* m_RootComponent;
	MSet<HName, std::shared_ptr<Component>> m_OwnedComponents;

	GameObject* m_Parent;
	MSet<HName, std::shared_ptr<GameObject>> m_ChildGameObjects;

	World* m_OwnedWorld;

	static const HName DefaultRootSceneComponentName;
};

NAMESPACE_MENGINE_END