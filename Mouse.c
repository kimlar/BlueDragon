#include "Mouse.h"

u32 mouse_x;
u32 mouse_y;
u8 mouse_button_left;
u8 mouse_button_left_old;
u8 mouse_button_middle;
u8 mouse_button_middle_old;
u8 mouse_button_right;
u8 mouse_button_right_old;
u8 mouse_button_x1;
u8 mouse_button_x2;
//u32 mouse_wheel_x;
//u32 mouse_wheel_x_up;
//u32 mouse_wheel_x_down;
u32 mouse_wheel_y;
//u32 mouse_wheel_y_up;
//u32 mouse_wheel_y_down;

void Mouse_Event(SDL_Event *e)
{
	switch (e->type)
	{
		case SDL_MOUSEMOTION:
		{
			mouse_x = e->motion.x;
			mouse_y = e->motion.y;
		} break;

		case SDL_MOUSEBUTTONUP:
		case SDL_MOUSEBUTTONDOWN:
		{
			switch (e->button.button)
			{
				case SDL_BUTTON_LEFT:
				{
					mouse_button_left_old = mouse_button_left;
					mouse_button_left = (e->button.state == SDL_PRESSED ? 1 : 0);
				} break;

				case SDL_BUTTON_MIDDLE:
				{
					mouse_button_middle_old = mouse_button_middle;
					mouse_button_middle = (e->button.state == SDL_PRESSED ? 1 : 0);
				} break;

				case SDL_BUTTON_RIGHT:
				{
					mouse_button_right_old = mouse_button_right;
					mouse_button_right = (e->button.state == SDL_PRESSED ? 1 : 0);
				} break;

				case SDL_BUTTON_X1:
				{
					mouse_button_x1 = (e->button.state == SDL_PRESSED ? 1 : 0);
				} break;

				case SDL_BUTTON_X2:
				{
					mouse_button_x2 = (e->button.state == SDL_PRESSED ? 1 : 0);
				} break;
			}
		} break;

		case SDL_MOUSEWHEEL:
		{
			u8 scroll_speed = 1;
			if (e->wheel.y > 0) // scroll up
			{
				mouse_wheel_y += scroll_speed;
			}
			else if (e->wheel.y < 0) // scroll down
			{
				mouse_wheel_y -= scroll_speed;
			}
		} break;
	}
}