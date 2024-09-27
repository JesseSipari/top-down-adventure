
#include <raylib.h>
#include <raymath.h>
#include "Character.h"

int main()
{
	constexpr int windowDimensions[2] = {384, 384};
	InitWindow(windowDimensions[0], windowDimensions[1], "Killerman2035");
	SetTargetFPS(60);

	// Load the map texture
	Texture2D map = LoadTexture("nature_tileset/Map1.png");
	Vector2 mapPosition = {0.0f, 0.0f};

	Character knight;
	knight.setScreenPos(windowDimensions);
	// Main game loop

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(RAYWHITE);

		mapPosition = Vector2Scale(knight.getWorldPos(), -1.f);

		// Draw the map
		DrawTextureEx(map, mapPosition, 0, 4.f, WHITE);

		// Update and draw the knight
		knight.tick(GetFrameTime());


		EndDrawing();
	}

	UnloadTexture(map);
	CloseWindow();

	return 0;
}
