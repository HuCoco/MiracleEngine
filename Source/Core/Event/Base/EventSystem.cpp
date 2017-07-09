#include <Core/Event/Base/EventSystem.h>
#include <Core/Event/Base/IEventListener.h>
#include <Core/Event/Base/IEvent.h>

Miracle::EventSystem* Miracle::EventSystem::s_pInstance = nullptr;

Miracle::EventSystem::EventSystem()
{

}

Miracle::EventSystem::~EventSystem()
{

}


Miracle::EventSystem* Miracle::EventSystem::Instance()
{
	if (s_pInstance == nullptr)
	{
		MENGINE_ASSERT_MSG(false, "You must STARTUP EventSystem fisrt.");
	}
	return s_pInstance;
}

void Miracle::EventSystem::StartUp()
{
	s_pInstance = new EventSystem;
}

void Miracle::EventSystem::ShutDown()
{
	delete s_pInstance;
}

void Miracle::EventSystem::AddEventListener(EventListenerType a_ListenerType, IEventListener* a_Listener)
{
	if (a_Listener)
	{
		m_Listeners[a_ListenerType].emplace_back(a_Listener);
	}
	else
	{
		MENGINE_ASSERT_MSG(false, "Listener is null.");
	}
}

void Miracle::EventSystem::RemoveEventListener(EventListenerType a_ListenerType, IEventListener* a_Listener)
{
	auto& Listeners = m_Listeners[a_ListenerType];
	auto iter = Listeners.begin();
	for (; iter < Listeners.end(); ++iter)
	{
		if (*iter == a_Listener)
		{
			Listeners.erase(iter);
			break;
		}
		MENGINE_ASSERT_MSG(false, "no this listener.");
	}
}

void Miracle::EventSystem::ProcessEvent(const std::shared_ptr<IEvent>& a_Event)
{
	EventListenerType ListenerType = a_Event->GetEventListenerType();
	auto& Listeners = m_Listeners[ListenerType];
	for each (auto Listener in Listeners)
	{
		Listener->HandleEvent(a_Event);
	}
}
