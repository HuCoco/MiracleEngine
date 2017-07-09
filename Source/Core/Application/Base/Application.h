#pragma once
#include <Independent/Platform/PreCompileHeader.h>
#include <Core/Application/Base/ApplicationSetting.h>

NAMESPACE_MENGINE_BEGIN


class BaseWindow;
class IMainLoop;
class Command;

class Application
{
public:
	Application();
	virtual ~Application();
	
	void Run();
	void ShutDown();
	virtual void Initialize();
	virtual void InitializeCommand();
	virtual void ConfigureCommandLine(char* a_cmd);
	//virtual void ConfigureCommandLine(int32_t argv, char* argc[]);
	
	static Application* Instance();

	inline BaseWindow* GetWindowHandle();
	inline ApplicationSetting& Setting();
protected:
	Command* m_Command;
	BaseWindow* m_pWindow;
	IMainLoop* m_pMainLoop;
	ApplicationSetting m_Setting;
private:
	volatile static Application* s_pInstance;
};

inline BaseWindow* Application::GetWindowHandle()
{
	return m_pWindow;
}

inline ApplicationSetting& Application::Setting()
{
	return m_Setting;
}

NAMESPACE_MENGINE_END