#pragma once
#include <Independent/Platform/PreCompileHeader.h>
#include <GamePlay/Component/Scene/CameraComponent.h>
#include <GamePlay/Base/Cameras.h>

NAMESPACE_MENGINE_BEGIN

class PerspectiveCameraComponent : public CameraComponent
{
public:
	PerspectiveCameraComponent();
	~PerspectiveCameraComponent();

	virtual void CameraUpdateFunc();

private:
	_F32 m_Fov;
	_F32 m_Aspect;
	_F32 m_NearPlane;
	_F32 m_FarPlane;

	_F32 m_MaxFov;
	_F32 m_MinFov;
};

NAMESPACE_MENGINE_END