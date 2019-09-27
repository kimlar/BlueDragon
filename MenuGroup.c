#include "MenuGroup.h"
//#include <SDL.h>
#include <assert.h>
#include "Window.h"
#include "Renderer.h"

void MenuGroup_Render(SDL_Rect rect)
{
	assert(renderer);

	SDL_SetRenderDrawColor(renderer, 0xE0, 0xE0, 0xE0, 0xFF);
	SDL_RenderFillRect(renderer, &rect);

	SDL_SetRenderDrawColor(renderer, 0x40, 0x40, 0x40, 0xFF);
	SDL_RenderDrawRect(renderer, &rect);
}