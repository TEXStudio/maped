#pragma once
#include <cmath>

struct Vector2f
{
	float x, y; 
};

struct Vector3f
{
	float x, y, z;
};

static Vector2f Normalise(Vector2f in)
{
	Vector2f Out;
	float Length = sqrt((in.x * in.x) + (in.y * in.y));
	Out.x = in.x/Length;
	Out.y = in.y/Length;
	return Out;
}