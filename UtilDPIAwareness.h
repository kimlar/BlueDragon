//
// WEBSOURCE: https://nlguillemot.wordpress.com/2016/12/11/high-dpi-rendering/
//
// LINK WITH: Shcore.lib
//
// INFO FOR SDL2: Add SDL_WINDOW_ALLOW_HIGHDPI flag for SDL_CreateWindow().
#pragma once
#include <Windows.h>
#include <ShellScalingAPI.h>

//extern void UtilDPIAwareness_SetDPIAwareness(void);

void UtilDPIAwareness_SetDPIAwareness(void)
{
	HRESULT hr = SetProcessDpiAwareness(PROCESS_PER_MONITOR_DPI_AWARE);
	if (FAILED(hr))
	{
		printf("ERROR: Failed to set DPI Awareness\n");
	}
}
