#include "Chrono.h"

#include "SDL.h"

bluefir::base::Chrono::Chrono()
{
	SDL_Init(SDL_INIT_TIMER);
}

void bluefir::base::Chrono::Start()
{
	end_time_ = 0U;
	start_time_ = SDL_GetTicks();
}

unsigned int bluefir::base::Chrono::Pause() const
{
	if (end_time_ == 0U)	return SDL_GetTicks() - start_time_;
	else return end_time_;
}

unsigned int bluefir::base::Chrono::Stop()
{
	if (end_time_ == 0U) end_time_ = SDL_GetTicks();
	return end_time_;
}

bluefir::base::uChrono::uChrono()
{
	SDL_Init(SDL_INIT_TIMER);
	frequency = (unsigned long long int)SDL_GetPerformanceFrequency();
}

void bluefir::base::uChrono::Start()
{
	end_time_ = 0U;
	start_time_ = SDL_GetPerformanceCounter();
}

float bluefir::base::uChrono::Pause() const
{
	if (end_time_ == 0U) return (float)(SDL_GetPerformanceCounter() - start_time_) * 1000.0F / (float)frequency;
	else return end_time_ * 1000.0F / (float)frequency;
}

float bluefir::base::uChrono::Stop()
{
	if (end_time_ == 0U) end_time_ = SDL_GetPerformanceCounter() - start_time_;
	return end_time_ * 1000.0F / (float)frequency;
}
