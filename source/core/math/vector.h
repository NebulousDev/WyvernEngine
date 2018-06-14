#pragma once

#include "../common.h"

struct Vec2f
{
	union
	{
		float32 x, y;
		float32 u, v;
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

struct Vec3f
{
	union
	{
		float32 x, y, z;
		float32 r, g, b;
		float32 elements[3];
	};
};

Vec3f operator+(Vec3f va, Vec3f vb)
{
	Vec3f result;
	result.x = va.x + vb.x;
	result.y = va.y + vb.y;
	result.z = va.z + vb.z;
	return result;
}

struct Vec4f
{
	union
	{
		float32 x, y, z, w;
		float32 elements[4];
	};
};

Vec4f operator+(Vec4f va, Vec4f vb)
{
	Vec4f result;
	result.x = va.x + vb.x;
	result.y = va.y + vb.y;
	result.z = va.z + vb.z;
	result.w = va.w + vb.w;
	return result;
}