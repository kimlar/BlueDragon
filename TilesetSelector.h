#pragma once
#include "DataTypes.h"

extern u32 tileselector_tile_selected_x;
extern u32 tileselector_tile_selected_y;

extern void TilesetSelector_Create(void);
extern void TilesetSelector_Destroy(void);
extern void TilesetSelector_Event(void);
extern void TilesetSelector_Render(void);