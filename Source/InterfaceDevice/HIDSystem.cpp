#include <InterfaceDevice/HIDSystem.h>

Miracle::HIDSystem* Miracle::HIDSystem::s_pInstance = nullptr;

Miracle::HIDSystem::HIDSystem()
{

}


Miracle::HIDSystem::~HIDSystem()
{
}

void Miracle::HIDSystem::StartUp()
{
	s_pInstance = new HIDSystem();
}

void Miracle::HIDSystem::ShutDown()
{
	delete s_pInstance;
}

Miracle::HIDSystem* Miracle::HIDSystem::Instance()
{
	if (s_pInstance == nullptr)
	{
		MENGINE_ASSERT_MSG(false, "You must STARTUP HIDSystem fisrt.");
	}
	return s_pInstance;
}

