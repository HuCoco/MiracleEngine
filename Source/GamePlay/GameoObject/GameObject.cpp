#include "GameObject.h"
#include <GamePlay/Component/Component.h>
#include <GamePlay/Component/Scene/SceneComponent.h>
#include <Core/StringUtils/StringUtils.h>


const Miracle::HName Miracle::GameObject::DefaultRootSceneComponentName = HName("DefaultRootSceneComponent");

Miracle::GameObject::GameObject()
	: HObject(HObject::HObjectType::GAME_OBJECT)
	, m_IsHaveSceneComponent(false)
	, m_RootComponent(nullptr)
	, m_Parent(nullptr)
{
}


Miracle::GameObject::~GameObject()
{
}

void Miracle::GameObject::Update(_F32 a_DeltaTime)
{
	return;
}

void Miracle::GameObject::Load()
{
	return;
}


void Miracle::GameObject::AppendComponent(const std::shared_ptr<Component>& a_Component)
{
	if (a_Component->IsSceneComponent())
	{
		AppendSceneComponent(std::static_pointer_cast<SceneComponent>(a_Component));
	}
	else
	{
		AppendNonSceneComponent(a_Component);
	}
}

void Miracle::GameObject::AppendGameObject(const std::shared_ptr<GameObject>& a_GameObject)
{
	if (!a_GameObject->GetName().IsInitialzed())
	{
		a_GameObject->SetName(StringUtils::PointerToString(a_GameObject.get()));
	}
	m_ChildGameObjects.Insert(a_GameObject->GetName(), a_GameObject);
	a_GameObject->AttachToGameObject(this);
}

void Miracle::GameObject::AttachToGameObject(GameObject* a_GameObject)
{
	m_Parent = a_GameObject;
}

void Miracle::GameObject::AppendSceneComponent(const std::shared_ptr<SceneComponent>& a_Component)
{
	if (m_IsHaveSceneComponent)
	{
		m_RootComponent->AppendComponent(a_Component);
		a_Component->AttachToComponent(m_RootComponent);
	}
	else
	{
		std::shared_ptr<SceneComponent> RootComponent = std::make_shared<SceneComponent>();
		RootComponent->SetName(DefaultRootSceneComponentName);
		RootComponent->AttachToGameObject(this);
		m_OwnedComponents.Insert(DefaultRootSceneComponentName, RootComponent);
		
		m_RootComponent = RootComponent.get();

		m_IsHaveSceneComponent = true;

		m_RootComponent->AppendComponent(a_Component);
		a_Component->AttachToComponent(m_RootComponent);
	}
}

void Miracle::GameObject::AppendNonSceneComponent(const std::shared_ptr<Component>& a_Component)
{
	if (!a_Component->GetName().IsInitialzed())
	{
		a_Component->SetName(StringUtils::PointerToString(a_Component.get()));
	}
	m_OwnedComponents.Insert(a_Component->GetName(), a_Component);
	a_Component->AttachToGameObject(this);
}

void Miracle::GameObject::AddUpdateFuncToUpdateManager(World* a_World)
{
	MENGINE_SET_ITERATOR_BEGIN(m_ChildGameObjects)
	{
		MENGINE_SET_GET_VALUE->AddUpdateFuncToUpdateManager(a_World);
	}
	MENGINE_SET_ITERATOR_END(m_ChildGameObjects)

	MENGINE_SET_ITERATOR_BEGIN(m_OwnedComponents)
	{
		MENGINE_SET_GET_VALUE->AddUpdateFuncToUpdateManager(a_World);
	}
	MENGINE_SET_ITERATOR_END(m_OwnedComponents)
}

Miracle::MTransform* Miracle::GameObject::GetTransform()
{
	if (m_IsHaveSceneComponent)
	{
		return m_RootComponent->GetTransfrom();
	}
	else
	{
		return nullptr;
	}
}

