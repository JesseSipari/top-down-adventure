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


private:
	int windowWidth{};
	int windowHeight{};
};

