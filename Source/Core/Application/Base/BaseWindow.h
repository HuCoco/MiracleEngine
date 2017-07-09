#pragma once
#include <Independent/Platform/PreCompileHeader.h>

NAMESPACE_MENGINE_BEGIN

class BaseWindow
{
public:
	BaseWindow();
	BaseWindow(_U32 a_Width, _U32 a_Height);
	virtual ~BaseWindow();

	virtual bool Initialze() = 0;
	virtual void SetTitle(const std::string& a_title);
	inline std::string GetTitle() const;
	inline _U32 GetXOrigin() const;
	inline _U32 GetYOrigin() const;
	inline _U32 GetWidth() const;
	inline _U32 GetHeight() const;
	inline bool IsMin() const;
	inline bool IsMax() const;
	inline _F32 GetAspectRatio() const;

	virtual void OnMove(_I32 a_x, _I32 a_y);
	virtual bool OnResize(_I32 a_width, _I32 a_height);
	virtual void OnMinimize();
	virtual void OnMaximize();
	virtual void OnDisplay() = 0;
	virtual void OnIdle() = 0;
	
protected:
	std::string m_Title;
	_U32 m_XOrigin;
	_U32 m_YOrigin;
	_U32 m_Width;
	_U32 m_Height;
	bool m_AllowResize;
	bool m_IsMinimized;
	bool m_IsMaximized;
};

inline std::string BaseWindow::GetTitle() const
{
	return m_Title;
}

inline _U32 BaseWindow::GetXOrigin() const
{
	return m_XOrigin;
}
inline _U32 BaseWindow::GetYOrigin() const
{
	return m_YOrigin;
}
inline _U32 BaseWindow::GetWidth() const
{
	return m_Width;
}
inline _U32 BaseWindow::GetHeight() const
{
	return m_Height;
}
inline bool BaseWindow::IsMin() const
{
	return m_IsMinimized;
}
inline bool BaseWindow::IsMax() const
{
	return m_IsMaximized;
}
inline _F32 BaseWindow::GetAspectRatio() const
{
	return _F32(m_Width) / _F32(m_Height);
}

NAMESPACE_MENGINE_END