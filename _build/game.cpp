#include "raylib.h"
#include "GameObject.h"
#include "ShapeRenderer2D.h"
#include "Vector3.h"
#include "Quaternion.h"
#include "TestRunner.h"
#include "Color.h"


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
	// Run tests before starting engine
	TestRunner testRunner = TestRunner(true, true);
	testRunner.RunTests();

	InitWindow(400, 400, "Jothly");
	SetTargetFPS(60);       // Set our game to run at 60 frames-per-second

	testObj.transform.pos += Vector2(100, 100);

	ShapeRenderer2D* sr2D = testObj.CreateComponent<ShapeRenderer2D>()->Init(
		30, Color::RED
	);

	// Main game loop
	while (!WindowShouldClose())    // Detect window close button or ESC key
	{
		Update();

		BeginDrawing();
		ClearBackground(RLB_RAYWHITE);
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