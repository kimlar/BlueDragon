#pragma once
#include <SDL.h>
#include "DataTypes.h"

extern u32 mouse_x;
extern u32 mouse_y;
extern u8 mouse_button_left;
extern u8 mouse_button_left_old;
extern u8 mouse_button_middle;
extern u8 mouse_button_middle_old;
extern u8 mouse_button_right;
extern u8 mouse_button_right_old;
extern u8 mouse_button_x1;
extern u8 mouse_button_x2;
//extern u32 mouse_wheel_x;
//extern u32 mouse_wheel_x_up;
//extern u32 mouse_wheel_x_down;
extern u32 mouse_wheel_y;
//extern u32 mouse_wheel_y_up;
//extern u32 mouse_wheel_y_down;

extern void Mouse_Event(SDL_Event *e);