#pragma once
#include <Independent/Platform/PreCompileHeader.h>
#include <Independent/DataStructure/MSet.h>
NAMESPACE_MENGINE_BEGIN

class WorldContext;
class GameInstance
{
public:
	GameInstance();
	~GameInstance();

	virtual void Initialize();
	void HandleOneFrame(_F32 a_DetlaTime);

	void SetWorldContext(WorldContext* m_WorldContext);
	inline WorldContext* GetWorldContext()
	{
		return m_CurrentWorldContext;
	}
private:
	WorldContext* m_CurrentWorldContext;
};

NAMESPACE_MENGINE_END