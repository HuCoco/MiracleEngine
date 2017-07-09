#pragma once
#include <Independent/Platform/PreCompileHeader.h>

#if defined(ME_MSWINDOWS_X32) || defined (ME_MSWINDOWS_X64)
#if _MSC_VER < 1900
#define GTE_NEEDS_64_BIT_CLOCK
#endif
#endif

#if !defined(GTE_NEEDS_64_BIT_CLOCK)
#include <chrono>
#endif

NAMESPACE_MENGINE_BEGIN

class MTimer
{
public:
	MTimer();
	~MTimer();

	_I64 GetNanoseconds() const;
	_I64 GetMicroseconds() const;
	_I64 GetMilliseconds() const;

	double GetSeconds() const;

	void Reset();
#if defined(GTE_NEEDS_64_BIT_CLOCK)
	// Internally use QueryPerformanceCounter.
	_I64 GetTicks() const;

	_I64 mFrequency;
	_I64 mInitialTicks;
	double mInvFrequency;
#else
	std::chrono::high_resolution_clock::time_point mInitialTime;
#endif
};

NAMESPACE_MENGINE_END