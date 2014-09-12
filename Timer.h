#include <SDL.h>

class Timer
{
public:
	Timer();

	void start();
	Uint32 getElapsedTime();

private:
	Uint32 m_startTime;
};