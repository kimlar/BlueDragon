#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include "DataTypes.h"

extern TTF_Font* Font_Load(char *file_path, u8 font_size);
extern void Font_Unload(TTF_Font *font);
extern SDL_Texture* Font_RenderText(TTF_Font* font, char *text, SDL_Color color);