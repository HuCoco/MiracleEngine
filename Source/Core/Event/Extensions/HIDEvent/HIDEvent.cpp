#include <Core/Event/Extensions/HIDEvent/HIDEvent.h>


Miracle::HIDEvent::HIDEvent(HIDSystem* a_Input)
	: IEvent(HID_EVENT,INPUT_LISTENER)
	, InputInfo(a_Input)
{

}

Miracle::HIDEvent::~HIDEvent()
{

}
