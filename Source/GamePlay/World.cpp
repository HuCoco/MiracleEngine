#include "World.h"
#include <GamePlay/GameoObject/GameObject.h>
#include <Core/StringUtils/StringUtils.h>

Miracle::World::World()
	: HObject(HObject::HObjectType::GAME_WORLD)
	, m_IsCompeletedLoad(false)
{
}


Miracle::World::~World()
{
}


void Miracle::World::Update(_F32 a_DeltaTime)
{
	m_UpdateManager.DoUpdate(a_DeltaTime);
}

void Miracle::World::AddGameObject(const std::shared_ptr<GameObject>& a_GameOject)
{
	if (!a_GameOject->GetName().IsInitialzed())
	{
		a_GameOject->SetName(StringUtils::PointerToString(a_GameOject.get()));
	}
	m_GameObjectSet.Insert(a_GameOject->GetName(), a_GameOject);
	a_GameOject->SetOwnedWorld(this);
	a_GameOject->AddUpdateFuncToUpdateManager(this);
}

void Miracle::World::RemoveGameObject(const HName& a_Name)
{
	m_GameObjectSet.Remove(a_Name);
}

std::shared_ptr<Miracle::GameObject> Miracle::World::FindGameObject(const HName& a_Name)
{
	auto SetNode = m_GameObjectSet.Find(a_Name);
	if (SetNode == nullptr)
	{
		return nullptr;
	}
	
	return SetNode->Value;
}

void Miracle::World::Load()
{
	if (m_IsCompeletedLoad == true)
	{
		return;
	}
	MENGINE_SET_ITERATOR_BEGIN(m_GameObjectSet)
	{
		MENGINE_SET_GET_VALUE->Load();
	}
	MENGINE_SET_ITERATOR_END(m_GameObjectSet)
	m_IsCompeletedLoad = true;
}
