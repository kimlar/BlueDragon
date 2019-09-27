#include "Renderer.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Window.h"
#include <SDL_image.h>

SDL_Renderer *renderer;
bool use_vsync;

u32 CanvasXOffset = 0;
u32 CanvasYOffset = 0;

void Renderer_Create(bool vsync)
{
	assert(window);
	use_vsync = vsync;
	
	if (renderer)
		SDL_DestroyRenderer(renderer);

	u8 renderer_flags;
	if(vsync)
	{
		renderer_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE | SDL_RENDERER_PRESENTVSYNC;
	}
	else
	{
		renderer_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE;
	}

	renderer = SDL_CreateRenderer(window, -1, renderer_flags);
	if (!renderer)
	{
		printf("Renderer could not be created!\n");
		exit(1);
	}

	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
}

void Renderer_Destroy(void)
{
	if(renderer)
		SDL_DestroyRenderer(renderer);
}

void Renderer_Begin(void)
{
	assert(renderer);

	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
	SDL_RenderClear(renderer);
}

void Renderer_End(void)
{
	assert(renderer);

	SDL_RenderPresent(renderer); // Note: this will cause the main thread to sleep until vsync signal.
}

void Renderer_Force_Repaint(void)
{
	Renderer_End();
}