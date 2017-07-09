#pragma once
#include <Independent/Platform/PreCompileHeader.h>
#include <GamePlay/Controller/MotionController.h>
#include <Core/Mathematics/GraphicsMathematics.h>
#include <InterfaceDevice/HIDSystem.h>

NAMESPACE_MENGINE_BEGIN

class CameraMotionController : public MotionController
{
public:
	CameraMotionController();
	~CameraMotionController();

	virtual void Handle(GameObject* a_GameObject, _F32 a_DeltaTime);

private:
	MouseManager::MouseButtonState m_LastLButtonState;
	MouseManager::MousePosition m_ClickLButtonMousePosition;
	Vector3f  m_ClickLButtonRotation;
};

NAMESPACE_MENGINE_END