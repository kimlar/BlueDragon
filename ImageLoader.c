#include "ImageLoader.h"
#include <stdio.h>
#include "Renderer.h"

SDL_Texture* ImageLoader_LoadTexture(char *file_path)
{
	// The final texture
	SDL_Texture* newTexture = NULL;

	// Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(file_path);
	if (loadedSurface == NULL)
	{
		printf("ERROR: Unable to load image %s! SDL_image Error: %s\n", file_path, IMG_GetError());
	}
	else
	{
		// Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if (newTexture == NULL)
		{
			printf("ERROR: Unable to create texture from %s! SDL Error: %s\n", file_path, SDL_GetError());
		}

		// Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	return newTexture;
}

SDL_Rect ImageLoader_GetRect(SDL_Texture* texture)
{
	SDL_Rect rect;
	int texture_width;
	int texture_height;
	if (SDL_QueryTexture(texture, NULL, NULL, &texture_width, &texture_height) != 0)
	{
		printf("ERROR: Could not query texture for size.\n");
		exit(1);
	}
	rect.x = 0;
	rect.y = 0;
	rect.w = texture_width;
	rect.h = texture_height;
	return rect;
}