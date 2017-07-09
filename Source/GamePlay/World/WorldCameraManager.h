#pragma once
#include <Independent/Platform/PreCompileHeader.h>
#include <Independent/DataStructure/MSet.h>
#include <Core/Foundation/HName.h>
#include <GamePlay/Base/Cameras.h>
NAMESPACE_MENGINE_BEGIN

class WorldCameraManager
{
public:
	WorldCameraManager();
	~WorldCameraManager();

	void AddCamera(const HName& a_Name,CameraSpaceMatrix* a_CameraMatrix);
	void RemoveCamera(const HName& a_Name);

	void SwitchCamera(const HName& a_Name);

	inline const CameraSpaceMatrix* GetCurrentCamera() const
	{
		return m_CurrentCamera;
	}
private:
	CameraSpaceMatrix* m_CurrentCamera;
	MSet<HName, CameraSpaceMatrix*> m_Cameras;
};

NAMESPACE_MENGINE_END