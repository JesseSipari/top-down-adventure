#ifndef BASE_CHARACTER_H
#define BASE_CHARACTER_H
#include <raylib.h>


class BaseCharacter
{
public:
	BaseCharacter();
	~BaseCharacter();
	virtual void tick(float deltaTime);
	Vector2 getWorldPos() const { return worldPos; }
	void undoMovement();
	Rectangle getCollisionRec();
	virtual Vector2 getScreenPos() = 0; // pure virtual function to make this an abstract class

	// protected so that derived classes can access them
protected:
	Texture2D texture;
	Texture2D idle;
	Texture2D run;

	Vector2 worldPos{};
	Vector2 worldPosLastFrame{};
	Vector2 velocity{};

	// 1 = facing right, -1 = facing left
	float rightLeft{ 1.f };
	// animation variables
	float runningTime{};
	int frame{};
	int maxFrames{ 6 };
	float updateTime{ 1.f / 12.f };
	float speed{ 4.f };
	float scale{ 4.0f };
	float width{};
	float height{};

private:

};

#endif // BASE_CHARACTER_H
