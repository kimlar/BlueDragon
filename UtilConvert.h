#pragma once
#include "DataTypes.h"

enum GetByteEnum
{
	Byte0 = 0,
	Byte1,
	Byte2,
	Byte3
};

u8 GetByteFromInteger(i32 data, u8 number)
{
	return (data >> (8 * number)) & 0xFF;
}