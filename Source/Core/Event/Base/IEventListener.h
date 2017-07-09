#pragma once
#include <Independent/Platform/PreCompileHeader.h>
#include <Core/Event/Base/IEvent.h>
#include <Core/Event/Base/EventSystem.h>
NAMESPACE_MENGINE_BEGIN

class IEventListener
{
protected:
	IEventListener();
public:
	~IEventListener();

	void Unregister(EventListenerType a_ListenerType);
	void Register(EventListenerType a_ListenerType);

	virtual bool HandleEvent(const std::shared_ptr<IEvent>& pEvent) = 0;

};

NAMESPACE_MENGINE_END