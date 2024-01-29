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
		WaveFunctionCollapseTile(&t0, "000", "000", "000", "000"),
		WaveFunctionCollapseTile(&t1, "111", "111", "111", "111"),
		WaveFunctionCollapseTile(&t2, "111", "121", "111", "111"),
		WaveFunctionCollapseTile(&t3, "111", "131", "111", "131"),
		WaveFunctionCollapseTile(&t4, "011", "121", "110", "000"),
		WaveFunctionCollapseTile(&t5, "011", "111", "111", "110"),
		WaveFunctionCollapseTile(&t6, "111", "121", "111", "121"),
		WaveFunctionCollapseTile(&t7, "131", "121", "131", "121"),
		WaveFunctionCollapseTile(&t8, "131", "111", "121", "111"),
		WaveFunctionCollapseTile(&t9, "121", "121", "111", "121"),
		WaveFunctionCollapseTile(&t10, "121", "121", "121", "121"), // check
		WaveFunctionCollapseTile(&t11, "121", "121", "111", "111"),
		WaveFunctionCollapseTile(&t12, "111", "121", "111", "121")
	};

	WaveFunctionCollapseGrid* wfcGrid = 
		testObj.CreateComponent<WaveFunctionCollapseGrid>()->Init(templateTiles, Vector2(0, 0), Vector2(GetScreenWidth(), GetScreenHeight()));

	wfcGrid->GenerateInitialGrid(50, 50);
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
