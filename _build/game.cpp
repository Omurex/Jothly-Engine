#include "raylib.h"
#include "GameObject.h"
#include "ShapeRenderer.h"


GameObject testObj;


void Update()
{
	testObj.Update(GetFrameTime());
}


void Draw()
{
	testObj.Draw();
}


void Init()
{
	InitWindow(400, 400, "Gravity");
	SetTargetFPS(60);       // Set our game to run at 60 frames-per-second

	testObj.CreateComponent<ShapeRenderer>();

	// Main game loop
	while (!WindowShouldClose())    // Detect window close button or ESC key
	{
		Update();

		BeginDrawing();
		ClearBackground(RAYWHITE);
		Draw();
		EndDrawing();
	}

	CloseWindow();
}


int main()
{
	Init();

	return 0;
}