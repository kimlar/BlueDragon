#include "World.h"
#include <stdio.h>
#include <stdlib.h>
#include "Tile.h"
#include "Camera.h"
#include "Tileset.h"
#include "Renderer.h"

void *WorldMemory;

u32 WorldWidth;
u32 WorldHeight;

char* WorldFilePath;

void World_Create(void)
{
	World_Destroy();

	//World_Load("World6.dat"); // 256x256
	//World_Load("World6-rnd.dat"); // 256x256 randomized
	//World_Load("World-tile-test.dat"); // 256x256
	WorldFilePath = "World-tile-test.dat";
	World_Load(WorldFilePath); // 256x256
	Tileset_Load("GrassTiles-TempArt.png");
}

void World_Destroy(void)
{
	if (WorldMemory)
	{
		VirtualFree(WorldMemory, 0, MEM_RELEASE);
	}
	Tileset_Unload();
}

void World_Render(void)
{
	u32 *WorldStart = WorldMemory;
	u32 *WorldPtr = WorldMemory;
	
	for (u32 Y = 0; Y < ((Camera_Height / tile_size)+2); ++Y)
	{
		for (u32 X = 0; X < ((Camera_Width / tile_size)+1); ++X)
		{
			WorldPtr = WorldStart + WorldWidth*(Y + Camera_Y / tile_size) + (X + Camera_X / tile_size);
			Tile_Render(X * tile_size - Camera_X % tile_size + CanvasXOffset, Y*tile_size - Camera_Y % tile_size + CanvasYOffset, *WorldPtr);
		}
	}
}

void World_Load(char *file_path)
{
	FILE *filePtr;
	fopen_s(&filePtr ,file_path, "rb");
	if (filePtr == NULL)
	{
		printf("Cannot open file: %s\n", file_path);
		exit(1);
	}

	// Get world width (tiles)
	if (fread(&WorldWidth, sizeof(u32), 1, filePtr) != 1)
	{
		if (feof(filePtr))
		{
			printf("Premature end of file.\n");
			fclose(filePtr);
			exit(1);
		}
		else
		{
			printf("File read error.\n");
			fclose(filePtr);
			exit(1);
		}
	}

	// Get world height (tiles)
	if (fread(&WorldHeight, sizeof(u32), 1, filePtr) != 1)
	{
		if (feof(filePtr))
		{
			printf("Premature end of file.\n");
			fclose(filePtr);
			exit(1);
		}
		else
		{
			printf("File read error.\n");
			fclose(filePtr);
			exit(1);
		}
	}

	// Allocate memory for tile data
	u32 tile_count = (WorldWidth * WorldHeight);
	//printf("tile_count: %d\n", tile_count);
	WorldMemory = VirtualAlloc(0, (tile_count * sizeof(u32)), MEM_RESERVE|MEM_COMMIT, PAGE_READWRITE);
	
	// Tile data
	//if (fread(WorldData, sizeof(u32), tile_count, filePtr) != tile_count)
	if (fread(WorldMemory, sizeof(u32), tile_count, filePtr) != tile_count)
	{
		if (feof(filePtr))
		{
			printf("Premature end of file.\n");
			fclose(filePtr);
			exit(1);
		}
		else
		{
			printf("File read error.\n");
			fclose(filePtr);
			exit(1);
		}
	}
	fclose(filePtr);
}

void World_Save(char *file_path)
{
	FILE *filePtr;
	fopen_s(&filePtr, file_path, "wb");
	if (filePtr == NULL)
	{
		printf("Cannot open file: %s\n", file_path);
		exit(1);
	}

	// Write world width (tiles)
	if (fwrite(&WorldWidth, sizeof(u32), 1, filePtr) != 1)
	{
		printf("Could not write data to file: %s\n", file_path);
		exit(1);
	}

	// Write world height (tiles)
	if (fwrite(&WorldHeight, sizeof(u32), 1, filePtr) != 1)
	{
		printf("Could not write data to file: %s\n", file_path);
		exit(1);
	}

	// Write world data (tiles)
	if (fwrite(WorldMemory, sizeof(u32), (WorldWidth*WorldHeight), filePtr) != (WorldWidth*WorldHeight))
	{
		printf("Could not write data to file: %s\n", file_path);
		exit(1);
	}
	
	fclose(filePtr);
}