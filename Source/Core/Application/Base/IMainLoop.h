#pragma once
#include <Independent/Platform/PreCompileHeader.h>

NAMESPACE_MENGINE_BEGIN

class IMainLoop
{
public:
	IMainLoop();
	virtual ~IMainLoop();
	virtual void Run() = 0;
};

NAMESPACE_MENGINE_END