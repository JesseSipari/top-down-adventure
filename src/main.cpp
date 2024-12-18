#include <raylib.h>
#include <raymath.h>
#include "BaseCharacter.h"
#include "character.h"
#include "Prop.h"
#include "Enemy.h"
#include <string>

int main()
{
    constexpr int windowDimensions[2] = {384, 384};
    InitWindow(windowDimensions[0], windowDimensions[1], "Killerman2035");

    // Load the map texture
    Texture2D map = LoadTexture("assets/nature_tileset/Map1_1.png");
    Vector2 mapPosition = {0.0f, 0.0f};
    const float mapScale{ 4.0f };

    Character knight(windowDimensions);

    Enemy goblin(Vector2{}, LoadTexture("assets/characters/goblin_idle_spritesheet.png"), LoadTexture("assets/characters/goblin_run_spritesheet.png"));

	goblin.setTarget(&knight);

    Prop props[2]
    {
        Prop{Vector2{600.f, 300.f}, LoadTexture("assets/nature_tileset/Rock.png")},
        Prop{Vector2{400.f, 500.f}, LoadTexture("assets/nature_tileset/Log.png")}
    };

    SetTargetFPS(60);
    // Main game loop
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        mapPosition = Vector2Scale(knight.getWorldPos(), -1.f);

        // Draw the map
        DrawTextureEx(map, mapPosition, 0, mapScale, WHITE);


    	// TODO refactor into functions

         // Draw the props
        for(auto prop : props)
        {
            prop.Render(knight.getWorldPos());
        }
        // Update and draw the knight
        knight.tick(GetFrameTime());

        // check map bounds
        if (knight.getWorldPos().x < 0.f ||
            knight.getWorldPos().y <0.f ||
            knight.getWorldPos().x + windowDimensions[0] > map.width * mapScale ||
            knight.getWorldPos().y + windowDimensions[1] > map.height * mapScale )
        {
            knight.undoMovement();
        }

        // Check prop collisions
        for (auto prop : props)
        {
            if (CheckCollisionRecs(prop.getCollisionRec(knight.getWorldPos()), knight.getCollisionRec()))
            {
                knight.undoMovement();
            }
           
        }

        if (!knight.getAlive())
        {
			DrawText("Game Over", 55.f, 45.f, 40, RED);
			EndDrawing();
            continue;
        }
        else
        {
            std::string knightsHealth = "Health: ";
            knightsHealth.append(std::to_string(knight.getHealth()), 0, 5);
			DrawText(knightsHealth.c_str(), 55.f, 45.f, 40, RED);
        }
		goblin.tick(GetFrameTime());


		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
		{
			if (CheckCollisionRecs(goblin.getCollisionRec(), knight.getWeaponCollisionRec()))
			{
				goblin.setAlive(false);
			}
		}

        EndDrawing();
    }

    UnloadTexture(map);
    CloseWindow();

    return 0;
}
