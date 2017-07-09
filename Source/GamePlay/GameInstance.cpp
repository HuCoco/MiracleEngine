#include "GameInstance.h"
#include <GamePlay/WorldContext.h>
#include <GamePlay/World.h>

Miracle::GameInstance::GameInstance()
{
}


Miracle::GameInstance::~GameInstance()
{
}

void Miracle::GameInstance::HandleOneFrame(_F32 a_DetlaTime)
{
	if (m_CurrentWorldContext == nullptr)
	{
		MENGINE_ASSERT_MSG(false, "Maybe you forget to set world context.");
		return;
	}
	m_CurrentWorldContext->HandleOneFrame(a_DetlaTime);
}

void Miracle::GameInstance::SetWorldContext(WorldContext* m_WorldContext)
{
	m_CurrentWorldContext = m_WorldContext;
}

void Miracle::GameInstance::Initialize()
{
	if (m_CurrentWorldContext != nullptr)
	{
		m_CurrentWorldContext->Initialize();
	}
}
