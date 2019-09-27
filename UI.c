#include "UI.h"

TTF_Font *font_ui;
//TTF_Font *font_ui_italic;
//TTF_Font *font_ui_bold;
//TTF_Font *font_header;

void UI_Create(void)
{
	font_ui = Font_Load("C:/Windows/Fonts/segoeui.ttf", 12);
}

void UI_Destroy(void)
{
	Font_Unload(font_ui);
}