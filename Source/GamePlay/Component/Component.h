#pragma once
#include <Independent/Platform/PreCompileHeader.h>
#include <Core/Foundation/HObject.h>

NAMESPACE_MENGINE_BEGIN

class GameObject;
class SceneComponent;
class World;
class Component : public HObject
{
public:
	// Component Type Function 
	enum ComponentType
	{
		UNKOWN,
		SCENE_COMPONENT = 0x01,
		FUNCTIONAL_COMPONENT = 0x02,
		INFO_COMPONENT = 0x04
	};


	Component();
	Component(ComponentType a_ComponentType);
	~Component();
	
	virtual void UpdateFunc(_F32 a_DeltaTime);
	virtual void AttachToGameObject(GameObject* m_GameObject);

	inline GameObject* GetOwningGameObject()
	{
		return m_OwningGameObject;
	}

	virtual void AddUpdateFuncToUpdateManager(World* a_World);

	inline ComponentType GetComponentType() const
	{
		return m_ComponentType;
	}

	inline bool IsSceneComponent() const
	{
		return (m_ComponentType & ComponentType::SCENE_COMPONENT) == ComponentType::SCENE_COMPONENT;
	}

	inline bool IsFunctionalComponent() const
	{
		return (m_ComponentType & ComponentType::FUNCTIONAL_COMPONENT) == ComponentType::FUNCTIONAL_COMPONENT;
	}

	inline bool IsInfoComponent() const
	{
		return (m_ComponentType & ComponentType::INFO_COMPONENT) == ComponentType::INFO_COMPONENT;
	}
protected:


protected:
	GameObject* m_OwningGameObject;
	ComponentType m_ComponentType;
};

NAMESPACE_MENGINE_END