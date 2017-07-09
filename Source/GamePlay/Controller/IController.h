#pragma once
#include <Independent/Platform/PreCompileHeader.h>

NAMESPACE_MENGINE_BEGIN

class GameObject;
class IController
{
public:
	IController();
	~IController();

	virtual void Handle(GameObject* a_GameObject,_F32 a_DeltaTime) = 0;
};

NAMESPACE_MENGINE_END