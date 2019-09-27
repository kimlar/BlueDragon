#include "Keyboard.h"

u8 IsKeyW;
u8 IsKeyS;
u8 IsKeyA;
u8 IsKeyD;

u8 IsKeyUp;
u8 IsKeyDown;
u8 IsKeyLeft;
u8 IsKeyRight;

void Keyboard_Event(SDL_Event *e)
{
	switch (e->key.keysym.sym)
	{
		case SDLK_w:
		{
			IsKeyW = (e->key.state == SDL_PRESSED ? 1 : 0);
		} break;

		case SDLK_s:
		{
			IsKeyS = (e->key.state == SDL_PRESSED ? 1 : 0);
		} break;

		case SDLK_a:
		{
			IsKeyA = (e->key.state == SDL_PRESSED ? 1 : 0);
		} break;

		case SDLK_d:
		{
			IsKeyD = (e->key.state == SDL_PRESSED ? 1 : 0);
		} break;

		case SDLK_UP:
		{
			IsKeyUp = (e->key.state == SDL_PRESSED ? 1 : 0);
		} break;

		case SDLK_DOWN:
		{
			IsKeyDown = (e->key.state == SDL_PRESSED ? 1 : 0);
		} break;

		case SDLK_LEFT:
		{
			IsKeyLeft = (e->key.state == SDL_PRESSED ? 1 : 0);
		} break;

		case SDLK_RIGHT:
		{
			IsKeyRight = (e->key.state == SDL_PRESSED ? 1 : 0);
		} break;
	}
}
