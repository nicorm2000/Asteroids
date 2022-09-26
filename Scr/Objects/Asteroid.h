#pragma once
#include "raylib.h"

enum Size
{
	BIG,
	MEDIUM,
	SMALL
};

struct Asteroid
{
	Vector2 size{};
	Vector2 speed{};
	Vector2 position{};
	Vector2 origin{};
	float rotation;
	float radius;
	int variants;
	Color color;
	Rectangle source;
	Rectangle dest;
	bool isActive;
	Size AsteroidSize;
	Texture2D asteroidTexture;
};

Asteroid CreateAsteroid(Asteroid& asteroid, Size asteroidSize);

void DrawAsteroid(Asteroid& asteroid, Texture2D asteroidBigTexture);
