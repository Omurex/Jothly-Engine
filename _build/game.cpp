#include "raylib.h"
#include "GameObject.h"
#include "ShapeRenderer.h"


GameObject testObj;


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

	new ShapeRenderer(&testObj);

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