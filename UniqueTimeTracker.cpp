#include "UniqueTimeTracker.h"

void UniqueTimeTracker::StartClock()
{
	m_timeElapsed = false;
	if(p_clock == 0)
		p_clock = new Clock();
	else 
	{
		delete p_clock;
		p_clock = new Clock();
	}
}

bool UniqueTimeTracker::HasTimeElapsedOnce(const float seconds)
{
	if (p_clock == 0) return false;
	if (p_clock->getElapsedTime().asSeconds() >= seconds && m_timeElapsed == false)
	{
		m_timeElapsed = true;
		return true;
	}
	else return false;
}

bool UniqueTimeTracker::HasTimeElapsed(const float seconds)
{
	if (p_clock == 0) return false;
	if (p_clock->getElapsedTime().asSeconds() >= seconds)
	{
		return true;
	}
	else return false;
}
