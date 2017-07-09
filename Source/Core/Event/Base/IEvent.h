#pragma once
#include <Independent/Platform/PreCompileHeader.h>
#include <Core/Event/Base/EventSystem.h>

NAMESPACE_MENGINE_BEGIN

enum EventType
{
	SYSTEM_EVENT,
		SYSTEM_RESIZE,
		SYSTEM_CLOSE,
	HID_EVENT,
		HID_LBUTTON_DOWN,
		HID_LBUTTON_UP,
		HID_MBUTTON_DOWN,
		HID_MBUTTON_UP,
		HID_RBUTTON_DOWN,
		HID_RBUTTON_UP,
		HID_MOUSE_LEAVE,
		HID_MOUSE_WHEEL,
		HID_MOUSE_MOVE,
		HID_KEYBOARD_KEYDOWN,
		HID_KEYBOARD_KEYUP,
		HID_KEYBOARD_CHAR,
	NUM_EVENT
};

class IEvent
{
public:
	IEvent(EventType a_EventType, EventListenerType a_EventListenerType);
	~IEvent();
	inline EventType GetEventType();
	inline EventListenerType GetEventListenerType();

private:
	void Initialize(EventType a_EventType, EventListenerType a_EventListenerType);
private:
	_U32 m_EventFlag;
};

inline Miracle::EventType Miracle::IEvent::GetEventType()
{
	return EventType(m_EventFlag & 0xffff);
}

inline Miracle::EventListenerType Miracle::IEvent::GetEventListenerType()
{
	return EventListenerType((m_EventFlag & 0xffff0000) >> 16);
}


NAMESPACE_MENGINE_END