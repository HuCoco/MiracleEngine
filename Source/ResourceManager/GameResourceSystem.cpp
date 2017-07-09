#include "GameResourceSystem.h"


Miracle::GameResourceSystem* Miracle::GameResourceSystem::s_pInstance = nullptr;

Miracle::GameResourceSystem::GameResourceSystem()
{
}


Miracle::GameResourceSystem::~GameResourceSystem()
{
}

void Miracle::GameResourceSystem::StartUp()
{
	s_pInstance = new GameResourceSystem;
}

void Miracle::GameResourceSystem::ShutDown()
{
	delete s_pInstance;
}

Miracle::GameResourceSystem* Miracle::GameResourceSystem::Instance()
{
	if (s_pInstance == nullptr)
	{
		MENGINE_ASSERT_MSG(false, "You must STARTUP GameResourceSystem fisrt.");
	}
	return s_pInstance;
}

Miracle::Model* Miracle::GameResourceSystem::GetModel(const HName& a_Name)
{
	return m_ModelManager.Load(a_Name);
}


Miracle::TexImage* Miracle::GameResourceSystem::GetImage(const HName& a_Name)
{
	return m_TextureManager.Load(a_Name);
}
