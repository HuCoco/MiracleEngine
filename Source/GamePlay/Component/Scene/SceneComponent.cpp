#include "SceneComponent.h"
#include <Core/StringUtils/StringUtils.h>
#include <GamePlay/GameoObject/GameObject.h>

Miracle::SceneComponent::SceneComponent()
	: Component(Component::ComponentType::SCENE_COMPONENT)
	, m_Parent(nullptr)
{
}


Miracle::SceneComponent::~SceneComponent()
{
}

Miracle::MTransform Miracle::SceneComponent::GetTransfomInWorldSpace()
{
	if (m_Parent == nullptr)
	{
		return m_Transform;
	}
	else
	{
		return m_Transform + m_Parent->GetTransfomInWorldSpace();
	}
}

Miracle::MTransform Miracle::SceneComponent::GetTransfomInModelSpace()
{
	return m_Transform;
}

void Miracle::SceneComponent::AppendComponent(const std::shared_ptr<SceneComponent>& a_SceneComponent)
{
	if (!a_SceneComponent->GetName().IsInitialzed())
	{
		a_SceneComponent->SetName(StringUtils::PointerToString(a_SceneComponent.get()));
	}
	m_OwnedComponets.Insert(a_SceneComponent->GetName(), a_SceneComponent);
	a_SceneComponent->AttachToComponent(this);
}

void Miracle::SceneComponent::AttachToComponent(SceneComponent* a_ParentSceneComponent)
{
	m_Parent = a_ParentSceneComponent;
	m_OwningGameObject = a_ParentSceneComponent->GetOwningGameObject();
}

void Miracle::SceneComponent::AddUpdateFuncToUpdateManager(World* a_World)
{
	MENGINE_SET_ITERATOR_BEGIN(m_OwnedComponets)
	{
		MENGINE_SET_GET_VALUE->AddUpdateFuncToUpdateManager(a_World);
	}
	MENGINE_SET_ITERATOR_END(m_OwnedComponets)
}
