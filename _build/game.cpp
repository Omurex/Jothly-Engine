#include "GameObject.h"
#include "ShapeRenderer2D.h"
#include "Vector3.h"
#include "Quaternion.h"
#include "TestRunner.h"
#include "Color.h"
#include "include/raylib-cpp.hpp"
#include "Texture.h"
#include <iostream>
#include <filesystem>
#include <algorithm>
#include <string>
#include "Constants.hpp"
#include "SpriteRenderer.h"


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

	win.SetTargetFPS(60);

	/*ShapeRenderer2D* sr2D = testObj.CreateComponent<ShapeRenderer2D>()->Init(
		30, Color::RED
	);*/

	std::cout << std::filesystem::current_path() << std::endl;
	Texture tex = Texture(con::RESOURCE_PATH + "test.png");
	
	SpriteRenderer* spriteRenderer = testObj.CreateComponent<SpriteRenderer>()->Init(&tex);

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


int main(int argc, char* argv[])
{

	// Initialize resource path
	std::string resourcePath = argv[0];
	int lastSection = resourcePath.find_last_of('\\');
	resourcePath = resourcePath.substr(0, lastSection);
	std::replace(resourcePath.begin(), resourcePath.end(), '\\', '/');
	resourcePath += "/../../resources/";
	con::RESOURCE_PATH = resourcePath;


	Init();

	return 0;
}
