#pragma once
#include <raylib.h>
#include "baseCharacter.h"

class Character : public BaseCharacter
{
public:
	Character(const int window_dimensions[]);
	~Character();

	virtual void tick(float deltaTime) override;


private:

};

