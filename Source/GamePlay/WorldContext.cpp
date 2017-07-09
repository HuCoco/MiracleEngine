#include "WorldContext.h"
#include <GamePlay/World.h>
#include <Core/StringUtils/StringUtils.h>

Miracle::WorldContext::WorldContext()
{
}


Miracle::WorldContext::~WorldContext()
{
}

void Miracle::WorldContext::HandleOneFrame(_F32 a_DeltaTime)
{
	if (m_CurrentWorld == nullptr)
	{
		MENGINE_ASSERT_MSG(false, "Maybe you forget to set world");
		return;
	}
	m_CurrentWorld->Update(a_DeltaTime);
}

void Miracle::WorldContext::AddWorld(const std::shared_ptr<World>& a_World)
{
	if (!a_World->GetName().IsInitialzed())
	{
		a_World->SetName(StringUtils::PointerToString(a_World.get()));
	}
	m_WorldSet.Insert(a_World->GetName(), a_World);
}

void Miracle::WorldContext::RemoveWorld(const HName& a_Name)
{
	m_WorldSet.Remove(a_Name);
}

std::shared_ptr<Miracle::World> Miracle::WorldContext::FindWorld(const HName& a_Name)
{
	auto SetNode = m_WorldSet.Find(a_Name);
	if (SetNode == nullptr)
	{
		return nullptr;
	}

	return SetNode->Value;
}

void Miracle::WorldContext::SetCurrentWorld(const HName& a_Name)
{
	auto world = FindWorld(a_Name).get();
	if (world != nullptr)
	{
		world->Load();
		m_CurrentWorld = world;
	}
}
