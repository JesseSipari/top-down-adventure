#pragma once
#include <raylib.h>
#include "baseCharacter.h"

class Character : public BaseCharacter
{
public:
	Character(const int window_dimensions[]);
	~Character();

	virtual void tick(float deltaTime) override;
	virtual Vector2 getScreenPos() override;

	// getters
	Rectangle getWeaponCollisionRec() const { return weaponCollisionRec; }
	float getHealth() const { return health; }
	void takeDamage(float damage);


private:
	int windowWidth{};
	int windowHeight{};
	Texture2D weapon{LoadTexture("assets/characters/weapon_sword.png")};
	Rectangle weaponCollisionRec{};
	float health{ 100.f };
};

