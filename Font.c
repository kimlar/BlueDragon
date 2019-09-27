#include "Font.h"
#include "stdlib.h"
#include "Renderer.h"

TTF_Font* Font_Load(char *file_path, u8 font_size)
{
	// Open the font
	TTF_Font *font = TTF_OpenFont(file_path, font_size);
	if (font == NULL)
	{
		printf("ERROR: Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
		exit(1);
	}

	return font;
}

void Font_Unload(TTF_Font *font)
{
	if (font == NULL)
		return;

	// Free font
	TTF_CloseFont(font);
	font = NULL;
}

SDL_Texture* Font_RenderText(TTF_Font* font, char *text, SDL_Color color)
{
	// Check font
	if (font == NULL)
	{
		printf("ERROR: Unable to render text because specified font file is invalid.\n");
		exit(1);
	}

	// Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Solid(font, text, color);
	if (textSurface == NULL)
	{
		printf("ERROR: Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
		exit(1);
	}

	// Create texture from surface pixels
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, textSurface);
	if (texture == NULL)
	{
		printf("ERROR: Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
		exit(1);
	}

	// Free old surface
	SDL_FreeSurface(textSurface);

	return texture;
}