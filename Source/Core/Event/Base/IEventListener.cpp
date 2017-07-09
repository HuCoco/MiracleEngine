#include <Core/Event/Base/IEventListener.h>


Miracle::IEventListener::IEventListener()
{

}

Miracle::IEventListener::~IEventListener()
{

}

void Miracle::IEventListener::Unregister(EventListenerType a_ListenerType)
{
	EventSystem::Instance()->RemoveEventListener(a_ListenerType,this);
}

void Miracle::IEventListener::Register(EventListenerType a_ListenerType)
{
	EventSystem::Instance()->AddEventListener(a_ListenerType, this);
}
