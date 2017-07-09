#include "PrimitiveComponent.h"
#include <GamePlay/World.h>
#include <GamePlay/GameoObject/GameObject.h>

Miracle::PrimitiveComponent::PrimitiveComponent()
{
}


Miracle::PrimitiveComponent::~PrimitiveComponent()
{
}



void Miracle::PrimitiveComponent::AddUpdateFuncToUpdateManager(World* a_World)
{

	a_World->GetUpdateManager().AddRenderFunc(
		HName(m_OwningGameObject->GetName().GetString() + GetName().GetString()),
		std::bind(&PrimitiveComponent::RenderFunc,this));
}

