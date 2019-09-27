#include "Editor.h"
#include <SDL.h>
#include "Renderer.h"
#include "Window.h"
#include "Timer.h"
#include "Keyboard.h"
#include "Player.h"
#include "World.h"
#include "Camera.h"
#include "TilesetSelector.h"
#include "Mouse.h"
#include "Tile.h"
#include "Menu.h"
#include "EditorHScroll.h"
#include "EditorVScroll.h"
#include "DataTypes.h"
#include "MenuSection.h"

SDL_Rect Editor_Current_Tile_Rect;

u8 Editor_Mouse_Pressed_Old;

void Editor_Start(void)
{
	Editor_Mouse_Pressed_Old = 0;

	Editor_Current_Tile_Rect.x = CanvasXOffset;
	Editor_Current_Tile_Rect.y = CanvasYOffset;
	Editor_Current_Tile_Rect.w = tile_size;
	Editor_Current_Tile_Rect.h = tile_size;

	Camera_Create();
	World_Create();
	EditorHScroll_Create();
	EditorVScroll_Create();
	Player_Create();
}

void Editor_Exit(void)
{
	Player_Destroy();
	World_Destroy();
}

void Editor_Update(void)
{
	//posX += velX * (float)dt;
	//posY += velY * (float)dt;
	//
	//if (posX > (window_width - boxSizeW) || posX < 0)
	//{
	//	velX = -velX;
	//}
	//if (posY > (window_height - boxSizeH) || posY < 0)
	//{
	//	velY = -velY;
	//}		

	EditorHScroll_Event();
	EditorVScroll_Event();
	Camera_Update();
	Player_Update();

	/*
	extern u32 tileselector_tile_selected_x;
	extern u32 tileselector_tile_selected_y;
	*/

	/*
	extern void *WorldMemory;

	extern u32 WorldWidth;
	extern u32 WorldHeight;
		
	u32 *WorldStart = WorldMemory;
	u32 *WorldPtr = WorldMemory;

	for (u32 Y = 0; Y < ((Camera_Height / tile_size)+2); ++Y)
	{
		for (u32 X = 0; X < ((Camera_Width / tile_size)+1); ++X)
		{
			WorldPtr = WorldStart + WorldWidth*(Y + Camera_Y / tile_size) + (X + Camera_X / tile_size);
			Tile_Render(X * tile_size - Camera_X % tile_size + CanvasXOffset, Y*tile_size - Camera_Y % tile_size + CanvasYOffset, *WorldPtr);
		}
	}
	*/
	/*
	u32 Camera_X;
	u32 Camera_Y;
	u32 Camera_Width;
	u32 Camera_Height;
	*/
	//if (mouse_button_left)

	if (menu_section_state)
		return;
	if (mouse_x > CanvasXOffset && mouse_x < (CanvasXOffset + Camera_Width - tile_size/2 - 16))
	{
		if (mouse_y > CanvasYOffset && mouse_y < (CanvasYOffset + Camera_Height - tile_size/2 - 16 - 4))
		{
			Editor_Current_Tile_Rect.x = ((mouse_x + Camera_X % tile_size - CanvasXOffset) / tile_size) * tile_size - Camera_X % tile_size + CanvasXOffset;
			Editor_Current_Tile_Rect.y = ((mouse_y + Camera_Y % tile_size - CanvasYOffset) / tile_size) * tile_size - Camera_Y % tile_size + CanvasYOffset;

			if (mouse_button_left && Editor_Mouse_Pressed_Old==0)
			{
				Editor_Mouse_Pressed_Old = 1;
				u32 gx = (Editor_Current_Tile_Rect.x + Camera_X) / tile_size;
				u32 gy = (Editor_Current_Tile_Rect.y + Camera_Y) / tile_size;
				//printf("grid(%d,%d)\n", gx, gy);
												
				u32 *WorldPtr = WorldMemory;
				WorldPtr += gx + gy * WorldWidth;
				*WorldPtr = tileselector_tile_selected_x + tileselector_tile_selected_y * 256;
			}
			else if (!mouse_button_left && Editor_Mouse_Pressed_Old == 1)
			{
				Editor_Mouse_Pressed_Old = 0;
			}
		}
	}
}

void Editor_Render(void)
{
	World_Render();

	// Draw tileset grid
	SDL_SetRenderDrawColor(renderer, 0x80, 0x80, 0x80, 0xFF);
	for (u32 i = 1; i < (u32)((Camera_Width / tile_size) + 1); ++i)
		SDL_RenderDrawLine(renderer, i*tile_size - Camera_X % tile_size + CanvasXOffset, CanvasYOffset, i*tile_size - Camera_X % tile_size + CanvasXOffset, CanvasYOffset + Camera_Height);
	for (u32 i = 1; i < (u32)((Camera_Height / tile_size) + 1); ++i)
		SDL_RenderDrawLine(renderer, CanvasXOffset, i*tile_size - Camera_Y % tile_size + CanvasYOffset, CanvasXOffset + Camera_Width, i*tile_size - Camera_Y % tile_size + CanvasYOffset);

	// Draw tileset grid selecter
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(renderer, 0x80, 0x80, 0xFF, 0x80);
	SDL_RenderFillRect(renderer, &Editor_Current_Tile_Rect);
	
	Player_Render();

	// Vertical scrollbar for Editor
	EditorVScroll_Render();
	
	// Horizontal scrollbar for Editor
	EditorHScroll_Render();

	// Right frame (for tools and such)
	SDL_SetRenderDrawColor(renderer, 0xCC, 0xCC, 0xCC, 0xFF);
	SDL_Rect Editor_RightFrame_Rect;
	Editor_RightFrame_Rect.x = window_width - 400 - 16 + 1;
	Editor_RightFrame_Rect.y = menu_height;
	Editor_RightFrame_Rect.w = 400 + 16;
	Editor_RightFrame_Rect.h = window_height;
	SDL_RenderFillRect(renderer, &Editor_RightFrame_Rect);
}