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

Vector2 startOfPath = Vector2(50, 10);

std::vector<Vector2> notSmoothNavMeshPath;
std::vector<Vector2> smoothNavMeshPath;


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


void UpdateNavMesh()
{
	if (IsKeyPressed(KeyboardKey::KEY_SPACE))
	{
		startOfPath = { GetMousePosition().x, GetMousePosition().y };
	}

	if(IsMouseButtonDown(MouseButton::MOUSE_BUTTON_RIGHT))
	{
		notSmoothNavMeshPath = ((NavMesh*)navmesh.GetComponent(ComponentID::NAVMESH))->CalculatePathWithoutSmoothing(
			startOfPath, { GetMousePosition().x, GetMousePosition().y });
	}
	else
	{
		notSmoothNavMeshPath = std::vector<Vector2>();
	}

	if(IsMouseButtonDown(MouseButton::MOUSE_BUTTON_LEFT))
	{
		smoothNavMeshPath = ((NavMesh*)navmesh.GetComponent(ComponentID::NAVMESH))->CalculatePathWithSmoothing(
			startOfPath, { GetMousePosition().x, GetMousePosition().y });
	}
	else
	{
		smoothNavMeshPath = std::vector<Vector2>();
	}
}


void Update()
{
	testObj.Update(GetFrameTime());

	navmesh.Update(GetFrameTime());

	UpdateNavMesh();

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

	for (int i = 1; i < notSmoothNavMeshPath.size(); i++)
	{
		ShapeDrawing2D::DrawCircle(notSmoothNavMeshPath[i], 3, Color::BLUE);
		ShapeDrawing2D::DrawLine(notSmoothNavMeshPath[i - 1], notSmoothNavMeshPath[i], 5, Color::RED);
	}

	for(int i = 1; i < smoothNavMeshPath.size(); i++)
	{
		ShapeDrawing2D::DrawCircle(smoothNavMeshPath[i], 7, Color::ORANGE);
		ShapeDrawing2D::DrawLine(smoothNavMeshPath[i - 1], smoothNavMeshPath[i], 10, Color::PURPLE);
	}

	/*if(navMeshPath.size() >= 2)
	{
		ShapeDrawing2D::DrawLine(navMeshPath[0], navMeshPath[navMeshPath.size() - 1], 10, Color::BLACK);
	}*/

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

	NavMesh* navmeshComponent = navmesh.CreateComponent<NavMesh>()->Init(5, Color::BLACK, true, 2, Color::WHITE, true,
		5.0f, Color::RED, true, true, false);

	//navmeshComponent->GenerateRandomPoints(20, Vector2(5, 5), Vector2(595, 595));

	SquareNavMeshObstacle squareObstacle1 = SquareNavMeshObstacle(Vector2(225, 225));
	squareObstacle1.color = Color::RED;

	SquareNavMeshObstacle squareObstacle2 = SquareNavMeshObstacle(Vector2(400, 400));
	squareObstacle2.color = Color::RED;

	SquareNavMeshObstacle squareObstacle3 = SquareNavMeshObstacle(Vector2(450, 250));
	squareObstacle3.color = Color::RED;

	SquareNavMeshObstacle squareObstacle4 = SquareNavMeshObstacle(Vector2(100, 100));
	squareObstacle4.color = Color::RED;

	SquareNavMeshObstacle squareObstacle5 = SquareNavMeshObstacle(Vector2(50, 400));
	squareObstacle5.color = Color::RED;

	SquareNavMeshObstacle squareObstacle6 = SquareNavMeshObstacle(Vector2(300, 300));
	squareObstacle6.color = Color::RED;

	navmeshComponent->AddObstacle(&squareObstacle1);
	navmeshComponent->AddObstacle(&squareObstacle2);
	navmeshComponent->AddObstacle(&squareObstacle3);
	navmeshComponent->AddObstacle(&squareObstacle4);
	navmeshComponent->AddObstacle(&squareObstacle5);
	navmeshComponent->AddObstacle(&squareObstacle6);

	navmeshComponent->AddPoints(std::vector<Vector2> {Vector2(5, 5), Vector2(595, 5), Vector2(595, 595), Vector2(5, 595)});

	superTri = navmeshComponent->CalculateSuperTriangle();
	navmeshComponent->GenerateDelaunayTriangles();

	AStarGraph* graph = navmeshComponent->GetAStarGraph();

	AStarNode* startNode = graph->GetNodes()[rand() % graph->GetNodes().size()];
	AStarNode* endNode = graph->GetNodes()[rand() % graph->GetNodes().size()];

	std::vector<AStarNode*> path = graph->CalculatePath(startNode, endNode);

	//containingTriangle = navmeshComponent->CalculatePath(Vector2(10, 10), Vector2(100, 100));

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
	srand(time(NULL));
	//srand(1710635000);

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
