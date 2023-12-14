#include "raylib.h"


void Update()
{

}


void Draw()
{

}


void Init()
{
	InitWindow(400, 400, "Gravity");
	SetTargetFPS(60);       // Set our game to run at 60 frames-per-second

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