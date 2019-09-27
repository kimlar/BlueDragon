#include "Window.h"
#include <stdio.h>
#include <assert.h>
#include "Renderer.h"

SDL_Window *window;
u32 window_width;
u32 window_height;
u8 window_mouse_focus;
u8 window_keyboard_focus;
u8 window_minimized;

void Window_Create(u32 width, u32 height, bool vsync)
{
	if (window)
		SDL_DestroyWindow(window);

	window = SDL_CreateWindow(
		"BlueDragon Editor",               // window title
		SDL_WINDOWPOS_UNDEFINED,           // initial x position
		SDL_WINDOWPOS_UNDEFINED,           // initial y position
		width,                             // width, in pixels
		height,                            // height, in pixels
		SDL_WINDOW_SHOWN|SDL_WINDOW_ALLOW_HIGHDPI // flags
	);

	if (!window)
	{
		printf("ERROR: Could not create window: %s\n", SDL_GetError());
		exit(1);
	}

	window_width = width;
	window_height = height;

	Renderer_Create(vsync);
}

void Window_Destroy(void)
{
	if (renderer)
		Renderer_Destroy();

	if(window)
		SDL_DestroyWindow(window);
}

void Window_Event(SDL_Event *e)
{
	assert(e->type == SDL_WINDOWEVENT);
	
	switch (e->window.event)
	{
		// Get new dimensions and repaint on window size change
		case SDL_WINDOWEVENT_SIZE_CHANGED:
		{
			window_width = e->window.data1;
			window_height = e->window.data2;
			Renderer_Force_Repaint();
		} break;

		// Repaint on exposure. Window was obsured and therefore needs to repaint.
		case SDL_WINDOWEVENT_EXPOSED:
		{
			Renderer_Force_Repaint();
		} break;

		// Mouse entered window
		case SDL_WINDOWEVENT_ENTER:
		{
			window_mouse_focus = 1;
		} break;

		// Mouse left window
		case SDL_WINDOWEVENT_LEAVE:
		{
			window_mouse_focus = 0;
		} break;

		// Window has keyboard focus
		case SDL_WINDOWEVENT_FOCUS_GAINED:
		{
			window_keyboard_focus = 1;
		} break;

		// Window has lost focus
		case SDL_WINDOWEVENT_FOCUS_LOST:
		{
			window_keyboard_focus = 0;
		} break;

		// Window minimized
		case SDL_WINDOWEVENT_MINIMIZED:
		{
			window_minimized = 1;
		} break;

		// Window maximized
		case SDL_WINDOWEVENT_MAXIMIZED:
		{
			window_minimized = 0;
		} break;

		// Window restored
		case SDL_WINDOWEVENT_RESTORED:
		{
			window_minimized = 0;
		} break;
	}
}

float Window_GetCurrentDPI(int monitor)
{
	float ddpi;
	float hdpi;
	float vdpi;
	if (SDL_GetDisplayDPI(monitor, &ddpi, &hdpi, &vdpi) != 0)
	{
		printf("ERROR: Could not get current DPI for monitor %d\n", monitor);
	}
	//printf("DPI: %f %f %f\n", ddpi, hdpi, vdpi);
	return ddpi;
}