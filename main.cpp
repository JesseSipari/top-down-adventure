#include <raylib.h>

int main()
{
	constexpr int windowDimensions[2] = { 384, 384 };
		InitWindow(windowDimensions[0], windowDimensions[1], "Killerman2035");
		SetTargetFPS(60);

		// Load the map texture
		Texture2D map = LoadTexture("nature_tileset/Map1.png");
		

		// Main game loop
		while (!WindowShouldClose())
		{
			BeginDrawing();
			ClearBackground(RAYWHITE);
			DrawText("Killerman2035", 10, 10, 20, DARKGRAY);
			// Draw the map
			Vector2 mapPosition = { 0.0f, 0.0f };
			DrawTextureEx (map, mapPosition, 0, 4.0, WHITE);
			EndDrawing();
		}

		UnloadTexture(map);
		CloseWindow();

}