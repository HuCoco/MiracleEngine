#include "LightComponent.h"
#include <GamePlay/World.h>


Miracle::LightComponent::LightComponent()
{
}


Miracle::LightComponent::~LightComponent()
{
}

void Miracle::LightComponent::LightUpdateFunc()
{

}

void Miracle::LightComponent::AddUpdateFuncToUpdateManager(World* a_World)
{
	a_World->GetUpdateManager().AddLightUpdateFunc(GetName(), std::bind(&LightComponent::LightUpdateFunc, this));
}
