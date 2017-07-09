#include "CameraComponent.h"
#include <GamePlay/World.h>


Miracle::CameraComponent::CameraComponent()
{
}


Miracle::CameraComponent::~CameraComponent()
{
}

void Miracle::CameraComponent::CameraUpdateFunc()
{

}

void Miracle::CameraComponent::AddUpdateFuncToUpdateManager(World* a_World)
{
	a_World->GetUpdateManager().AddCameraUpdateFunc(GetName(), std::bind(&CameraComponent::CameraUpdateFunc, this));
	a_World->GetCameraManager().AddCamera(GetName(), &m_CameraSpaceMatrix);
}

