#include "Menu.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Window.h"
#include "Renderer.h"
#include "Font.h"
#include "MenuBar.h"
#include "MenuSection.h"

u32 menu_height;
//TTF_Font *menu_font;
//SDL_Rect menu_font_rect;
//SDL_Texture *menu_font_texture;

void Menu_Create(void)
{
	menu_height = 20;
	CanvasYOffset = menu_height;

	//menu_font = Font_Load("C:/Windows/Fonts/segoeui.ttf", 12);
	//SDL_Color color = { 0,0,0 };
	//menu_font_texture = Font_RenderText(menu_font, "File", color);
	//
	//int temp_menu_width;
	//int temp_menu_height;
	//if (SDL_QueryTexture(menu_font_texture, NULL, NULL, &temp_menu_width, &temp_menu_height) != 0)
	//{
	//	printf("ERROR: Could not query texture for size.\n");
	//	exit(1);
	//}
	//menu_font_rect.x = 0;
	//menu_font_rect.y = 0;
	//menu_font_rect.w = temp_menu_width;
	//menu_font_rect.h = temp_menu_height;

	//          # [File] [Edit] ...    #
	//          | [New ] |
	//          | [Open] |
	//          | [Save] |
	//          |--------|
	//          | [Exit] |

	// AppMenu (app_menu) : MenuBar
	// ^File   (file_menu) : MenuItem
	//  [FileGroup] (file_menu_group) : MenuGroup
	//  ^New   (file_menu_new)
	//  ^Open  (file_menu_open)
	//  ^Save  (file_menu_save)
	//  ^----  (file_menu_separator_1)
	//  ^Exit  (file_menu_exit) : MenuItem
	// ^Edit   (edit_menu)
	//  [EditGroup] (edit_menu_group) : MenuGroup
	//  ^Preferences (edit_menu_preferences)
	// ^Help   (help_menu)
	//  ^About (help_menu_about)

	MenuSection_Create();
}

void Menu_Destroy(void)
{
	//if (menu_font_texture != NULL)
	//{
	//	SDL_DestroyTexture(menu_font_texture);
	//}
	//
	//Font_Unload(menu_font);

	MenuSection_Destroy();
}

void Menu_Event(void)
{
	MenuSection_Event();
}

void Menu_Render(void)
{
	assert(renderer);
	
	/*
	SDL_SetRenderDrawColor(renderer, 0xCC, 0xCC, 0xCC, 0xFF);
	SDL_Rect rect;
	rect.x = 0;
	rect.y = 0;
	rect.w = window_width;
	rect.h = CanvasYOffset;
	SDL_RenderFillRect(renderer, &rect);
	*/

	//SDL_RenderCopy(renderer, menu_font_texture, NULL, &menu_font_rect);

	MenuBar_Render();

	MenuSection_Render();
}