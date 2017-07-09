#include "ControllerComponent.h"
#include <Core/Logging/MLog.h>


Miracle::ControllerComponent::ControllerComponent()
{
}


Miracle::ControllerComponent::~ControllerComponent()
{
}

void Miracle::ControllerComponent::UpdateFunc(_F32 a_DeltaTime)
{
	if (m_Controller != nullptr)
	{
		m_Controller->Handle(m_OwningGameObject, a_DeltaTime);
	}
	else
	{
		MENGINE_LOG_WARNING("This ControllComponent have no Contoller yet.");
	}
}

void Miracle::ControllerComponent::SetController(IController* a_Controller)
{
	m_Controller = a_Controller;
}

void Miracle::ControllerComponent::ClearController()
{
	m_Controller = nullptr;
}
