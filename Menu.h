#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "DataTypes.h"

extern u32 menu_height;

extern void Menu_Create(void);
extern void Menu_Destroy(void);
extern void Menu_Event(void);
extern void Menu_Render(void);