#include <Independent/Timer/MTimer.h>

#if !defined(GTE_NEEDS_64_BIT_CLOCK)

Miracle::MTimer::MTimer()
{
}


Miracle::MTimer::~MTimer()
{

}

_I64 Miracle::MTimer::GetNanoseconds() const
{
	auto currentTime = std::chrono::high_resolution_clock::now();
	return std::chrono::duration_cast<std::chrono::nanoseconds>(
		currentTime - mInitialTime).count();
}

_I64 Miracle::MTimer::GetMicroseconds() const
{
	auto currentTime = std::chrono::high_resolution_clock::now();
	return std::chrono::duration_cast<std::chrono::microseconds>(
		currentTime - mInitialTime).count();
}

_I64 Miracle::MTimer::GetMilliseconds() const
{
	auto currentTime = std::chrono::high_resolution_clock::now();
	return std::chrono::duration_cast<std::chrono::milliseconds>(
		currentTime - mInitialTime).count();
}

double Miracle::MTimer::GetSeconds() const
{
	_I64 msecs = GetMilliseconds();
	return static_cast<double>(msecs) / 1000.0;
}

void Miracle::MTimer::Reset()
{
	mInitialTime = std::chrono::high_resolution_clock::now();
}


#else

#include <cmath>
#include <windows.h>

Miracle::MTimer::MTimer()
	:
	mFrequency(0),
	mInitialTicks(0),
	mInvFrequency(0.0)
{
	LARGE_INTEGER frequency = { 1 }, counter = { 0 };
	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&counter);
	mFrequency = static_cast<_I64>(frequency.QuadPart);
	mInitialTicks = static_cast<_I64>(counter.QuadPart);
	mInvFrequency = 1.0 / static_cast<double>(mFrequency);
}

_I64 Miracle::MTimer::GetNanoseconds() const
{
	_I64 ticks = GetTicks();
	double seconds = mInvFrequency * static_cast<double>(ticks);
	_I64 nanoseconds = static_cast<_I64>(ceil(1000000000.0 * seconds));
	return nanoseconds;
}

_I64 Miracle::MTimer::GetMicroseconds() const
{
	_I64 ticks = GetTicks();
	double seconds = mInvFrequency * static_cast<double>(ticks);
	_I64 microseconds = static_cast<_I64>(ceil(1000000.0 * seconds));
	return microseconds;
}

_I64 Miracle::MTimer::GetMilliseconds() const
{
	_I64 ticks = GetTicks();
	double seconds = mInvFrequency * static_cast<double>(ticks);
	_I64 milliseconds = static_cast<_I64>(ceil(1000.0 * seconds));
	return milliseconds;
}

double Miracle::MTimer::GetSeconds() const
{
	_I64 ticks = GetTicks();
	double seconds = mInvFrequency * static_cast<double>(ticks);
	return seconds;
}

void Miracle::MTimer::Reset()
{
	LARGE_INTEGER counter = { 0 };
	QueryPerformanceCounter(&counter);
	mInitialTicks = static_cast<_I64>(counter.QuadPart);
}

_I64 Miracle::MTimer::GetTicks() const
{
	LARGE_INTEGER counter = { 0 };
	QueryPerformanceCounter(&counter);
	return static_cast<_I64>(counter.QuadPart) - mInitialTicks;
}

#endif