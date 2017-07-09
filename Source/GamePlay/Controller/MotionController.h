#pragma once
#include <Independent/Platform/PreCompileHeader.h>
#include <GamePlay/Controller/IController.h>
#include <InterfaceDevice/HIDSystem.h>

NAMESPACE_MENGINE_BEGIN

class MotionController : public IController
{
public:

	enum ControlKey
	{
		FORWARD,
		BACKWARD,
		LEFT,
		RIGHT,
		RISE,
		DROP,
		NUM_CONTROL_KEY
	};


	MotionController();
	~MotionController();

	virtual void Handle(GameObject* a_GameObject, _F32 a_DeltaTime);
	void SetDefaulControllKey();
	void SetControllKeyMapping(const ControlKey& a_ControlKey, const KeyBoardManager::FunctionKey& a_FunctionKey);

	inline void SetMoveSpeed(_F32 a_MoveSpeed)
	{
		m_MoveSpeed = a_MoveSpeed;
	}

protected:

protected:
	KeyBoardManager::FunctionKey m_ControllKey[ControlKey::NUM_CONTROL_KEY];
	_F32 m_MoveSpeed;
};

NAMESPACE_MENGINE_END