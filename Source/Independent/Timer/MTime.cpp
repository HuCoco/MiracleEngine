#include <Independent/Timer/MTime.h>



Miracle::MTime::MTime()
	: m_TotalTime(0.0)
	, m_CurrentTime(0.0)
	, m_LastTime(0.0)
	, m_IntervalTime(0.0)
	, m_InitailTime(m_Timer.GetSeconds())
{
	
}


Miracle::MTime::~MTime()
{
}

void Miracle::MTime::Tick()
{
	auto time = m_Timer.GetSeconds();
	m_TotalTime = time - m_InitailTime;
	m_CurrentTime = time;
	m_IntervalTime = m_CurrentTime - m_LastTime;
	if (m_IntervalTime > 100.0f)
	{
		m_IntervalTime = 0.0f;
	}
	m_LastTime = m_CurrentTime;
}
