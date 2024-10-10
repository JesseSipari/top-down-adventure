#include <raylib.h>
#include <raymath.h>
#include "character.h"
#include "Prop.h"

int main()
{
    constexpr int windowDimensions[2] = {384, 384};
    InitWindow(windowDimensions[0], windowDimensions[1], "Killerman2035");
    SetTargetFPS(60);

    // Load the map texture
    Texture2D map = LoadTexture("assets/nature_tileset/Map1_1.png");
    Vector2 mapPosition = {0.0f, 0.0f};
    const float mapScale{ 4.0f };
    Character knight(windowDimensions);
    Prop rock(Vector2{}, LoadTexture("assets/nature_tileset/Rock.png"));
    // Main game loop
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        mapPosition = Vector2Scale(knight.getWorldPos(), -1.f);

        // Draw the map
        DrawTextureEx(map, mapPosition, 0, mapScale, WHITE);
        
        rock.Render(knight.getWorldPos());

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

        EndDrawing();
    }

    UnloadTexture(map);
    CloseWindow();

    return 0;
}
