#include "GameObject.h"
#include "ShapeRenderer2D.h"
#include "Vector3.h"
#include "Quaternion.h"
#include "TestRunner.h"
#include "Color.h"
#include "include/raylib-cpp.hpp"


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

	raylib::Window win = raylib::Window(400, 400, "Jothly");
	//raylib::SetTargetFPS(60);       // Set our game to run at 60 frames-per-second

	win.SetTargetFPS(60);

	ShapeRenderer2D* sr2D = testObj.CreateComponent<ShapeRenderer2D>()->Init(
		30, Color::RED
	);

	// Main game loop
	while (!WindowShouldClose())    // Detect window close button or ESC key
	{
		Update();

		win.BeginDrawing();
		win.ClearBackground({ 255, 255, 255, 255 });
		Draw();
		win.EndDrawing();
	}

	CloseWindow();
}


int main()
{
	Init();

	return 0;
}