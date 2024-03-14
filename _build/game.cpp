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
#include "NavMesh.h"
#include "ShapeDrawing2D.h"
#include "SquareNavMeshObstacle.h"


using namespace jothly;


GameObject testObj = GameObject("TestObj", Vector3(0, 0, 0), Quaternion::Quaternion2D(0), Vector3(1, 1));
Texture testTex;
WaveFunctionCollapseGrid* wfcGrid;
Texture smallBlackDot;

//GameObject dTriangle;
DelaunayTriangle tri;
//DelaunayPoint dPoint = DelaunayPoint(Vector2(0, 0));
DelaunayTriangle superTri;
GameObject navmesh;


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

	navmesh.Update(GetFrameTime());

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
	navmesh.Draw();
	//superTri.Draw(3, Color::YELLOW);

	//tri.Draw(1, Color::RED);
	//dTriangle.Draw();
	//dPoint.Draw(&testTex, Vector2(100, 100));

	/*ShapeDrawing2D::DrawCircle(tri.GetCircumcenter(), tri.GetCircumradius(), Color::RED);
	tri.Draw(3);
	ShapeDrawing2D::DrawCircle(tri.GetCircumcenter(), 10, Color::BLUE);*/

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
	smallBlackDot = Texture(con::RESOURCE_PATH + "smallBlackDot.png");

	//tri = DelaunayTriangle(Vector2(100, 100), Vector2(400, 200), Vector2(200, 400));

	//dTriangle.CreateComponent<DelaunayTriangle>()->Init(Vector2(0, 0), Vector2(100, 100), Vector2(200, 400), &testTex);

	//std::vector<Vector2> testPoints { Vector2(100, 100), Vector2(50, 100), Vector2(200, 300), Vector2(150, 250) };

	NavMesh* navmeshComponent = navmesh.CreateComponent<NavMesh>()->Init(5, Color::BLACK, true, 1, Color::WHITE, true);
	navmeshComponent->GenerateRandomPoints(20, Vector2(5, 5), Vector2(595, 595));

	SquareNavMeshObstacle squareObstacle1 = SquareNavMeshObstacle(Vector2(225, 225));
	squareObstacle1.color = Color::RED;

	SquareNavMeshObstacle squareObstacle2 = SquareNavMeshObstacle(Vector2(400, 400));
	squareObstacle2.color = Color::RED;

	SquareNavMeshObstacle squareObstacle3 = SquareNavMeshObstacle(Vector2(450, 250));
	squareObstacle3.color = Color::RED;

	SquareNavMeshObstacle squareObstacle4 = SquareNavMeshObstacle(Vector2(100, 100));
	squareObstacle4.color = Color::RED;

	navmeshComponent->AddObstacle(&squareObstacle1);
	navmeshComponent->AddObstacle(&squareObstacle2);
	navmeshComponent->AddObstacle(&squareObstacle3);

	//navmeshComponent->LoadObstaclePoints(std::vector<Vector2>{
	//	//Vector2(225, 225),
	//	Vector2(220, 220),
	//	Vector2(230, 220),
	//	Vector2(230, 230),
	//	Vector2(220, 230)
	//	/*Vector2(205, 205),
	//	Vector2(245, 205),
	//	Vector2(245, 245),
	//	Vector2(205, 245)*/
	//});

	//navmeshComponent->AddPoints(std::vector<Vector2> { Vector2(195, 195), Vector2(255, 195), Vector2(255, 255), Vector2(195, 255) });
	/*navmeshComponent->AddPoints(std::vector<Vector2> { Vector2(200, 200), Vector2(250, 200), Vector2(250, 250), Vector2(200, 250),
		Vector2(225, 200), Vector2(225, 250), Vector2(200, 225), Vector2(250, 225)});*/
	navmeshComponent->AddPoints(std::vector<Vector2> {Vector2(5, 5), Vector2(595, 5), Vector2(595, 595), Vector2(5, 595)});
	//navmeshComponent->AddPoints(std::vector<Vector2>{Vector2(240, 240)});

	/*navmeshComponent->LoadPoints(std::vector<Vector2>{
		Vector2(355.442963, 330.130920),
		Vector2(210.492264, 248.774689),
		Vector2(294.906464, 251.637314),
		Vector2(249.470505, 328.202148)
	});*/
	/*navmeshComponent->LoadPoints( std::vector<Vector2> { Vector2(291.720337f, 323.941772f), Vector2(231.952881f, 289.461945f),
		Vector2(357.774597, 380.449829) } );*/
	//navmeshComponent->LoadPoints(std::vector<Vector2> {Vector2(384.026611, 255.885498), Vector2(316.727173, 296.194336), Vector2(218.359940, 343.644531)});
	//navmeshComponent->LoadPoints(testPoints);

	superTri = navmeshComponent->CalculateSuperTriangle();
	navmeshComponent->GenerateDelaunayTriangles();

	AStarGraph* graph = navmeshComponent->GetAStarGraph();
	graph->GetPath(graph->GetNodes()[rand() % graph->GetNodes().size()], graph->GetNodes()[rand() % graph->GetNodes().size()]);

	//navmeshComponent->GenerateDelaunayTriangles();

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
	//srand(time(NULL));
	srand(1710452288);

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
