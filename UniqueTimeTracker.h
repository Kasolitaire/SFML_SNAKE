#pragma once
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
using namespace sf;
class UniqueTimeTracker
{
public:
	void StartClock();
	bool HasTimeElapsedOnce(const float seconds);
	bool HasTimeElapsed(const float seconds);
private:
	Clock* p_clock = 0;
	bool m_timeElapsed = false;
};

