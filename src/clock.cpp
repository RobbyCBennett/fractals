#ifdef _WIN32
	#define WIN32_LEAN_AND_MEAN 1
	#include <Windows.h>
#else
	#include <time.h>
#endif

#include "clock.hpp"


namespace frac {


Clock::Clock()
{
#ifdef _WIN32
	LARGE_INTEGER frequency;
	QueryPerformanceFrequency(&frequency);
	period = 1.0 / (double) frequency.QuadPart;
#endif
}


double Clock::seconds()
{
#ifdef _WIN32
	LARGE_INTEGER count;
	QueryPerformanceCounter(&count);
	return (double) count.QuadPart * period;
#else
	timespec time;
	clock_gettime(CLOCK_MONOTONIC, &time);
	return (double) time.tv_sec + (double) time.tv_nsec * 0.000000001;
#endif
}


} // namespace frac
