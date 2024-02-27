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
#include "DelaunayTriangle.h"
#include "DelaunayPoint.h"


using namespace jothly;


GameObject testObj = GameObject("TestObj", Vector3(0, 0, 0), Quaternion::Quaternion2D(0), Vector3(1, 1));
Texture testTex;
WaveFunctionCollapseGrid* wfcGrid;

DelaunayPoint dPoint = DelaunayPoint(Vector2(0, 0));


void UpdateWFC()
{
	if (IsKeyPressed(KEY_SPACE) || IsKeyDown(KEY_F))
	{
		wfcGrid->RunNextStep();
	}
	if (IsKeyPressed(KEY_ENTER))
	{
		wfcGrid->Run();
	}
}


void Update()
{
	testObj.Update(GetFrameTime());
	
	//UpdateWFC();
}


void InitWFC()
{
	Texture ld = Texture(con::RESOURCE_PATH + "ld.png");
	Texture lu = Texture(con::RESOURCE_PATH + "lu.png");
	Texture ru = Texture(con::RESOURCE_PATH + "ru.png");
	Texture rd = Texture(con::RESOURCE_PATH + "rd.png");

	/*std::vector<WaveFunctionCollapseTile> templateTiles = std::vector<WaveFunctionCollapseTile>
	{
		WaveFunctionCollapseTile(&ld, "OXX", "XXO", "OOO", "OOO"),
	};*/

	// NOTE: MAKE TEXTURE MANAGER, BADLY NEEDED
	Texture t0 = Texture(con::RESOURCE_PATH + "coding-train/0.png");
	Texture t1 = Texture(con::RESOURCE_PATH + "coding-train/1.png");
	Texture t2 = Texture(con::RESOURCE_PATH + "coding-train/2.png");
	Texture t3 = Texture(con::RESOURCE_PATH + "coding-train/3.png");
	Texture t4 = Texture(con::RESOURCE_PATH + "coding-train/4.png");
	Texture t5 = Texture(con::RESOURCE_PATH + "coding-train/5.png");
	Texture t6 = Texture(con::RESOURCE_PATH + "coding-train/6.png");
	Texture t7 = Texture(con::RESOURCE_PATH + "coding-train/7.png");
	Texture t8 = Texture(con::RESOURCE_PATH + "coding-train/8.png");
	Texture t9 = Texture(con::RESOURCE_PATH + "coding-train/9.png");
	Texture t10 = Texture(con::RESOURCE_PATH + "coding-train/10.png");
	Texture t11 = Texture(con::RESOURCE_PATH + "coding-train/11.png");
	Texture t12 = Texture(con::RESOURCE_PATH + "coding-train/12.png");

	std::vector<WaveFunctionCollapseTile> templateTiles = std::vector<WaveFunctionCollapseTile>
	{
		WaveFunctionCollapseTile(&t0, "000", "000", "000", "000", TileSymmetry::FOUR_SIDED_SYMMETRIC),
		WaveFunctionCollapseTile(&t1, "111", "111", "111", "111", TileSymmetry::FOUR_SIDED_SYMMETRIC),
		WaveFunctionCollapseTile(&t2, "111", "121", "111", "111"),
		WaveFunctionCollapseTile(&t3, "111", "131", "111", "131", TileSymmetry::TWO_SIDED_SYMMETRIC),
		WaveFunctionCollapseTile(&t4, "011", "121", "110", "000"),
		WaveFunctionCollapseTile(&t5, "011", "111", "111", "110"),
		WaveFunctionCollapseTile(&t6, "111", "121", "111", "121", TileSymmetry::TWO_SIDED_SYMMETRIC),
		WaveFunctionCollapseTile(&t7, "131", "121", "131", "121", TileSymmetry::TWO_SIDED_SYMMETRIC),
		WaveFunctionCollapseTile(&t8, "131", "111", "121", "111"),
		WaveFunctionCollapseTile(&t9, "121", "121", "111", "121"),
		WaveFunctionCollapseTile(&t10, "121", "121", "121", "121", TileSymmetry::TWO_SIDED_SYMMETRIC),
		WaveFunctionCollapseTile(&t11, "121", "121", "111", "111"),
		WaveFunctionCollapseTile(&t12, "111", "121", "111", "121", TileSymmetry::TWO_SIDED_SYMMETRIC)
	};

	wfcGrid = testObj.CreateComponent<WaveFunctionCollapseGrid>()->Init(templateTiles, Vector2(0, 0), Vector2(GetScreenWidth(), GetScreenHeight()));

	wfcGrid->GenerateInitialGrid(20, 20);
	wfcGrid->InitializeGeneration();
}



void Draw()
{
	testObj.Draw();
	dPoint.Draw(&testTex, Vector2(100, 100));
}


void Init()
{
	// Run tests before starting engine
	TestRunner testRunner = TestRunner(true, true);
	testRunner.RunTests();


	raylib::Window win = raylib::Window(600, 600, "Jothly");

	win.SetTargetFPS(60);
	
	std::cout << std::filesystem::current_path() << std::endl;
	testTex = Texture(con::RESOURCE_PATH + "test.png");
	Texture gameObjectOrigin = Texture(con::RESOURCE_PATH + "smallBlackDot.png");

	//InitWFC();

	// Main game loop
	while (!WindowShouldClose())    // Detect window close button or ESC key
	{
		Update();

		win.BeginDrawing();
		win.ClearBackground({ 0, 128, 200, 255 });
		Draw();

		win.EndDrawing();
	}

	CloseWindow();
}


int main(int argc, char* argv[])
{
	srand(time(NULL));
	//srand(1706603061); // 5, 1706603061
	//srand(1707010537);

	std::cout << "SEED: " + std::to_string(time(NULL)) << std::endl;

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
