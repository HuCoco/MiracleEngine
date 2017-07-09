#pragma once
#include <Independent/Platform/PreCompileHeader.h>
#include <Core/Application/Base/IMainLoop.h>

NAMESPACE_MENGINE_BEGIN

class Application;
class GLMainLoop : public IMainLoop
{
public:
	GLMainLoop(Application* a_Application);
	virtual ~GLMainLoop();
	virtual void Run() override;
private:
	Application* m_pApplication;
};

NAMESPACE_MENGINE_END