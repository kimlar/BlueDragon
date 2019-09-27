#pragma once
#include <windows.h> // need ?
#include "DataTypes.h"

extern void *WorldMemory;

extern u32 WorldWidth;
extern u32 WorldHeight;

extern char* WorldFilePath;

extern void World_Create(void);
extern void World_Destroy(void);
extern void World_Render(void);

extern void World_Load(char *file_path);
extern void World_Save(char *file_path);