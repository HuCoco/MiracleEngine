#include <Core/Event/Base/IEvent.h>
#include <Core/Event/Base/IEvent.h>

Miracle::IEvent::IEvent(EventType a_EventType, EventListenerType a_EventListenerType)
{
	Initialize(a_EventType, a_EventListenerType);
}

Miracle::IEvent::~IEvent()
{

}

void Miracle::IEvent::Initialize(EventType a_EventType, EventListenerType a_EventListenerType)
{
	_U16 Low = a_EventType;
	_U16 High = a_EventListenerType << 16;
	m_EventFlag = High | Low;
}




