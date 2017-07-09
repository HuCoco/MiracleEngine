#include "Component.h"
#include <GamePlay/World.h>


Miracle::Component::Component(ComponentType a_ComponentType)
	: HObject(HObject::HObjectType::GAME_COMPONENT)
	, m_ComponentType(a_ComponentType)
	, m_OwningGameObject(nullptr)
{
}

Miracle::Component::Component()
	: HObject(HObject::HObjectType::GAME_COMPONENT)
	, m_ComponentType(ComponentType::UNKOWN)
	, m_OwningGameObject(nullptr)
{

}

Miracle::Component::~Component()
{
}

void Miracle::Component::UpdateFunc(_F32 a_DeltaTime)
{

}

void Miracle::Component::AttachToGameObject(GameObject* m_GameObject)
{
	m_OwningGameObject = m_GameObject;
}

void Miracle::Component::AddUpdateFuncToUpdateManager(World* a_World)
{
	a_World->GetUpdateManager().AddCommonGameUpdateFunc(GetName(), std::bind(&Component::UpdateFunc,this, std::placeholders::_1));
}

