#include "Timer.h"
#include <stdbool.h>
#include <SDL.h>
#include "DataTypes.h"
#include "Window.h"
#include "Renderer.h"

double dt; // in seconds
double delta_time; // in seconds

u64 timer_prev;
u64 timer_curr;

void Timer_Initialize()
{
	timer_prev = 0;
	timer_curr = SDL_GetPerformanceCounter();
	delta_time = 0;
}

void Timer_Update()
{
	timer_prev = timer_curr;
	timer_curr = SDL_GetPerformanceCounter();
	delta_time = (double)((timer_curr - timer_prev) * 1000 / (double)SDL_GetPerformanceFrequency()) * 0.001;

	// TODO(kim): Should I move this to another place?
	if (window_minimized || !use_vsync)
	{
		dt = delta_time;
	}
	else
	{
		dt = (1.0 / 60.0);
	}
}
