#pragma once
#include <SDL.h>
#include <SDL_image.h>

extern SDL_Texture* bgTileset;

extern void Tileset_Load(char *file_path);
extern void Tileset_Unload(void);