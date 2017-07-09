#pragma once
#include <Independent/Platform/PreCompileHeader.h>
#include <GamePlay/Component/Scene/SceneComponent.h>
#include <GamePlay/Base/Cameras.h>
NAMESPACE_MENGINE_BEGIN
class World;
class CameraComponent : public SceneComponent
{
public:
	CameraComponent();
	~CameraComponent();

	virtual void CameraUpdateFunc();
	virtual void AddUpdateFuncToUpdateManager(World* a_World);


protected:
	CameraSpaceMatrix m_CameraSpaceMatrix;
};

NAMESPACE_MENGINE_END