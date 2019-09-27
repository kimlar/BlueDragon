#pragma once

extern double dt; // in seconds (using vsync if possible, fallback to real-timer)
extern double delta_time; // in seconds (using real-timer)

extern void Timer_Initialize();
extern void Timer_Update();