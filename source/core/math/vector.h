#pragma once

#include "../common.h"

struct Vec2f
{
	union
	{
		float32 x, y;
		float32 elements[2];
	};
};

Vec2f operator+(Vec2f va, Vec2f vb)
{
	Vec2f result;
	result.x = va.x + vb.x;
	result.y = va.y + vb.y;
	return result;
}