#include "Game.h"
#include "raylib.h"
#include <ctime>
#include <math.h>

#include "Objects/Ship.h"
#include "Objects/Asteroid.h"

static void Initialize()
{
	InitWindow(1024, 768, "ASTEROIDS");
}

static void Close()
{
	CloseWindow();
}

bool CollisionCircleCircle(Ship& spaceShip, Asteroid& asteroid1)
{
	float distX = spaceShip.position.x - asteroid1.position.x;
	float distY = spaceShip.position.y - asteroid1.position.y;
	float distance = sqrt((distX * distX) + (distY * distY));

	if (distance <= spaceShip.radius + asteroid1.radius)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void GameCollisions(Ship& spaceShip, Asteroid& asteroid1)
{
	if (CollisionCircleCircle(spaceShip, asteroid1))
	{
		asteroid1.color = RED;
	}
}

void CheckInput(Ship& spaceShip, Vector2 normalizedDirection)
{
	if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
	{
		spaceShip.speed.x += normalizedDirection.x;
		spaceShip.speed.y += normalizedDirection.y;
	}

	spaceShip.position.x += spaceShip.speed.x * GetFrameTime();
	spaceShip.position.y += spaceShip.speed.y * GetFrameTime();
}

void windowTp(Ship& spaceShip, Asteroid& asteroid1, Texture2D shipTexture)
{
	//ship teleports to other side
	if (spaceShip.position.x > GetScreenWidth() + shipTexture.width)
		spaceShip.position.x = -5;
	if (spaceShip.position.x < 0 - shipTexture.width)
		spaceShip.position.x = GetScreenWidth() + 5;

	if (spaceShip.position.y > GetScreenHeight() + shipTexture.height)
		spaceShip.position.y = -5;
	if (spaceShip.position.y < 0 - shipTexture.height)
		spaceShip.position.y = GetScreenHeight() + 5;

	//asteroid teleports to other side
	if (asteroid1.position.x > GetScreenWidth() + asteroid1.size.x)
		asteroid1.position.x = -5;
	if (asteroid1.position.x < 0 - asteroid1.size.x)
		asteroid1.position.x = GetScreenWidth() + 5;

	if (asteroid1.position.y > GetScreenHeight() + asteroid1.size.y)
		asteroid1.position.y = -5;
	if (asteroid1.position.y < 0 - asteroid1.size.y)
		asteroid1.position.y = GetScreenHeight() + 5;
}

void RunGame()
{
	Initialize();

	SetTargetFPS(60);

	HideCursor();

	bool playing_game = true;
	bool exitWindow = false;
	bool isPaused = false;

	Vector2 mousePosition = GetMousePosition();

	GameScreen gameState = GameScreen::GAME;

	Texture2D shipTexture = LoadTexture("../resources/player.png");

	Ship spaceShip;
	Asteroid asteroid1;
	CreateShip(spaceShip, shipTexture);
	CreateAsteroid(asteroid1);

	Vector2 vectorDirection{ mousePosition.x - spaceShip.position.x, mousePosition.y - spaceShip.position.y };

	float arcTan = atan(vectorDirection.y / vectorDirection.x);

	float angle = arcTan * 180 / PI;

	float vectorModule = sqrt(pow(vectorDirection.x, 2)  + pow(vectorDirection.y, 2));

	Vector2 normalizedDirection = { vectorDirection.x / vectorModule, vectorDirection.y / vectorModule };

	while (!WindowShouldClose() || !playing_game)
	{
		BeginDrawing();

		ClearBackground(BLACK);

		switch (gameState)
		{
		case GameScreen::GAMETITLE:

			mousePosition = GetMousePosition();

			break;

		case GameScreen::GAME:

			mousePosition = GetMousePosition();

			vectorDirection = { mousePosition.x - spaceShip.position.x, mousePosition.y - spaceShip.position.y };

			arcTan = atan(vectorDirection.y / vectorDirection.x);

			angle = arcTan * 180 / PI;
			
			if (vectorDirection.x < 0)
			{
				angle += 180;
			}

			vectorModule = sqrt(pow(vectorDirection.x, 2) + pow(vectorDirection.y, 2));

			normalizedDirection = { vectorDirection.x / vectorModule, vectorDirection.y / vectorModule };

			asteroid1.position.x += asteroid1.speed.x * GetFrameTime();
			asteroid1.position.y += asteroid1.speed.y * GetFrameTime();

			//ship update values
			spaceShip.rotation = angle;
			spaceShip.origin = { (float)spaceShip.size.x / 2, (float)spaceShip.size.y / 2 };
			spaceShip.source = { 0, 0, (float)shipTexture.width, (float)shipTexture.height };
			spaceShip.dest = { spaceShip.position.x, spaceShip.position.y, (float)shipTexture.width,  (float)shipTexture.height };

			GameCollisions(spaceShip, asteroid1);
			CheckInput(spaceShip, normalizedDirection);
			windowTp(spaceShip, asteroid1, shipTexture);

			DrawFPS(10, 10);
			DrawShip(spaceShip, angle, shipTexture);
			DrawAsteroid(asteroid1);
			DrawCircle(mousePosition.x, mousePosition.y, 5, GREEN);
			DrawText(TextFormat("Rotation %02.02f", spaceShip.rotation), 10, 50, 20, WHITE);

			break;

		case GameScreen::HOWTOPLAY:

			mousePosition = GetMousePosition();

			break;

		case GameScreen::CREDITS:

			mousePosition = GetMousePosition();

			break;

		case GameScreen::EXIT:

			WindowShouldClose();

			break;
		}

		EndDrawing();
	}

	UnloadTexture(shipTexture);

	Close();
}