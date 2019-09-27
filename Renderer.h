#pragma once
#include <SDL.h>
#include <stdbool.h>
#include "DataTypes.h"

extern SDL_Renderer *renderer;
extern bool use_vsync;

extern u32 CanvasXOffset;
extern u32 CanvasYOffset;

extern void Renderer_Create(bool vsync);
extern void Renderer_Destroy(void);
extern void Renderer_Begin(void);
extern void Renderer_End(void);
extern void Renderer_Force_Repaint(void);