#include "MenuBar.h"
#include <SDL.h>
#include <assert.h>
#include "Window.h"
#include "Renderer.h"

void MenuBar_Render(void)
{
	assert(renderer);

	SDL_SetRenderDrawColor(renderer, 0xCC, 0xCC, 0xCC, 0xFF);
	SDL_Rect rect;
	rect.x = 0;
	rect.y = 0;
	rect.w = window_width;
	rect.h = CanvasYOffset;
	SDL_RenderFillRect(renderer, &rect);
}