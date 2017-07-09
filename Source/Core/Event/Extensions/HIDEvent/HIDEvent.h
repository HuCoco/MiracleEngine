#pragma once
#include <Core/Event/Base/IEvent.h>
#include <InterfaceDevice/HIDSystem.h>
NAMESPACE_MENGINE_BEGIN

class HIDEvent : public IEvent
{
public:
	HIDEvent(HIDSystem* a_Input);
	~HIDEvent();

	const HIDSystem* InputInfo;
};

NAMESPACE_MENGINE_END