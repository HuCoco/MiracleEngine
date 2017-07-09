#pragma once
#include <Independent/Platform/PreCompileHeader.h>
#include <Independent/DataStructure/MSet.h>
#include <Core/Foundation/HName.h>


NAMESPACE_MENGINE_BEGIN

class World;
class GameInstance;
class WorldContext
{
public:
	WorldContext();
	~WorldContext();
	virtual void Initialize() = 0;
	void HandleOneFrame(_F32 a_DeltaTime);

	inline void SetGameInstance(GameInstance* a_GameInstance)
	{
		m_OwningGameInstance = a_GameInstance;
	}

	inline GameInstance* GetGameInstance()
	{
		return m_OwningGameInstance;
	}

	inline World* GetCurrentWorld()
	{
		return m_CurrentWorld;
	}
	
	// World Managerment Function
	void AddWorld(const std::shared_ptr<World>& a_World);
	void RemoveWorld(const HName& a_Name);
	std::shared_ptr<World> FindWorld(const HName& a_Name);
	void SetCurrentWorld(const HName& a_Name);
private:
	MSet<HName, std::shared_ptr<World>> m_WorldSet;
	World* m_CurrentWorld;
	GameInstance* m_OwningGameInstance;
};

NAMESPACE_MENGINE_END