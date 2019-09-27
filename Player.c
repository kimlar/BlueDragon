#include "Player.h"
#include <assert.h>
#include <SDL.h>
#include "Renderer.h"
#include "Timer.h"
#include "Keyboard.h"

float Player_Position_X;
float Player_Position_Y;
float Player_Velocity_X;
float Player_Velocity_Y;
float Player_Width;
float Player_Height;

void Player_Create(void)
{
	Player_Position_X = 10.0f;
	Player_Position_Y = 10.0f;
	Player_Velocity_X = 500.0f;
	Player_Velocity_Y = 500.0f;
	Player_Width = 40.0f;
	Player_Height = 40.0f;
}

void Player_Destroy(void)
{

}

void Player_Update(void)
{
	if (IsKeyW)
	{
		Player_Position_Y -= Player_Velocity_Y * (float)dt;
	}
	if (IsKeyS)
	{
		Player_Position_Y += Player_Velocity_Y * (float)dt;
	}
	if (IsKeyA)
	{
		Player_Position_X -= Player_Velocity_X * (float)dt;
	}
	if (IsKeyD)
	{
		Player_Position_X += Player_Velocity_X * (float)dt;
	}
}

void Player_Render(void)
{
	assert(renderer);

	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_Rect rect;
	//rect.x = 100;
	rect.x = (int)Player_Position_X + CanvasXOffset;
	rect.y = (int)Player_Position_Y + CanvasYOffset;
	rect.w = (int)Player_Width;
	rect.h = (int)Player_Height;
	SDL_RenderFillRect(renderer, &rect);
}