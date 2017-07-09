#pragma once
#include <Independent/Platform/PreCompileHeader.h>

NAMESPACE_MENGINE_BEGIN

class MouseManager
{
public:

	struct MousePosition
	{
		_I32 x{ 0 };
		_I32 y{ 0 };

		MousePosition() = default;
		MousePosition(_I32 a_x, _I32 a_y)
			: x(a_x)
			, y(a_y)
		{
			
		}
	};

	enum class MouseButtonState
	{
		Up,
		Down
	};

	MouseManager();
	~MouseManager();

	void SetPosition(_U32 a_X, _U32 a_Y);
	void SetRightButtonState(MouseButtonState a_State);
	void SetLeftButtonState(MouseButtonState a_State);


	inline bool MouseManager::IsLeftButtonUp() const
	{
		return m_LButtonState == MouseButtonState::Up;
	}

	inline bool MouseManager::IsLeftButtonDown() const
	{
		return m_LButtonState == MouseButtonState::Down;
	}

	inline bool MouseManager::IsRightButtonUp() const
	{
		return m_RButtonState == MouseButtonState::Up;
	}

	inline bool MouseManager::IsRightButtonDown() const
	{
		return m_RButtonState == MouseButtonState::Down;
	}

	MousePosition GetMousePosition() const
	{
		return m_MousePoisiton;
	}

	MousePosition GetMousePositionOffset() const
	{
		return MousePosition(m_MousePoisiton.x - m_MouseLastPoisiton.x, m_MousePoisiton.y - m_MouseLastPoisiton.y);
	}

	MousePosition GetMousePositionOffsetSinceLastRightButtonClick() const
	{
		return MousePosition(m_MousePoisiton.x - m_MouseRBClickPoisiton.x, m_MousePoisiton.y - m_MouseRBClickPoisiton.y);
	}

	MousePosition GetMousePositionOffsetSinceLastLeftButtonClick() const
	{
		return MousePosition(m_MousePoisiton.x - m_MouseLBClickPoisiton.x, m_MousePoisiton.y - m_MouseLBClickPoisiton.y);
	}

private:
	MousePosition m_MousePoisiton;
	MousePosition m_MouseLastPoisiton;
	MousePosition m_MouseLBClickPoisiton;
	MousePosition m_MouseRBClickPoisiton;
	MouseButtonState m_LButtonState;
	MouseButtonState m_RButtonState;
	MouseButtonState m_LButtonLastState;
	MouseButtonState m_RButtonLastState;
};





NAMESPACE_MENGINE_END