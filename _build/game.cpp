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
#include "WaveFunctionCollapseGrid.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "TextureDrawing.h"


using namespace jothly;


GameObject testObj = GameObject("TestObj", Vector3(0, 0, 0), Quaternion::Quaternion2D(0), Vector3(1, 1));
Texture tex;


void Update()
{
	testObj.Update(GetFrameTime());
}


void Draw()
{
	testObj.Draw();
	//TextureDrawing::DrawTexture(tex, Vector2(0, 0), Vector2(tex.GetWidth() / 2, tex.GetHeight() / 2), Vector2(100, 100), 45);

}


void Init()
{
	// Run tests before starting engine
	TestRunner testRunner = TestRunner(true, true);
	testRunner.RunTests();


	raylib::Window win = raylib::Window(600, 600, "Jothly");

	win.SetTargetFPS(60);
	//testObj.transform.pos = Vector2(GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f);

	/*ShapeRenderer2D* sr2D = testObj.CreateComponent<ShapeRenderer2D>()->Init(
		30, Color::RED
	);*/

	std::cout << std::filesystem::current_path() << std::endl;
	tex = Texture(con::RESOURCE_PATH + "test.png");
	Texture gameObjectOrigin = Texture(con::RESOURCE_PATH + "smallBlackDot.png");
	
	Texture ld = Texture(con::RESOURCE_PATH + "ld.png");
	Texture lu = Texture(con::RESOURCE_PATH + "lu.png");
	Texture ru = Texture(con::RESOURCE_PATH + "ru.png");
	Texture rd = Texture(con::RESOURCE_PATH + "rd.png");

	std::vector<WaveFunctionCollapseTile> templateTiles = std::vector<WaveFunctionCollapseTile>
	{
		WaveFunctionCollapseTile(&ld, "OXX", "XXO", "OOO", "OOO"),
	};

	WaveFunctionCollapseGrid* wfcGrid = 
		testObj.CreateComponent<WaveFunctionCollapseGrid>()->Init(templateTiles, Vector2(0, 0), Vector2(GetScreenWidth(), GetScreenHeight()));

	wfcGrid->GenerateInitialGrid(4, 4);
	wfcGrid->Run();

	/*for (int x = 0; x < wfcGrid->GetNumCellsX(); x++)
	{
		for (int y = 0; y < wfcGrid->GetNumCellsY(); y++)
		{
			auto testTile = wfcGrid->GetTile(x, y);
			testTile->texture = &tex;
		}
	}*/

	SpriteRenderer* spriteRenderer = testObj.CreateComponent<SpriteRenderer>()->Init(&gameObjectOrigin, Color::GREEN);

	// Main game loop
	while (!WindowShouldClose())    // Detect window close button or ESC key
	{
		Update();

		win.BeginDrawing();
		win.ClearBackground({ 0, 128, 200, 255 });
		Draw();

		//testObj.transform.rot *= Quaternion::Quaternion2D(30 * GetFrameTime());

		win.EndDrawing();
	}

	CloseWindow();
}


int main(int argc, char* argv[])
{
	srand(time(NULL));

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
