#pragma once
#include "baseCharacter.h"
#include "character.h"
#include "raylib.h"

class Enemy : public BaseCharacter
{
public:
	Enemy(Vector2 pos, Texture2D idle_texture, Texture2D run_texture);
	~Enemy();

	virtual void tick(float deltaTime) override;
	void setTarget(Character* character) {target = character;}

private:
	// Variables
	Character* target;

};