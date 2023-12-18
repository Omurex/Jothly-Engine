#include <iostream>
#include "raylib.h"
#include "GameObject.h"
#include "ShapeRenderer2D.h"
#include "Vector3.h"
#include "Quaternion.h"
#include "Vector4.h"

using namespace jothly;


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

	ShapeRenderer2D* sr2D = testObj.CreateComponent<ShapeRenderer2D>();
	sr2D->SetOffset({ 100, 100 });

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