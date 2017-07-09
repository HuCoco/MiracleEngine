#include "MotionController.h"
#include <GamePlay/GameoObject/GameObject.h>


Miracle::MotionController::MotionController()
	: m_MoveSpeed(3.0f)
{
	SetDefaulControllKey();
}


Miracle::MotionController::~MotionController()
{
}

void Miracle::MotionController::Handle(GameObject* a_GameObject, _F32 a_DeltaTime)
{
	MTransform* TargetTramsform = a_GameObject->GetTransform();
	if (TargetTramsform != nullptr)
	{
		auto KeyBoard = HIDSystem::Instance()->KeyBoardState;
		if (KeyBoard.IsFunctionKeyDown(m_ControllKey[FORWARD]))
		{
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
			TargetTramsform->Move(TargetTramsform->GetUpDirection() * m_MoveSpeed * a_DeltaTime);
		}

		if (KeyBoard.IsFunctionKeyDown(m_ControllKey[DROP]))
		{
			TargetTramsform->Move(-TargetTramsform->GetUpDirection() * m_MoveSpeed * a_DeltaTime);
		}
	}
}

void Miracle::MotionController::SetControllKeyMapping(const ControlKey& a_ControlKey, const KeyBoardManager::FunctionKey& a_FunctionKey)
{
	if (a_ControlKey >= 0 && a_ControlKey < NUM_CONTROL_KEY)
	{
		m_ControllKey[a_ControlKey] = a_FunctionKey;
	}
}

void Miracle::MotionController::SetDefaulControllKey()
{
	m_ControllKey[FORWARD] = KeyBoardManager::FunctionKey::KEY_W;
	m_ControllKey[BACKWARD] = KeyBoardManager::FunctionKey::KEY_S;
	m_ControllKey[LEFT] = KeyBoardManager::FunctionKey::KEY_A;
	m_ControllKey[RIGHT] = KeyBoardManager::FunctionKey::KEY_D;
	m_ControllKey[RISE] = KeyBoardManager::FunctionKey::KEY_SPACE;
	m_ControllKey[DROP] = KeyBoardManager::FunctionKey::KEY_LEFT_CONTROL;
}
