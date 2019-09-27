#include "EditorVScroll.h"
#include <SDL.h>
#include <assert.h>
#include "Window.h"
#include "Renderer.h"
#include "Camera.h"
#include "Tile.h"
#include "World.h"
#include "Mouse.h"

u8 EditorVScroll_Up = 0;
u8 EditorVScroll_Down = 0;

u32 EditorVScroll_Handle_Lenght;

void EditorVScroll_Create(void)
{
	//EditorVScroll_Handle_Lenght = 100;
	u32 scrollbarHeight = Camera_Height - 16 - 16 - 30 - 1 - 4 - 1;
	EditorVScroll_Handle_Lenght = ((Camera_Height * scrollbarHeight) / (WorldHeight*tile_size));
	//EditorVScroll_Handle_Lenght = scrollbarHeight;
}

void EditorVScroll_Event(void)
{
	EditorVScroll_Up = 0;
	EditorVScroll_Down = 0;
	if (mouse_button_left)
	{
		// Scroll up button
		if (mouse_x > (CanvasXOffset + window_width - 400 - 16 + 1 - 16) &&
			mouse_x < (CanvasXOffset + window_width - 400 - 16 + 1 - 16 + 16) &&
			mouse_y > CanvasYOffset &&
			mouse_y < (CanvasYOffset + 16))
		{
			EditorVScroll_Up = 1;
		}
		// Scroll down button
		if (mouse_x > (CanvasXOffset + window_width - 400 - 16 + 1 - 16) &&
			mouse_x < (CanvasXOffset + window_width - 400 - 16 + 1 - 16 + 16) &&
			mouse_y > (CanvasYOffset + window_height - 16 - 16 - 16 - 4) &&
			mouse_y < (CanvasYOffset + window_height - 16 - 16 - 16 - 4 + 16))
		{
			EditorVScroll_Down = 1;
		}
	}
}

void EditorVScroll_Render(void)
{
	assert(renderer);

	// Total background (Dark corner piece)
	SDL_SetRenderDrawColor(renderer, 0x80, 0x80, 0x80, 0xFF);
	SDL_Rect rect;
	rect.x = CanvasXOffset + window_width - 400 - 16 + 1 - 16;
	rect.y = CanvasYOffset;
	rect.w = 16;
	rect.h = window_height - 16-4;
	SDL_RenderFillRect(renderer, &rect);

	// Background for scrollbar
	SDL_SetRenderDrawColor(renderer, 0xEC, 0xEC, 0xEC, 0xFF);
	SDL_Rect rectScrollBack;
	rectScrollBack.x = CanvasXOffset + window_width - 400 - 16 + 1 - 16;
	rectScrollBack.y = CanvasYOffset;
	rectScrollBack.w = 16;
	rectScrollBack.h = window_height - 16 - 16 - 4;
	SDL_RenderFillRect(renderer, &rectScrollBack);

	// Scroll up button
	SDL_SetRenderDrawColor(renderer, 0xC0, 0xC0, 0xC0, 0xFF);
	SDL_Rect rectUpButton;
	rectUpButton.x = CanvasXOffset + window_width - 400 - 16 + 1 - 16;
	rectUpButton.y = CanvasYOffset;
	rectUpButton.w = 16;
	rectUpButton.h = 16;
	SDL_RenderDrawRect(renderer, &rectUpButton);

	// Scroll down button
	SDL_SetRenderDrawColor(renderer, 0xC0, 0xC0, 0xC0, 0xFF);
	SDL_Rect rectDownButton;
	rectDownButton.x = CanvasXOffset + window_width - 400 - 16 + 1 - 16;
	rectDownButton.y = CanvasYOffset + window_height - 16 - 16 - 16 - 4;
	rectDownButton.w = 16;
	rectDownButton.h = 16;
	SDL_RenderDrawRect(renderer, &rectDownButton);

	// Scroll handle
	u32 tempHandleY = (Camera_Y * tile_size) / (WorldHeight + (Camera_Height / tile_size) + EditorVScroll_Handle_Lenght*2 + 8 + 3);
	SDL_SetRenderDrawColor(renderer, 0xBC, 0xBC, 0xBC, 0xFF);
	SDL_Rect rectHandle;	
	rectHandle.x = CanvasXOffset + window_width - 400 - 16 + 1 - 16 + 1;
	rectHandle.y = CanvasYOffset + 16 + 1 + tempHandleY;
	//rectHandle.y = CanvasYOffset + 16 + 1;
	rectHandle.w = 16 - 2;
	rectHandle.h = EditorVScroll_Handle_Lenght - 2;
	SDL_RenderFillRect(renderer, &rectHandle);
}