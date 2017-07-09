#pragma once
#include <Independent/Platform/PreCompileHeader.h>
#include <Core/Application/Base/IMainLoop.h>
NAMESPACE_MENGINE_BEGIN

class Application;
class MSMainLoop : public IMainLoop
{
public:
	MSMainLoop(Application* a_Application);
	virtual ~MSMainLoop();
	virtual void Run() override;
private:
	Application* m_pApplication;
};

NAMESPACE_MENGINE_END