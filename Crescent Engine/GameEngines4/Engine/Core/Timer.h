#ifndef TIMER_H
#define TIMER_H

#include <SDL.h>

class Timer
{
public:
	Timer(const Timer&) = delete;
	Timer(Timer&&) = delete;
	Timer& operator=(const Timer&) = delete;
	Timer& operator=(Timer&&) = delete;

	Timer();

	void Start();
	void UpdateFrameTick();
	float GetDeltaTime() const;
	unsigned int GetSleepTime(const unsigned int fps_);
	float GetCurrentTick() const;

private:
	unsigned int prevTicks;
	unsigned int currentTicks;
};
#endif

