#include "Camera.h"
#include "Timer.h"
#include "Keyboard.h"
#include "World.h"
#include "Tile.h"
#include "Window.h"
#include "EditorHScroll.h"
#include "EditorVScroll.h"

u32 Camera_X;
u32 Camera_Y;
u32 Camera_Width;
u32 Camera_Height;
double Camera_MoveSpeed;

void Camera_Create(void)
{
	Camera_X = 0;
	Camera_Y = 0;
	Camera_Width = window_width - 400; //1280;
	Camera_Height = window_height; //720;
	Camera_MoveSpeed = 800.0f; //200.0; //2000.0;
}

void Camera_Update(void)
{
	/*
	if (IsKeyUp)
	{
		Camera_Y += (u32)(Camera_MoveSpeed * dt);
	}
	if (IsKeyDown)
	{
		Camera_Y -= (u32)(Camera_MoveSpeed * dt);
	}
	*/
	if (IsKeyUp || EditorVScroll_Up)
	{
		i32 cam_move_y = (i32)Camera_Y - (i32)(Camera_MoveSpeed * dt);
		if (cam_move_y < 0)
		{
			Camera_Y = 0;
		}
		else
		{
			Camera_Y = cam_move_y;
		}
	}
	if (IsKeyDown || EditorVScroll_Down)
	{
		u32 cam_move_max = (WorldHeight*tile_size) - Camera_Height + tile_size;
		//u32 cam_move_max = (WorldHeight*tile_size) - Camera_Height;
		i32 cam_move_y = (i32)Camera_Y + (i32)(Camera_MoveSpeed * dt);
		if (cam_move_y > (i32)(cam_move_max))
		{
			Camera_Y = cam_move_max;
		}
		else
		{
			Camera_Y = cam_move_y;
		}
	}
	if (IsKeyLeft || EditorHScroll_Left)
	{
		i32 cam_move_x = (i32)Camera_X - (i32)(Camera_MoveSpeed * dt);
		if (cam_move_x < 0)
		{
			Camera_X = 0;
		}
		else
		{
			Camera_X = cam_move_x;
		}
	}
	if (IsKeyRight || EditorHScroll_Right)
	{
		u32 cam_move_max = (WorldWidth*tile_size) - Camera_Width + tile_size;
		i32 cam_move_x = (i32)Camera_X + (i32)(Camera_MoveSpeed * dt);
		if (cam_move_x > (i32)(cam_move_max))
		{
			Camera_X = cam_move_max;
		}
		else
		{
			Camera_X = cam_move_x;
		}
	}
	//printf("x: %d\n", Camera_X);
}