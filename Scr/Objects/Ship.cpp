#include "Ship.h"

Ship CreateShip(Ship& spaceShip, Texture2D shipTexture)
{
	spaceShip.size.x = 20;
	spaceShip.size.y = 20;
	spaceShip.position.x = GetScreenWidth() / 2.0f;
	spaceShip.position.y = GetScreenHeight() / 2.0f;
	spaceShip.radius = 10;
	spaceShip.speed.x = 0;
	spaceShip.rotation = 0;
	spaceShip.color = WHITE;
	return spaceShip;
}

void DrawShip(Ship& spaceShip, float angle, Texture2D shipTexture)
{
	DrawTexturePro(shipTexture, spaceShip.source, spaceShip.dest, spaceShip.origin, angle, WHITE);
}