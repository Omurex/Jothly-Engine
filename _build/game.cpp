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
#include "NavMeshAgent.h"
#include "TicTacToeBoard.h"


using namespace jothly;


// WFC Variables
GameObject wfcObject = GameObject("WFC Object", Vector3(0, 0, 0), Quaternion::Quaternion2D(0), Vector3(1, 1));
Texture testTex;
WaveFunctionCollapseGrid* wfcGrid;
Texture smallBlackDot;

// NavMesh Variables
GameObject navMeshAgent = GameObject("NavMeshAgent", Vector2(200, 100), Quaternion::Quaternion2D(0), Vector2(1));
NavMeshAgent* navMeshAgentComponent = nullptr;
DelaunayTriangle tri;
DelaunayTriangle superTri;
GameObject navMesh;
Vector2 startOfPath = Vector2(50, 10);
std::vector<Vector2> notSmoothNavMeshPath;
std::vector<Vector2> smoothNavMeshPath;
SquareNavMeshObstacle squareObstacle1;
SquareNavMeshObstacle squareObstacle2;
SquareNavMeshObstacle squareObstacle3;
SquareNavMeshObstacle squareObstacle4;
SquareNavMeshObstacle squareObstacle5;
SquareNavMeshObstacle squareObstacle6;

GameObject ticTacToeObject = GameObject("Tic Tac Toe Object", Vector2(300, 300), Quaternion::Quaternion2D(0), Vector2(1));
TicTacToeBoard* ticTacToe = nullptr;


void UpdateWFC()
{
	wfcObject.Update(GetFrameTime());

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
	navMesh.Update(GetFrameTime());
	navMeshAgent.Update(GetFrameTime());

	if(IsMouseButtonDown(MouseButton::MOUSE_BUTTON_RIGHT))
	{
		notSmoothNavMeshPath = ((NavMesh*)navMesh.GetComponent(ComponentID::NAVMESH))->CalculatePathWithoutSmoothing(
			navMeshAgent.transform.pos, { GetMousePosition().x, GetMousePosition().y }, false);
	}
	else
	{
		notSmoothNavMeshPath = std::vector<Vector2>();
	}

	if(IsMouseButtonDown(MouseButton::MOUSE_BUTTON_LEFT))
	{
		smoothNavMeshPath = ((NavMesh*)navMesh.GetComponent(ComponentID::NAVMESH))->CalculatePathWithSmoothing(
			navMeshAgent.transform.pos, { GetMousePosition().x, GetMousePosition().y }, false);
	}
	else
	{
		smoothNavMeshPath = std::vector<Vector2>();
	}

	if (IsKeyDown(KeyboardKey::KEY_SPACE))
	{
		navMeshAgentComponent->SetDestination({ GetMousePosition().x, GetMousePosition().y });
	}
}


void Update()
{
	//UpdateWFC();
	UpdateNavMesh();

	//ticTacToeObject.Update(GetFrameTime());
}


void InitWFC()
{
	Texture ld = Texture(con::RESOURCE_PATH + "ld.png");
	Texture lu = Texture(con::RESOURCE_PATH + "lu.png");
	Texture ru = Texture(con::RESOURCE_PATH + "ru.png");
	Texture rd = Texture(con::RESOURCE_PATH + "rd.png");

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

	wfcGrid = wfcObject.CreateComponent<WaveFunctionCollapseGrid>()->Init(templateTiles, Vector2(0, 0), Vector2(GetScreenWidth(), GetScreenHeight()));

	wfcGrid->GenerateInitialGrid(20, 20);
	wfcGrid->InitializeGeneration();
}


void InitNavMesh()
{
	NavMesh* navMeshComponent = navMesh.CreateComponent<NavMesh>()->Init(5, Color::BLACK, true, 2, Color::WHITE, true,
		5.0f, Color::RED, true, true, false);

	squareObstacle1 = SquareNavMeshObstacle(Vector2(225, 225));
	squareObstacle1.color = Color::RED;

	squareObstacle2 = SquareNavMeshObstacle(Vector2(400, 400));
	squareObstacle2.color = Color::RED;

	squareObstacle3 = SquareNavMeshObstacle(Vector2(450, 250));
	squareObstacle3.color = Color::RED;

	squareObstacle4 = SquareNavMeshObstacle(Vector2(100, 100));
	squareObstacle4.color = Color::RED;

	squareObstacle5 = SquareNavMeshObstacle(Vector2(50, 400));
	squareObstacle5.color = Color::RED;

	squareObstacle6 = SquareNavMeshObstacle(Vector2(450, 300));
	squareObstacle6.color = Color::RED;

	navMeshComponent->AddObstacle(&squareObstacle1);
	navMeshComponent->AddObstacle(&squareObstacle2);
	navMeshComponent->AddObstacle(&squareObstacle3);
	navMeshComponent->AddObstacle(&squareObstacle4);
	navMeshComponent->AddObstacle(&squareObstacle5);
	navMeshComponent->AddObstacle(&squareObstacle6);

	navMeshComponent->AddPoints(std::vector<Vector2> {Vector2(5, 5), Vector2(595, 5), Vector2(595, 595), Vector2(5, 595)});

	superTri = navMeshComponent->CalculateSuperTriangle();
	navMeshComponent->GenerateDelaunayTriangles();

	AStarGraph* graph = navMeshComponent->GetAStarGraph();

	AStarNode* startNode = graph->GetNodes()[rand() % graph->GetNodes().size()];
	AStarNode* endNode = graph->GetNodes()[rand() % graph->GetNodes().size()];

	std::vector<AStarNode*> path = graph->CalculatePath(startNode, endNode);

	navMeshAgent.transform.scale = Vector2(.3f);
	navMeshAgent.CreateComponent<SpriteRenderer>()->Init(&smallBlackDot);
	navMeshAgentComponent = navMeshAgent.CreateComponent<NavMeshAgent>()->Init(navMeshComponent, 100);
}


void DrawWFC()
{
	wfcObject.Draw();
}


void DrawNavMesh()
{
	navMesh.Draw();
	navMeshAgent.Draw();

	for (int i = 1; i < notSmoothNavMeshPath.size(); i++)
	{
		ShapeDrawing2D::DrawCircle(notSmoothNavMeshPath[i], 3, Color::BLUE);
		ShapeDrawing2D::DrawLine(notSmoothNavMeshPath[i - 1], notSmoothNavMeshPath[i], 5, Color::RED);
	}

	for (int i = 1; i < smoothNavMeshPath.size(); i++)
	{
		ShapeDrawing2D::DrawCircle(smoothNavMeshPath[i], 7, Color::ORANGE);
		ShapeDrawing2D::DrawLine(smoothNavMeshPath[i - 1], smoothNavMeshPath[i], 10, Color::PURPLE);
	}
}



void Draw()
{
	//ticTacToeObject.Draw();

	//DrawWFC();
	DrawNavMesh();
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
	
	Texture ticTacToeXTex = Texture(con::RESOURCE_PATH + "TicTacToeX.png");
	Texture ticTacToeOTex = Texture(con::RESOURCE_PATH + "TicTacToeO.png");

	ticTacToe = ticTacToeObject.CreateComponent<TicTacToeBoard>()->Init(&ticTacToeXTex, &ticTacToeOTex);
	ticTacToe->PlaceSquare(0, 2, false);
	ticTacToe->PlaceSquare(1, 1, true);
	ticTacToe->PlaceSquare(2, 0, true);
	ticTacToe->PlaceSquare(0, 1, false);
	ticTacToe->PlaceSquare(0, 0, true);
	ticTacToe->PlaceSquare(1, 0, false);
	ticTacToe->PlaceSquare(1, 2, true);
	ticTacToe->PlaceSquare(2, 2, false);
	ticTacToe->PlaceSquare(2, 1, false);

	TTTResult gameResult = ticTacToe->CheckForEndOfGame();
	std::cout << gameResult;

	//InitWFC();
	InitNavMesh();

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
	//srand(1710794466);

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
