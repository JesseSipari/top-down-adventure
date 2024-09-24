#include <ios>
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
		float scale = 4.0f;
		Texture2D knight = LoadTexture("characters/knight_idle_spritesheet.png");
		Texture2D knight_idle = LoadTexture("characters/knight_idle_spritesheet.png");
		Texture2D knight_run = LoadTexture("characters/knight_run_spritesheet.png");
		Vector2 knightPosition = {
			static_cast<float>(windowDimensions[0]) / 2.0f - scale * (0.5f * static_cast<float>(knight.width) / 6.0f),
			static_cast<float>(windowDimensions[1]) / 2.0f - scale * (0.5f * static_cast<float>(knight.height) / 8.0f)
		};


		// 1 = facing right, -1 = facing left
		float rightLeft{ 1.f };

		// animation variables
		float runningTime{};
		int frame{};
		constexpr int maxFrames{ 6 };
		constexpr float updateTime{ 1.f/12.f};

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
				// set mapPosition = mapPosition - direction
				mapPosition = Vector2Subtract(mapPosition, Vector2Scale(Vector2Normalize(direction), speed));
				direction.x < 0.f ? rightLeft = -1.f : rightLeft = 1.f;
				knight = knight_run;
			}
			else
			{
				knight = knight_idle;
			}

			// Draw the map
			DrawTextureEx (map, mapPosition, 0, scale, WHITE);

			// Update animation frame
			runningTime += GetFrameTime();
			if (runningTime >= updateTime)
			{
				frame++;
				runningTime = 0.f;
				if (frame > maxFrames) frame = 0;
			}

			// Draw the knight
			
			Rectangle source{ frame * static_cast<float>(knight.width) / 6.f, 0.f, rightLeft * static_cast<float>(knight.width) / 6.f, static_cast<float>(knight.height) };
			Rectangle dest{ knightPosition.x, knightPosition.y, scale * static_cast<float>(knight.width) / 6.f, scale * static_cast<float>(knight.height) };
			DrawTexturePro(knight, source, dest, Vector2{}, 0.f, WHITE);

			EndDrawing();
		}
		
		UnloadTexture(map);
		UnloadTexture(knight);
		CloseWindow();

		return 0;
}
