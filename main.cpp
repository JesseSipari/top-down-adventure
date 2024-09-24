#include <raylib.h>
#include <vector>
#include <raymath.h>

int main()
{
	constexpr int windowDimensions[2] = { 384, 384 };
		InitWindow(windowDimensions[0], windowDimensions[1], "Killerman2035");
		SetTargetFPS(60);

		// Load the map texture
		Texture2D map = LoadTexture("nature_tileset/Map1.png");
		Vector2 mapPosition = { 0.0f, 0.0f };

		float speed = 4.0f;

		// Main game loop
		while (!WindowShouldClose())
		{
			BeginDrawing();
			ClearBackground(RAYWHITE);

			Vector2 direction{};
			if (IsKeyDown(KEY_A)) direction.x -= 1.0f;
			if (IsKeyDown(KEY_D)) direction.x += 1.0f;
			if (IsKeyDown(KEY_W)) direction.y -= 1.0f;
			if (IsKeyDown(KEY_S)) direction.y += 1.0f;
			if (Vector2Length(direction) != 0.0f)
			{

				mapPosition = Vector2Subtract(mapPosition, Vector2Scale(Vector2Normalize(direction), speed));
				
				
			}

			DrawTextureEx (map, mapPosition, 0, 4.0, WHITE);
			EndDrawing();
		}
			
		UnloadTexture(map);
		CloseWindow();

}
