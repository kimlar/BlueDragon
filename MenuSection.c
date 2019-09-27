#include "MenuSection.h"
#include <assert.h>
#include <stdbool.h>
#include "Window.h"
#include "Renderer.h"
#include "Font.h"
#include "UI.h"
#include "Mouse.h"
#include "MenuGroup.h"
#include "Menu.h"
#include "Application.h"
#include "World.h"

typedef enum
{
	Default = 0,
	Hover,
	Clicked
} MenuSectionState;

typedef enum
{
	None = 0,
	File_New,
	File_Open,
	File_Save,
	File_Exit,
} MenuSelectionEnum;

// Menu
u32 menu_section_state = 0;

// File
u32 file_number_items = 4;
u32 file_menu_selection = 0;
MenuSectionState fileMenuSectionState = Default;
SDL_Rect file_menu_section_font_rect;
SDL_Texture *file_menu_section_font_texture;

// Edit
u32 edit_number_items = 0;
//u32 edit_menu_selection = 0;
MenuSectionState editMenuSectionState = Default;
SDL_Rect edit_menu_section_font_rect;
SDL_Texture *edit_menu_section_font_texture;

////////////////////////////////////////////////////

// File->New
//u32 file_menu_new_id = File_New;
SDL_Rect file_menu_new_font_rect;
SDL_Texture *file_menu_new_font_texture;
// File->Open
//u32 file_menu_open_id = File_Open;
SDL_Rect file_menu_open_font_rect;
SDL_Texture *file_menu_open_font_texture;
// File->Save
//u32 file_menu_save_id = File_Save;
SDL_Rect file_menu_save_font_rect;
SDL_Texture *file_menu_save_font_texture;
// File->LineSeparator1
// File->Exit
//u32 file_menu_exit_id = File_Exit;
SDL_Rect file_menu_exit_font_rect;
SDL_Texture *file_menu_exit_font_texture;

void MenuSection_Create(void)
{
	SDL_Color color = { 0,0,0 };

	// File
	fileMenuSectionState = Default;
	file_menu_section_font_texture = Font_RenderText(font_ui, "File", color);
	int temp_file_menu_width;
	int temp_file_menu_height;
	if (SDL_QueryTexture(file_menu_section_font_texture, NULL, NULL, &temp_file_menu_width, &temp_file_menu_height) != 0)
	{
		printf("ERROR: Could not query texture for size.\n");
		exit(1);
	}
	file_menu_section_font_rect.x = 8;
	file_menu_section_font_rect.y = 2;
	file_menu_section_font_rect.w = temp_file_menu_width;
	file_menu_section_font_rect.h = temp_file_menu_height;

	// Edit
	editMenuSectionState = Default;
	edit_menu_section_font_texture = Font_RenderText(font_ui, "Edit", color);
	int temp_edit_menu_width;
	int temp_edit_menu_height;
	if (SDL_QueryTexture(edit_menu_section_font_texture, NULL, NULL, &temp_edit_menu_width, &temp_edit_menu_height) != 0)
	{
		printf("ERROR: Could not query texture for size.\n");
		exit(1);
	}
	edit_menu_section_font_rect.x = (file_menu_section_font_rect.x + file_menu_section_font_rect.w + 8) + 8;
	edit_menu_section_font_rect.y = 2;
	edit_menu_section_font_rect.w = temp_edit_menu_width;
	edit_menu_section_font_rect.h = temp_edit_menu_height;

	///////////////////////////////////////////////////////////////////////////

	// File->New
	file_menu_new_font_texture = Font_RenderText(font_ui, "New", color);
	int temp_file_menu_new_width;
	int temp_file_menu_new_height;
	if (SDL_QueryTexture(file_menu_new_font_texture, NULL, NULL, &temp_file_menu_new_width, &temp_file_menu_new_height) != 0)
	{
		printf("ERROR: Could not query texture for size.\n");
		exit(1);
	}
	file_menu_new_font_rect.x = 20 + 8;
	file_menu_new_font_rect.y = 2 + 1*menu_height;
	file_menu_new_font_rect.w = temp_file_menu_new_width;
	file_menu_new_font_rect.h = temp_file_menu_new_height;

	// File->Open
	file_menu_open_font_texture = Font_RenderText(font_ui, "Open", color);
	int temp_file_menu_open_width;
	int temp_file_menu_open_height;
	if (SDL_QueryTexture(file_menu_open_font_texture, NULL, NULL, &temp_file_menu_open_width, &temp_file_menu_open_height) != 0)
	{
		printf("ERROR: Could not query texture for size.\n");
		exit(1);
	}
	file_menu_open_font_rect.x = 20 + 8;
	file_menu_open_font_rect.y = 2 + 2 * menu_height;
	file_menu_open_font_rect.w = temp_file_menu_open_width;
	file_menu_open_font_rect.h = temp_file_menu_open_height;

	// File->Save
	file_menu_save_font_texture = Font_RenderText(font_ui, "Save", color);
	int temp_file_menu_save_width;
	int temp_file_menu_save_height;
	if (SDL_QueryTexture(file_menu_save_font_texture, NULL, NULL, &temp_file_menu_save_width, &temp_file_menu_save_height) != 0)
	{
		printf("ERROR: Could not query texture for size.\n");
		exit(1);
	}
	file_menu_save_font_rect.x = 20 + 8;
	file_menu_save_font_rect.y = 2 + 3 * menu_height;
	file_menu_save_font_rect.w = temp_file_menu_save_width;
	file_menu_save_font_rect.h = temp_file_menu_save_height;

	// File->Exit
	file_menu_exit_font_texture = Font_RenderText(font_ui, "Exit", color);
	int temp_file_menu_exit_width;
	int temp_file_menu_exit_height;
	if (SDL_QueryTexture(file_menu_exit_font_texture, NULL, NULL, &temp_file_menu_exit_width, &temp_file_menu_exit_height) != 0)
	{
		printf("ERROR: Could not query texture for size.\n");
		exit(1);
	}
	file_menu_exit_font_rect.x = 20 + 8;
	file_menu_exit_font_rect.y = 2 + 4 * menu_height;
	file_menu_exit_font_rect.w = temp_file_menu_exit_width;
	file_menu_exit_font_rect.h = temp_file_menu_exit_height;
}

void MenuSection_Destroy(void)
{
	if (file_menu_new_font_texture != NULL)
	{
		SDL_DestroyTexture(file_menu_new_font_texture);
	}

	if (file_menu_open_font_texture != NULL)
	{
		SDL_DestroyTexture(file_menu_open_font_texture);
	}

	if (file_menu_save_font_texture != NULL)
	{
		SDL_DestroyTexture(file_menu_save_font_texture);
	}

	if (file_menu_exit_font_texture != NULL)
	{
		SDL_DestroyTexture(file_menu_exit_font_texture);
	}
	
	////////////////////////////////////////////////////////

	if (file_menu_section_font_texture != NULL)
	{
		SDL_DestroyTexture(file_menu_section_font_texture);
	}

	if (edit_menu_section_font_texture != NULL)
	{
		SDL_DestroyTexture(edit_menu_section_font_texture);
	}

	Font_Unload(font_ui);
}

void MenuSection_Event(void)
{
	bool isFileRect = (mouse_x > (u32)(file_menu_section_font_rect.x - 8) &&
		mouse_x < (u32)(file_menu_section_font_rect.x + file_menu_section_font_rect.w + 8) &&
		mouse_y >(u32)(file_menu_section_font_rect.y - 2) &&
		mouse_y < (u32)(file_menu_section_font_rect.y + file_menu_section_font_rect.h + 1));
	
	bool isEditRect = (mouse_x > (u32)(edit_menu_section_font_rect.x - 8) &&
		mouse_x < (u32)(edit_menu_section_font_rect.x + edit_menu_section_font_rect.w + 8) &&
		mouse_y >(u32)(edit_menu_section_font_rect.y - 2) &&
		mouse_y < (u32)(edit_menu_section_font_rect.y + edit_menu_section_font_rect.h + 1));
	
	bool isLeftPressed = mouse_button_left && !mouse_button_left_old;
	bool isLeftReleased = !mouse_button_left && mouse_button_left_old;
	
	if (!isFileRect && isLeftPressed && fileMenuSectionState == Clicked)
	{
		//printf("file_menu_selection: %d\n", file_menu_selection);
		switch (file_menu_selection)
		{
			case File_New:
			{
				//printf("New\n");
			} break;

			case File_Open:
			{
				//printf("Open\n");
				World_Load(WorldFilePath);
			} break;

			case File_Save:
			{
				//printf("Save\n");
				World_Save(WorldFilePath);
			} break;

			case File_Exit:
			{
				//printf("Exit\n");
				running = 0;
			} break;
		}
	}

	if (isFileRect)
	{
		if (isLeftReleased)
		{
			if (fileMenuSectionState == Hover)
			{
				fileMenuSectionState = Clicked;
				editMenuSectionState = Default;
			}
		}
		else
		{
			fileMenuSectionState = Hover;
		}
	}
	else
	{
		if (isLeftPressed && fileMenuSectionState == Clicked)
		{
			fileMenuSectionState = Default;
		}
		else if (isEditRect && fileMenuSectionState == Clicked)
		{
			fileMenuSectionState = Default;
			editMenuSectionState = Clicked;
		}
	}

	if (isEditRect)
	{
		if (isLeftReleased)
		{
			if (editMenuSectionState == Hover)
			{
				editMenuSectionState = Clicked;
				fileMenuSectionState = Default;
			}
		}
		else
		{
			editMenuSectionState = Hover;
		}
	}
	else
	{
		if (isLeftPressed && editMenuSectionState == Clicked)
		{
			editMenuSectionState = Default;
		}
		else if (isFileRect && editMenuSectionState == Clicked)
		{
			fileMenuSectionState = Clicked;
			editMenuSectionState = Default;
		}
	}

	if (isLeftReleased)
	{
		menu_section_state = (file_menu_selection != 0); /*|| (edit_menu_selection != 0);*/
		file_menu_selection = 0;
		//edit_menu_selection = 0;
		//printf("menu_section_state: %d\n", menu_section_state);
	}
}

void MenuSection_Render(void)
{
	assert(renderer);

	// File
	if (fileMenuSectionState == Hover)
	{
		SDL_SetRenderDrawColor(renderer, 0xAA, 0xAA, 0xAA, 0xFF);
		SDL_Rect rect;
		rect.x = file_menu_section_font_rect.x - 8;
		rect.y = 0;
		rect.w = file_menu_section_font_rect.w + 16;
		rect.h = file_menu_section_font_rect.h + 3;
		SDL_RenderFillRect(renderer, &rect);
	}
	else if (fileMenuSectionState == Clicked)
	{
		SDL_SetRenderDrawColor(renderer, 0xAA, 0xAA, 0xAA, 0xFF);
		SDL_Rect rectHover;
		rectHover.x = file_menu_section_font_rect.x - 8;
		rectHover.y = 0;
		rectHover.w = file_menu_section_font_rect.w + 16;
		rectHover.h = file_menu_section_font_rect.h + 3;
		SDL_RenderFillRect(renderer, &rectHover);

		SDL_Rect rect;
		rect.x = file_menu_section_font_rect.x - 8;
		rect.y = menu_height;
		rect.w = 100;
		rect.h = 2 + 4 * menu_height;
		MenuGroup_Render(rect);

		////////////////////////////////////////////////////

		file_menu_selection = 0;
		if ((mouse_y / menu_height) > 0 && (mouse_y / menu_height) <= file_number_items)
		{
			SDL_Rect rectMenuSelect;
			rectMenuSelect.x = file_menu_new_font_rect.x - 20 - 8;
			rectMenuSelect.y = (mouse_y / menu_height)*menu_height + 1;
			rectMenuSelect.w = 100;
			rectMenuSelect.h = 2 + menu_height - 2;
			if (mouse_x > (u32)rectMenuSelect.x && mouse_x <= (u32)(rectMenuSelect.x + rectMenuSelect.w))
			{
				SDL_SetRenderDrawColor(renderer, 0x67, 0x89, 0xAB, 0xFF);
				rectMenuSelect.x += 1;
				rectMenuSelect.w -= 2;
				SDL_RenderFillRect(renderer, &rectMenuSelect);
				file_menu_selection = (mouse_y / menu_height);
			}
		}

		////////////////////////////////////////////////////

		//File->New
		SDL_RenderCopy(renderer, file_menu_new_font_texture, NULL, &file_menu_new_font_rect);
		//File->Open
		SDL_RenderCopy(renderer, file_menu_open_font_texture, NULL, &file_menu_open_font_rect);
		//File->Save
		SDL_RenderCopy(renderer, file_menu_save_font_texture, NULL, &file_menu_save_font_rect);
		//File->LineSeparator_1
		SDL_RenderDrawLine(renderer, 1, 4 * menu_height, 100 - 2, 4 * menu_height);
		//File->Exit
		SDL_RenderCopy(renderer, file_menu_exit_font_texture, NULL, &file_menu_exit_font_rect);

		////////////////////////////////////////////////////
	}
	SDL_RenderCopy(renderer, file_menu_section_font_texture, NULL, &file_menu_section_font_rect);

	// Edit
	if (editMenuSectionState == Hover)
	{
		SDL_SetRenderDrawColor(renderer, 0xAA, 0xAA, 0xAA, 0xFF);
		SDL_Rect rect;
		rect.x = edit_menu_section_font_rect.x - 8;
		rect.y = 0;
		rect.w = edit_menu_section_font_rect.w + 16;
		rect.h = edit_menu_section_font_rect.h + 3;
		SDL_RenderFillRect(renderer, &rect);
	}
	else if (editMenuSectionState == Clicked)
	{
		SDL_SetRenderDrawColor(renderer, 0xAA, 0xAA, 0xAA, 0xFF);
		SDL_Rect rectHover;
		rectHover.x = edit_menu_section_font_rect.x - 8;
		rectHover.y = 0;
		rectHover.w = edit_menu_section_font_rect.w + 16;
		rectHover.h = edit_menu_section_font_rect.h + 3;
		SDL_RenderFillRect(renderer, &rectHover);

		SDL_Rect rect;
		rect.x = edit_menu_section_font_rect.x - 8;
		rect.y = menu_height;
		rect.w = 100;
		rect.h = 2 + 4 * menu_height;
		MenuGroup_Render(rect);
	}
	SDL_RenderCopy(renderer, edit_menu_section_font_texture, NULL, &edit_menu_section_font_rect);
}