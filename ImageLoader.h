#pragma once
#include <SDL.h>
#include <SDL_image.h>

extern SDL_Texture* ImageLoader_LoadTexture(char *file_path);
extern SDL_Rect ImageLoader_GetRect(SDL_Texture* texture);