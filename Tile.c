#include "Tile.h"
#include <assert.h>
#include <SDL.h>
#include "Renderer.h"
#include "Tileset.h"
#include "UtilConvert.h"

u32 tile_size = 32; // 16;//32; //16; //64; //32;

void Tile_Render(u32 x, u32 y, u32 tileId)
{
	assert(renderer);

	/*
	SDL_SetRenderDrawColor(renderer, (u8)tileId, (u8)tileId, (u8)tileId, 255);
	SDL_Rect rect;
	//rect.x = x * tile_size; //0;
	//rect.y = y * tile_size; //0;
	rect.x = x; //0;
	rect.y = y; //0;
	rect.w = tile_size;
	rect.h = tile_size;
	SDL_RenderFillRect(renderer, &rect);
	*/

	//if(x==tile_size*2 && y==tile_size*0)
	//	printf("byte: %d\n", (tileId >> (8*1)) & 0xFF);

	SDL_Rect rectSrc;
	rectSrc.x = GetByteFromInteger(tileId, Byte0)*tile_size;
	rectSrc.y = GetByteFromInteger(tileId, Byte1)*tile_size;
	//rectSrc.x = tile_size*(tileId % 10); // 0;
	//rectSrc.y = tile_size*(tileId % 4); // 0;
	//rectSrc.x = 128;
	//rectSrc.y = 96;
	//int x = (number >> (8*n)) & 0xff;
	//rectSrc.x = 128;
	//rectSrc.y = 96;
	rectSrc.w = tile_size;
	rectSrc.h = tile_size;
	SDL_Rect rectDest;
	rectDest.x = x;
	rectDest.y = y;
	rectDest.w = tile_size;
	rectDest.h = tile_size;
	SDL_RenderCopy(renderer, bgTileset, &rectSrc, &rectDest);
}