#include "CameraMotionController.h"
#include <GamePlay/GameoObject/GameObject.h>
#include <Core/Logging/MLog.h>
#include <Core/Logging/MLogToOutputWindow.h>
#include <Core/StringUtils/StringUtils.h>

Miracle::CameraMotionController::CameraMotionController()
	:m_LastLButtonState(MouseManager::MouseButtonState::Up)
	, MotionController()
{
}


Miracle::CameraMotionController::~CameraMotionController()
{
}

void Miracle::CameraMotionController::Handle(GameObject* a_GameObject, _F32 a_DeltaTime)
{
	MTransform* TargetTramsform = a_GameObject->GetTransform();
	if (TargetTramsform != nullptr)
	{
		auto KeyBoard = HIDSystem::Instance()->KeyBoardState;
		if (KeyBoard.IsFunctionKeyDown(m_ControllKey[FORWARD]))
		{
			auto d = TargetTramsform->GetDirection();
			TargetTramsform->Move(TargetTramsform->GetDirection() * m_MoveSpeed * a_DeltaTime);
		}

		if (KeyBoard.IsFunctionKeyDown(m_ControllKey[BACKWARD]))
		{
			TargetTramsform->Move(-TargetTramsform->GetDirection() * m_MoveSpeed * a_DeltaTime);
		}

		if (KeyBoard.IsFunctionKeyDown(m_ControllKey[LEFT]))
		{
			auto a = TargetTramsform->GetRightDirection();
			TargetTramsform->Move(-TargetTramsform->GetRightDirection() * m_MoveSpeed * a_DeltaTime);
		}

		if (KeyBoard.IsFunctionKeyDown(m_ControllKey[RIGHT]))
		{
			TargetTramsform->Move(TargetTramsform->GetRightDirection() * m_MoveSpeed * a_DeltaTime);
		}

		if (KeyBoard.IsFunctionKeyDown(m_ControllKey[RISE]))
		{
			auto a = TargetTramsform->GetRightDirection();
			TargetTramsform->Move(Vector3f(0.0f,1.0f,0.0f) * m_MoveSpeed * a_DeltaTime);
		}

		if (KeyBoard.IsFunctionKeyDown(m_ControllKey[DROP]))
		{
			TargetTramsform->Move(-Vector3f(0.0f, 1.0f, 0.0f) * m_MoveSpeed * a_DeltaTime);
		}

		auto Mouse = HIDSystem::Instance()->MouseState;
		if (Mouse.IsRightButtonDown())
		{	
			if (m_LastLButtonState == MouseManager::MouseButtonState::Up)
			{
				m_ClickLButtonMousePosition = Mouse.GetMousePosition();
				m_ClickLButtonRotation = TargetTramsform->GetRotation();
				m_LastLButtonState = MouseManager::MouseButtonState::Down;
			}
			_F32 xOffset = static_cast<_F32>(Mouse.GetMousePosition().x - m_ClickLButtonMousePosition.x)  * -0.05f;
			_F32 yOffset = static_cast<_F32>(Mouse.GetMousePosition().y - m_ClickLButtonMousePosition.y)  * 0.05f;
			TargetTramsform->SetRotation(Vector3f(
				MathUtils::Angle2Radian(yOffset) + m_ClickLButtonRotation[0],
				MathUtils::Angle2Radian(xOffset) + m_ClickLButtonRotation[1],
				m_ClickLButtonRotation[2]));
			
		}
		else if(m_LastLButtonState == MouseManager::MouseButtonState::Down && Mouse.IsRightButtonUp())
		{
			m_LastLButtonState = MouseManager::MouseButtonState::Up;
		}
	}
}
