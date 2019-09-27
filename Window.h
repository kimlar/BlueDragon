#pragma once
#include <SDL.h>
#include <stdbool.h>
#include "DataTypes.h"

extern SDL_Window *window;
extern u32 window_width;
extern u32 window_height;
extern u8 window_mouse_focus;
extern u8 window_keyboard_focus;
extern u8 window_minimized;

extern void Window_Create(u32 width, u32 height, bool vsync);
extern void Window_Destroy(void);
extern void Window_Event(SDL_Event *e);

extern float Window_GetCurrentDPI(int monitor);