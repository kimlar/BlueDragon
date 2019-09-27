#include "EditorHScroll.h"
#include <SDL.h>
#include <assert.h>
#include "Window.h"
#include "Renderer.h"
#include "DataTypes.h"
#include "World.h"
#include "Tile.h"
#include "Camera.h"
#include "Mouse.h"

u8 EditorHScroll_Left = 0;
u8 EditorHScroll_Right = 0;

u32 EditorHScroll_Handle_Lenght;

void EditorHScroll_Create(void)
{
	u32 scrollbarWidth = Camera_Width - 16 - 16 - 30 - 1;
	EditorHScroll_Handle_Lenght = ((Camera_Width * scrollbarWidth)/(WorldWidth*tile_size));
}

void EditorHScroll_Event(void)
{
	EditorHScroll_Left = 0;
	EditorHScroll_Right = 0;
	if (mouse_button_left)
	{
		// Scroll left button
		if (mouse_x > CanvasXOffset &&
			mouse_x < (CanvasXOffset + 16) &&
			mouse_y > (CanvasYOffset + window_height - 16 - 16 - 4) &&
			mouse_y < (CanvasYOffset + window_height - 16 - 16 - 4 + 16))
		{
			EditorHScroll_Left = 1;
		}
		// Scroll right button
		if (mouse_x > (CanvasXOffset + window_width - 16 - 400 - 16 - 16 + 1) &&
			mouse_x < (CanvasXOffset + window_width - 16 - 400 - 16 - 16 + 1 + 16) &&
			mouse_y >(CanvasYOffset + window_height - 16 - 16 - 4) &&
			mouse_y < (CanvasYOffset + window_height - 16 - 16 - 4 + 16))
		{
			EditorHScroll_Right = 1;
		}
	}
}

void EditorHScroll_Render(void)
{
	assert(renderer);

	// Background for scrollbar
	SDL_SetRenderDrawColor(renderer, 0xEC, 0xEC, 0xEC, 0xFF);
	SDL_Rect rect;
	rect.x = CanvasXOffset;
	rect.y = CanvasYOffset+window_height-16-16-4;
	rect.w = window_width-16-400-16+1;
	rect.h = 16;
	SDL_RenderFillRect(renderer, &rect);

	// Scroll left button
	SDL_SetRenderDrawColor(renderer, 0xC0, 0xC0, 0xC0, 0xFF);
	SDL_Rect rectLeftButton;
	rectLeftButton.x = CanvasXOffset;
	rectLeftButton.y = CanvasYOffset +window_height - 16 -16 -4;
	rectLeftButton.w = 16;
	rectLeftButton.h = 16;
	SDL_RenderDrawRect(renderer, &rectLeftButton);

	// Scroll right button
	SDL_SetRenderDrawColor(renderer, 0xC0, 0xC0, 0xC0, 0xFF);
	SDL_Rect rectRightButton;
	rectRightButton.x = CanvasXOffset + window_width-16-400-16-16+1;
	rectRightButton.y = CanvasYOffset + window_height - 16 - 16 - 4;
	rectRightButton.w = 16;
	rectRightButton.h = 16;
	SDL_RenderDrawRect(renderer, &rectRightButton);

	// Scroll handle
	//u32 tempHandleX = (Camera_X * tile_size)/WorldWidth;
	u32 tempHandleX = (Camera_X * tile_size) / (WorldWidth + (Camera_Width/tile_size) + EditorHScroll_Handle_Lenght/2 - 4);
	SDL_SetRenderDrawColor(renderer, 0xBC, 0xBC, 0xBC, 0xFF);
	SDL_Rect rectHandle;
	rectHandle.x = CanvasXOffset + 16 + 1 + tempHandleX;
	//rectHandle.x = CanvasXOffset + 16 + 1;
	rectHandle.y = CanvasYOffset + window_height - 16 - 16 - 4 +1;
	rectHandle.w = EditorHScroll_Handle_Lenght -2;
	rectHandle.h = 16 -2;
	SDL_RenderFillRect(renderer, &rectHandle);


	//EditorHScroll_Handle_Lenght = ((Camera_Width * scrollbarWidth)/(WorldWidth*tile_size));
}