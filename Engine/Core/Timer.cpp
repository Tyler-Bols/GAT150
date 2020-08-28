#include "pch.h"
#include "Timer.h"
using namespace nc;

void nc::Timer::Reset()
{
    m_timePoint = clock::now();
}

Timer::clock::rep nc::Timer::ElapsedTicks()
{
    clock::duration duration = (clock::now() - m_timePoint);
    return duration.count();
}

Timer::clock::rep nc::Timer::TicksPerSecond()
{
    return clock_duration::period::den;
}

double nc::Timer::ElaspedSeconds()
{
    return ElapsedTicks() / static_cast<double>(TicksPerSecond());
}

void nc::FrameTimer::Tick()
{
    m_dt = static_cast<float>(ElaspedSeconds());
    m_timePoint = clock::now();
}


