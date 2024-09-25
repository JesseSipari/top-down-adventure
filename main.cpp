#include <ios>
#include <raylib.h>
#include <vector>
#include <raymath.h>

class Character
{
public:
	Character();
	~Character();
	Vector2 getWorldPos() const { return worldPos; }
	void setScreenPos(const int window_dimensions[2]);
	void tick(float deltaTime);

private:
	Texture2D texture;
	Texture2D idle;
	Texture2D run;
	Vector2 screenPos{};
	Vector2 worldPos{};
	// 1 = facing right, -1 = facing left
	float rightLeft{1.f};
	// animation variables
	float runningTime{};
	int frame{};
	constexpr static int maxFrames{6};
	constexpr static float updateTime{1.f / 12.f};
	const float speed{4.f};
	const float scale{4.f};
};

Character::Character()
	: texture(LoadTexture("characters/knight_idle_spritesheet.png")),
	idle(LoadTexture("characters/knight_idle_spritesheet.png")),
	run(LoadTexture("characters/knight_run_spritesheet.png")) {}

Character::~Character() {
	UnloadTexture(texture);
	UnloadTexture(idle);
	UnloadTexture(run);
}

void Character::setScreenPos(const int window_dimensions[2])
{
	screenPos = {
		static_cast<float>(window_dimensions[0]) / 2.0f - scale * (0.5f * static_cast<float>(texture.width) / 6.0f),
		static_cast<float>(window_dimensions[1]) / 2.0f - scale * (0.5f * static_cast<float>(texture.height) / 8.0f)

	};
}

void Character::tick(float deltaTime)
{
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

	Rectangle source{
		frame * static_cast<float>(texture.width) / 6.f, 0.f, rightLeft * static_cast<float>(texture.width) / 6.f,
		static_cast<float>(texture.height)
	};
	Rectangle dest{
		screenPos.x, screenPos.y, scale * static_cast<float>(texture.width) / 6.f,
		scale * static_cast<float>(texture.height)
	};
	DrawTexturePro(texture, source, dest, Vector2{}, 0.f, WHITE);
}

int main()
{
	constexpr int windowDimensions[2] = {384, 384};
	InitWindow(windowDimensions[0], windowDimensions[1], "Killerman2035");
	SetTargetFPS(60);

	// Load the map texture
	Texture2D map = LoadTexture("nature_tileset/Map1.png");
	Vector2 mapPosition = {0.0f, 0.0f};

	Character knight;
	knight.setScreenPos(windowDimensions);
	// Main game loop

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(RAYWHITE);

		mapPosition = Vector2Scale(knight.getWorldPos(), -1.f);

		// Draw the map
		DrawTextureEx(map, mapPosition, 0, 4.f, WHITE);

		// Update and draw the knight
		knight.tick(GetFrameTime());


		EndDrawing();
	}

	UnloadTexture(map);
	CloseWindow();

	return 0;
}
