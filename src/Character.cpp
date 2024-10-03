#include "character.h"
#include <raymath.h>



Character::Character(const int window_dimensions[])
	:texture(LoadTexture("assets/characters/knight_idle_spritesheet.png")),
	idle(LoadTexture("assets/characters/knight_idle_spritesheet.png")),
	run(LoadTexture("assets/characters/knight_run_spritesheet.png"))
{
	width = texture.width / static_cast<float>(maxFrames);
	height = texture.height;
	screenPos = { static_cast<float>(window_dimensions[0]) / 2.0f - scale * (0.5f * width),
					static_cast<float>(window_dimensions[1]) / 2.0f - scale * (0.5f * height) };

}

Character::~Character() {
	UnloadTexture(texture);
	UnloadTexture(idle);
	UnloadTexture(run);
}

void Character::undoMovement()
{
	worldPos = worldPosLastFrame;
}

void Character::tick(float deltaTime)
{
	worldPosLastFrame = worldPos;
	Vector2 direction{};
	if (IsKeyDown(KEY_A)) direction.x -= 1.0f;
	if (IsKeyDown(KEY_D)) direction.x += 1.0f;
	if (IsKeyDown(KEY_W)) direction.y -= 1.0f;
	if (IsKeyDown(KEY_S)) direction.y += 1.0f;
	if (Vector2Length(direction) != 0.0f)

	{
		// set worldPos = worldPos + direction
		worldPos = Vector2Add(worldPos, Vector2Scale(Vector2Normalize(direction), speed));
		direction.x < 0.f ? rightLeft = -1.f : rightLeft = 1.f;
		texture = run;
	}
	else
	{
		texture = idle;
	}

	// Update animation frame
	runningTime += deltaTime;
	if (runningTime >= updateTime)
	{
		frame++;
		runningTime = 0.f;
		if (frame > maxFrames) frame = 0;
	}

	// Draw the knight
	Rectangle source{frame * width, 0.f, rightLeft * width, height};
	Rectangle dest{screenPos.x, screenPos.y, scale * width, scale * height};
	DrawTexturePro(texture, source, dest, Vector2{}, 0.f, WHITE);
}