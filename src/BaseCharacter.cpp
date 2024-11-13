#include "BaseCharacter.h"


BaseCharacter::BaseCharacter()

{
}

BaseCharacter::~BaseCharacter()
{
	UnloadTexture(texture);
	UnloadTexture(idle);
	UnloadTexture(run);
}

void BaseCharacter::undoMovement()
{
	worldPos = worldPosLastFrame;
}

Rectangle BaseCharacter::getCollisionRec()
{

	return Rectangle{
		screenPos.x,
		screenPos.y,
		width * scale,
		height * scale
	};

}

void BaseCharacter::tick(float deltaTime)
{
	worldPosLastFrame = worldPos;

	// Update animation frame
	runningTime += deltaTime;
	if (runningTime >= updateTime)
	{
		frame++;
		runningTime = 0.f;
		if (frame > maxFrames) frame = 0;
	}

	// Draw the enemy
	Rectangle source{ frame * width, 0.f, rightLeft * width, height };
	Rectangle dest{ screenPos.x, screenPos.y, scale * width, scale * height };
	DrawTexturePro(texture, source, dest, Vector2{}, 0.f, WHITE);
}