#include "TilesetSelector.h"
#include <SDL.h>
#include <assert.h>
#include "Window.h"
#include "Renderer.h"
#include "Font.h"
#include "UI.h"
#include "ImageLoader.h"
#include "Mouse.h"
#include "Window.h"
#include "Menu.h"

SDL_Rect tileset_title_font_rect;
SDL_Texture *tileset_title_font_texture;

SDL_Rect TilesetSelector_Rect;

SDL_Rect tileset_texture_rect;
SDL_Texture *tileset_texture;

SDL_Rect gridRect;
u32 tileselector_tile_size;

SDL_Rect gridRectSelected;
u32 tileselector_tile_selected_x;
u32 tileselector_tile_selected_y;

void TilesetSelector_Create(void)
{
	TilesetSelector_Rect.x = window_width - 400 - 16 +1; //800;
	TilesetSelector_Rect.y = menu_height;//100;
	TilesetSelector_Rect.w = 400 + 16;
	TilesetSelector_Rect.h = 300;

	SDL_Color color = { 0,0,0 };
	tileset_title_font_texture = Font_RenderText(font_ui, "Tileset", color);
	int temp_tileset_text_width;
	int temp_tileset_text_height;
	if (SDL_QueryTexture(tileset_title_font_texture, NULL, NULL, &temp_tileset_text_width, &temp_tileset_text_height) != 0)
	{
		printf("ERROR: Could not query texture for size.\n");
		exit(1);
	}
	tileset_title_font_rect.x = TilesetSelector_Rect.x + 8;
	tileset_title_font_rect.y = TilesetSelector_Rect.y + 4;
	tileset_title_font_rect.w = temp_tileset_text_width;
	tileset_title_font_rect.h = temp_tileset_text_height;

	tileset_texture = ImageLoader_LoadTexture("GrassTiles-TempArt.png");
	tileset_texture_rect = ImageLoader_GetRect(tileset_texture);
	tileset_texture_rect.x = TilesetSelector_Rect.x + 8;
	tileset_texture_rect.y = TilesetSelector_Rect.y + 4 + 20;

	gridRect = tileset_texture_rect;
	tileselector_tile_size = 32;

	gridRectSelected.x = tileset_texture_rect.x;
	gridRectSelected.y = tileset_texture_rect.y;
	gridRectSelected.w = tileselector_tile_size;
	gridRectSelected.h = tileselector_tile_size;
	tileselector_tile_selected_x = 0;
	tileselector_tile_selected_y = 0;


	//int temp_tileset_texture_width;
	//int temp_tileset_texture_height;
	//if (SDL_QueryTexture(tileset_texture, NULL, NULL, &temp_tileset_texture_width, &temp_tileset_texture_height) != 0)
	//{
	//	printf("ERROR: Could not query texture for size.\n");
	//	exit(1);
	//}
	//tileset_texture_rect.x = 0;
	//tileset_texture_rect.y = 0;
	//tileset_texture_rect.w = temp_tileset_texture_width;
	//tileset_texture_rect.h = temp_tileset_texture_height;
}

void TilesetSelector_Destroy(void)
{
	if (tileset_texture != NULL)
	{
		SDL_DestroyTexture(tileset_texture);
	}

	if (tileset_title_font_texture != NULL)
	{
		SDL_DestroyTexture(tileset_title_font_texture);
	}
}

void TilesetSelector_Event(void)
{
	if (mouse_button_left)
	{
		if (mouse_x > (u32)tileset_texture_rect.x &&
			mouse_x < (u32)(tileset_texture_rect.x + tileset_texture_rect.w) &&
			mouse_y > (u32)tileset_texture_rect.y &&
			mouse_y < (u32)(tileset_texture_rect.y + tileset_texture_rect.h)
			)
		{
			tileselector_tile_selected_x = (mouse_x - tileset_texture_rect.x) / tileselector_tile_size;
			tileselector_tile_selected_y = (mouse_y - tileset_texture_rect.y) / tileselector_tile_size;
			gridRectSelected.x = tileset_texture_rect.x + (tileselector_tile_selected_x * tileselector_tile_size);
			gridRectSelected.y = tileset_texture_rect.y + (tileselector_tile_selected_y * tileselector_tile_size);
		}
	}
	

/*
gridRectSelected.x = tileset_texture_rect.x;
gridRectSelected.y = tileset_texture_rect.y;
gridRectSelected.w = tileselector_tile_size;
gridRectSelected.h = tileselector_tile_size;
tileselector_tile_selected_x = 0;
tileselector_tile_selected_y = 0;
*/
}

void TilesetSelector_Render(void)
{
	assert(renderer);

	// Base frame
	SDL_SetRenderDrawColor(renderer, 0xCC, 0xCC, 0xCC, 0xFF);
	SDL_RenderFillRect(renderer, &TilesetSelector_Rect);
	// Border frame
	SDL_SetRenderDrawColor(renderer, 0x40, 0x40, 0x40, 0xFF);
	SDL_RenderDrawRect(renderer, &TilesetSelector_Rect);
	// Text: Tileset
	SDL_RenderCopy(renderer, tileset_title_font_texture, NULL, &tileset_title_font_rect);
	// Frame for tileset
	SDL_SetRenderDrawColor(renderer, 0xAA, 0xAA, 0xAA, 0xFF);
	SDL_Rect frameTilesetRect;
	frameTilesetRect.x = TilesetSelector_Rect.x + 8;
	frameTilesetRect.y = TilesetSelector_Rect.y + 4 + 20;
	frameTilesetRect.w = TilesetSelector_Rect.w - 16;
	frameTilesetRect.h = TilesetSelector_Rect.h - 4 - 20 - 8;
	SDL_RenderFillRect(renderer, &frameTilesetRect);
	// Border frame for tileset
	SDL_SetRenderDrawColor(renderer, 0x80, 0x80, 0x80, 0xFF);
	SDL_RenderFillRect(renderer, &frameTilesetRect);
	// Draw tileset
	SDL_RenderCopy(renderer, tileset_texture, NULL, &tileset_texture_rect);
	// Draw tileset grid
	SDL_SetRenderDrawColor(renderer, 0x80, 0x80, 0x80, 0x80);
	for (u32 i = 1; i < (u32)(tileset_texture_rect.w / tileselector_tile_size); ++i)
		SDL_RenderDrawLine(renderer, gridRect.x+i*tileselector_tile_size, gridRect.y, gridRect.x + i*tileselector_tile_size, gridRect.y + gridRect.h);
	for (u32 i = 1; i < (u32)(tileset_texture_rect.h / tileselector_tile_size); ++i)
		SDL_RenderDrawLine(renderer, gridRect.x, gridRect.y + i * tileselector_tile_size, gridRect.x + gridRect.w, gridRect.y + i * tileselector_tile_size);
	// Draw tileset grid selecter
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(renderer, 0x80, 0x80, 0xFF, 0x80);
	SDL_RenderFillRect(renderer, &gridRectSelected);
}