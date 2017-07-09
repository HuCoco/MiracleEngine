#pragma once
#include <Independent/Platform/PreCompileHeader.h>
#include <Independent/DataStructure/MSet.h>
#include <GamePlay/World/WorldUpdateManager.h>
#include <GamePlay/World/WorldLightManager.h>
#include <GamePlay/World/WorldCameraManager.h>
#include <Core/Foundation/HObject.h>
#include <Core/Foundation/HName.h>

NAMESPACE_MENGINE_BEGIN

class GameObject;
class World : public HObject
{
public:
	World();
	~World();
	virtual void Load();
	virtual void Update(_F32 a_DeltaTime);

	// GameObject Managerment Function
	void AddGameObject(const std::shared_ptr<GameObject>& a_GameOject);
	void RemoveGameObject(const HName& a_Name);
	std::shared_ptr<GameObject> FindGameObject(const HName& a_Name);

	//Update Function mananger
	inline WorldUpdateManager& GetUpdateManager()
	{
		return m_UpdateManager;
	}

	inline WorldLightManager& GetLightManager()
	{
		return m_LightManager;
	}

	inline WorldCameraManager& GetCameraManager()
	{
		return m_CameraManager;
	}

private:
	MSet<HName, std::shared_ptr<GameObject>> m_GameObjectSet;
	WorldUpdateManager m_UpdateManager;
	WorldLightManager m_LightManager;
	WorldCameraManager m_CameraManager;
	bool m_IsCompeletedLoad;
};

NAMESPACE_MENGINE_END
