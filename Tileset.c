#include "Tileset.h"
#include <stdio.h>
#include "ImageLoader.h"

SDL_Texture* bgTileset;

void Tileset_Load(char *file_path)
{
	Tileset_Unload();

	bgTileset = ImageLoader_LoadTexture(file_path);
	if (bgTileset == NULL)
	{
		printf("ERROR: Unable to load texture from ImageLoader_LoadTexture()\n");
	}
}

extern void Tileset_Unload(void)
{
	if (bgTileset != NULL)
	{
		SDL_DestroyTexture(bgTileset);
	}
}