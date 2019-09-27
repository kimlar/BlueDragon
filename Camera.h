#pragma once
#include "DataTypes.h"

extern u32 Camera_X;
extern u32 Camera_Y;
extern u32 Camera_Width;
extern u32 Camera_Height;
extern double Camera_MoveSpeed;

extern void Camera_Create(void);
//extern void Camera_Destroy(void);
extern void Camera_Update(void);
//extern void Camera_Render(void);