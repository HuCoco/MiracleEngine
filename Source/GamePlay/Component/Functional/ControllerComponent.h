#pragma once
#include <Independent/Platform/PreCompileHeader.h>
#include <GamePlay/Component/Functional/FunctionalComponent.h>
#include <GamePlay/Controller/IController.h>

NAMESPACE_MENGINE_BEGIN

class ControllerComponent : public FunctionalComponent
{
public:
	ControllerComponent();
	~ControllerComponent();

	virtual void UpdateFunc(_F32 a_DeltaTime);

	// IController Function
	void SetController(IController* a_Controller);
	void ClearController();
private:
	IController* m_Controller;
};

NAMESPACE_MENGINE_END