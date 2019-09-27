#pragma once
#include <SDL.h>
#include "DataTypes.h"

extern u8 IsKeyW;
extern u8 IsKeyS;
extern u8 IsKeyA;
extern u8 IsKeyD;

extern u8 IsKeyUp;
extern u8 IsKeyDown;
extern u8 IsKeyLeft;
extern u8 IsKeyRight;

extern void Keyboard_Event(SDL_Event *e);