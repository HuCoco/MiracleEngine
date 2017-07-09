#include "MouseManager.h"



Miracle::MouseManager::MouseManager()
	: m_MouseLBClickPoisiton()
	, m_MouseRBClickPoisiton()
	, m_MouseLastPoisiton()
	, m_MousePoisiton()
	, m_RButtonState(MouseButtonState::Up)
	, m_LButtonState(MouseButtonState::Up)
	, m_RButtonLastState(MouseButtonState::Up)
	, m_LButtonLastState(MouseButtonState::Up)
{
}


Miracle::MouseManager::~MouseManager()
{
}

void Miracle::MouseManager::SetPosition(_U32 a_X, _U32 a_Y)
{
	m_MousePoisiton.x = a_X;
	m_MousePoisiton.y = a_Y;
}

void Miracle::MouseManager::SetRightButtonState(MouseButtonState a_State)
{
	m_RButtonState = a_State;
}

void Miracle::MouseManager::SetLeftButtonState(MouseButtonState a_State)
{
	m_LButtonState = a_State;
}
