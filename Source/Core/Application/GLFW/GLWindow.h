#pragma once
#include <Independent/Platform/PreCompileHeader.h>
#include <ThirdParty/GraphicsKit/OpenGLPreCompileHeader.h>
#include <Core/Application/Base/BaseWindow.h>

NAMESPACE_MENGINE_BEGIN

class GLWindow : public BaseWindow
{
public:
	GLWindow();
	GLWindow(_U32 a_Width, _U32 a_Height);
	virtual ~GLWindow();
	virtual bool Initialze() override;
	virtual void OnDisplay() override;
	virtual void OnIdle() override;
	virtual void SetTitle(std::string const& title) override;
	inline GLFWwindow* GetHandle() const;

private:
	GLFWwindow* m_hWnd;
};

inline GLFWwindow* GLWindow::GetHandle() const
{
	return m_hWnd;
}

NAMESPACE_MENGINE_END