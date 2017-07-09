#pragma once
#include <Independent/Platform/PreCompileHeader.h>
#include <Core/Application/Base/BaseWindow.h>
#include <windows.h>

NAMESPACE_MENGINE_BEGIN

class MSWindow : public BaseWindow
{
public:
	MSWindow();
	MSWindow(_U32 a_Width, _U32 a_Height);
	virtual ~MSWindow();

	virtual bool Initialze() override;
	virtual void OnDisplay() override;
	virtual void OnIdle() override;
	virtual void SetTitle(std::string const& title) override;
	inline HWND GetHandle() const;

private:
	HWND m_hWnd;
	DWORD m_Style;
};

inline HWND MSWindow::GetHandle() const
{
	return m_hWnd;
}

NAMESPACE_MENGINE_END