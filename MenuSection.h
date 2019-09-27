#pragma once
#include "DataTypes.h"

extern u32 menu_section_state;

void MenuSection_Create(void);
void MenuSection_Destroy(void);
void MenuSection_Event(void);
void MenuSection_Render(void);