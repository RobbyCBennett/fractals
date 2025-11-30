#pragma once


namespace frac {


// A monotonic clock
class Clock
{
public:
	Clock();

	double seconds();

private:
#ifdef _WIN32
	double period;
#endif
};


} // namespace frac
