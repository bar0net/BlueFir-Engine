#include "Chrono.h"

#include "SDL.h"

bluefir::base::Chrono::Chrono()
{
	SDL_Init(SDL_INIT_TIMER);
}

void bluefir::base::Chrono::Start()
{
	end_time = 0U;
	start_time = SDL_GetTicks();
}

unsigned int bluefir::base::Chrono::Pause()
{
	if (end_time == 0U)	return SDL_GetTicks() - start_time;
	else return end_time;
}

unsigned int bluefir::base::Chrono::Stop()
{
	if (end_time == 0U) end_time = SDL_GetTicks();
	return end_time;
}

bluefir::base::uChrono::uChrono()
{
	SDL_Init(SDL_INIT_TIMER);
	frequency = (unsigned long long int)SDL_GetPerformanceFrequency();
}

void bluefir::base::uChrono::Start()
{
	end_time = 0U;
	start_time = SDL_GetPerformanceCounter();
}

float bluefir::base::uChrono::Pause()
{
	if (end_time == 0U) return (float)(SDL_GetPerformanceCounter() - start_time) * 1000.0F / (float)frequency;
	else return end_time * 1000.0F / (float)frequency;
}

float bluefir::base::uChrono::Stop()
{
	if (end_time == 0U) end_time = SDL_GetPerformanceCounter() - start_time;
	return end_time * 1000.0F / (float)frequency;
}
