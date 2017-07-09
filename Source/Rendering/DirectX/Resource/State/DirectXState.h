#pragma once
#include <Independent/Platform/PreCompileHeader.h>
#include <Rendering/DirectX/Resource/DirectXResourceChild.h>
#include <Rendering/Base/Resource/State/State.h>

NAMESPACE_MENGINE_BEGIN

class DirectXState : public DirectXResourceChild
{
protected:
	DirectXState(State* a_State);
public:
	virtual ~DirectXState();
};

NAMESPACE_MENGINE_END