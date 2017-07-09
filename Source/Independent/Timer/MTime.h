#pragma once
#include <Independent/Platform/PreCompileHeader.h>
#include <Independent/Timer/MTimer.h>

NAMESPACE_MENGINE_BEGIN

class MTime
{
public:
	MTime();
	~MTime();

	inline _D64 GetTotalTime() const;
	inline _D64 GetCurrTime() const;
	inline _D64 GetIntervalTime() const;

	void Tick();
private:
	MTimer m_Timer;
	_D64 m_InitailTime;
	_D64 m_TotalTime;
	_D64 m_CurrentTime;
	_D64 m_LastTime;
	_D64 m_IntervalTime;
};

inline _D64 MTime::GetTotalTime() const
{
	return m_TotalTime;
}

inline _D64 MTime::GetCurrTime() const
{
	return m_CurrentTime;
}

inline _D64 MTime::GetIntervalTime() const
{
	return m_IntervalTime;
}

NAMESPACE_MENGINE_END