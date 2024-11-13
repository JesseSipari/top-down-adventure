#include "character.h"
#include <raymath.h>



Character::Character(const int window_dimensions[]) :
	windowWidth(window_dimensions[0]), windowHeight(window_dimensions[1])
{
	texture = LoadTexture("assets/characters/knight_idle_spritesheet.png");
	idle = LoadTexture("assets/characters/knight_idle_spritesheet.png");
	run = LoadTexture("assets/characters/knight_run_spritesheet.png");

	width = texture.width / static_cast<float>(maxFrames);
	height = texture.height;

}

Vector2 Character::getScreenPos()
{
	return Vector2{
		static_cast<float>(windowWidth) / 2.0f - scale * (0.5f * width),
		static_cast<float>(windowHeight) / 2.0f - scale * (0.5f * height)
	};
}

Character::~Character() {
	UnloadTexture(texture);
	UnloadTexture(idle);
	UnloadTexture(run);
}


void Character::tick(float deltaTime)
{

	if (IsKeyDown(KEY_A)) velocity.x -= 1.0f;
	if (IsKeyDown(KEY_D)) velocity.x += 1.0f;
	if (IsKeyDown(KEY_W)) velocity.y -= 1.0f;
	if (IsKeyDown(KEY_S)) velocity.y += 1.0f;
	BaseCharacter::tick(deltaTime);


}

