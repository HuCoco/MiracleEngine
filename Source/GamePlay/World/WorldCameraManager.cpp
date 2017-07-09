#include "WorldCameraManager.h"



Miracle::WorldCameraManager::WorldCameraManager()
{
}


Miracle::WorldCameraManager::~WorldCameraManager()
{
}

void Miracle::WorldCameraManager::SwitchCamera(const HName& a_Name)
{
	MENGINE_SET_FIND(m_Cameras,a_Name);
	if (SetNode != nullptr)
	{
		m_CurrentCamera = SetNode->Value;
	}
	return;
}

void Miracle::WorldCameraManager::RemoveCamera(const HName& a_Name)
{
	m_Cameras.Remove(a_Name);
}

void Miracle::WorldCameraManager::AddCamera(const HName& a_Name, CameraSpaceMatrix* a_CameraMatrix)
{
	m_Cameras.Insert(a_Name, a_CameraMatrix);
}
