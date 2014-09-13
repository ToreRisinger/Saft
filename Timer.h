class Timer
{
public:
	Timer();

	void start();
	Uint32 getElapsedTime();

private:
	Uint32 m_startTime;
};

Timer::Timer()
{
	m_startTime = 0;
}

void Timer::start()
{
	m_startTime = SDL_GetTicks();
}

Uint32 Timer::getElapsedTime()
{
	return SDL_GetTicks() - m_startTime;
}