#pragma once
#include <Independent/Platform/PreCompileHeader.h>

NAMESPACE_MENGINE_BEGIN

class IEventListener;
class IEvent;
enum EventListenerType
{
	INPUT_LISTENER,
	CUSTOM_LISTENER,
	NUM_EVENT_LISTENER
};




class EventSystem
{
public:
	EventSystem();
	~EventSystem();

	static void StartUp();
	static void ShutDown();

	static EventSystem* Instance();
	void ProcessEvent(const std::shared_ptr<IEvent>& a_Listener);
	void AddEventListener(EventListenerType a_ListenerType,IEventListener* a_Listener);
	void RemoveEventListener(EventListenerType a_ListenerType, IEventListener* a_Listener);
private:
	static EventSystem* s_pInstance;

	std::vector<IEventListener*> m_Listeners[NUM_EVENT_LISTENER];
};

NAMESPACE_MENGINE_END