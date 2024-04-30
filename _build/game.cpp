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
#include "Input.h"
#include "TicTacToePlayer.h"
#include "TicTacToeHumanPlayer.h"
#include "TicTacToeMiniMaxPlayer.h"
#include "socklib.h"


using namespace jothly;


// WFC Variables
GameObject wfcObject = GameObject("WFC Object", Vector3(0, 0, 0), Quaternion::Quaternion2D(0), Vector3(1, 1));
Texture testTex;
WaveFunctionCollapseGrid* wfcGrid;
Texture smallBlackDot;
Texture ld, lu, ru, rd, t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12;
std::vector<WaveFunctionCollapseTile> templateTiles;

// NavMesh Variables
GameObject navMeshAgent = GameObject("NavMeshAgent", Vector2(200, 100), Quaternion::Quaternion2D(0), Vector2(1));
NavMeshAgent* navMeshAgentComponent = nullptr;
DelaunayTriangle tri;
DelaunayTriangle superTri;
GameObject navMesh;
Vector2 startOfPath = Vector2(50, 10);
std::vector<Vector2> notSmoothNavMeshPath;
std::vector<Vector2> smoothNavMeshPath;
SquareNavMeshObstacle squareObstacle1, squareObstacle2, squareObstacle3, squareObstacle4, squareObstacle5, squareObstacle6;

// TicTacToe Variables
GameObject ticTacToeObject = GameObject("Tic Tac Toe Object", Vector2(300, 300), Quaternion::Quaternion2D(0), Vector2(1));
TicTacToeBoard* ticTacToe = nullptr;
TicTacToeHumanPlayer xPlayer;
TicTacToeMiniMaxPlayer oPlayer;

// Networking
Socket sock;


struct Server
{
	Socket serverSock;
	char buffer[4096];

	Server() : serverSock(Socket::Family::INET, Socket::Type::STREAM) 
	{}

	void Update()
	{
		std::string send = "HELLO WORLD";
		serverSock.Bind(Address("127.0.0.1", 5550));
		serverSock.Listen();
		Socket recvdSock;
		serverSock.AcceptInto(recvdSock);
		int recvdBytes = recvdSock.Recv(buffer, sizeof(buffer));
		recvdSock.Send(send.c_str(), send.size());
	}
};



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

	if(Input::GetMouseButtonDown(MouseCode::MB_RIGHT))
	{
		notSmoothNavMeshPath = ((NavMesh*)navMesh.GetComponent(ComponentID::NAVMESH))->CalculatePathWithoutSmoothing(
			navMeshAgent.transform.pos, { GetMousePosition().x, GetMousePosition().y }, false);
	}
	else
	{
		notSmoothNavMeshPath = std::vector<Vector2>();
	}

	if(Input::GetMouseButtonDown(MouseCode::MB_LEFT))
	{
		smoothNavMeshPath = ((NavMesh*)navMesh.GetComponent(ComponentID::NAVMESH))->CalculatePathWithSmoothing(
			navMeshAgent.transform.pos, { GetMousePosition().x, GetMousePosition().y }, false);
	}
	else
	{
		smoothNavMeshPath = std::vector<Vector2>();
	}

	if (Input::GetKeyDown(KeyCode::SPACE))
	{
		navMeshAgentComponent->SetDestination({ GetMousePosition().x, GetMousePosition().y });
	}
}


void Update()
{
	//UpdateWFC();
	//UpdateNavMesh();

	ticTacToeObject.Update(GetFrameTime());
}


void InitWFC()
{
	ld = Texture(con::RESOURCE_PATH + "ld.png");
	lu = Texture(con::RESOURCE_PATH + "lu.png");
	ru = Texture(con::RESOURCE_PATH + "ru.png");
	rd = Texture(con::RESOURCE_PATH + "rd.png");

	// NOTE: MAKE TEXTURE MANAGER, BADLY NEEDED
	t0 = Texture(con::RESOURCE_PATH + "coding-train/0.png");
	t1 = Texture(con::RESOURCE_PATH + "coding-train/1.png");
	t2 = Texture(con::RESOURCE_PATH + "coding-train/2.png");
	t3 = Texture(con::RESOURCE_PATH + "coding-train/3.png");
	t4 = Texture(con::RESOURCE_PATH + "coding-train/4.png");
	t5 = Texture(con::RESOURCE_PATH + "coding-train/5.png");
	t6 = Texture(con::RESOURCE_PATH + "coding-train/6.png");
	t7 = Texture(con::RESOURCE_PATH + "coding-train/7.png");
	t8 = Texture(con::RESOURCE_PATH + "coding-train/8.png");
	t9 = Texture(con::RESOURCE_PATH + "coding-train/9.png");
	t10 = Texture(con::RESOURCE_PATH + "coding-train/10.png");
	t11 = Texture(con::RESOURCE_PATH + "coding-train/11.png");
	t12 = Texture(con::RESOURCE_PATH + "coding-train/12.png");

	templateTiles = std::vector<WaveFunctionCollapseTile>
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
	ticTacToeObject.Draw();

	//DrawWFC();
	//DrawNavMesh();
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
	/*ticTacToe->PlaceSquare(0, 2, false);
	ticTacToe->PlaceSquare(1, 1, true);
	ticTacToe->PlaceSquare(2, 0, true);
	ticTacToe->PlaceSquare(0, 1, false);
	ticTacToe->PlaceSquare(0, 0, true);
	ticTacToe->PlaceSquare(1, 0, false);
	ticTacToe->PlaceSquare(1, 2, true);
	ticTacToe->PlaceSquare(2, 2, false);
	ticTacToe->PlaceSquare(2, 1, false);*/

	oPlayer.SetMaxDepth(100);
	ticTacToe->SetPlayers(&xPlayer, &oPlayer);

	//InitWFC();
	//InitNavMesh();

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
	SockLibInit();
	srand(time(NULL));
	//srand(1710794466);

	std::cout << "SEED: " + std::to_string(time(NULL)) << std::endl;

	char buffer[4096];
	std::string sendStr = "Hello World!";

	/*std::string input;
	std::cin >> input;*/

	// NOT FIXED, ASK FOR HELP
	//if (input == "0") // Server
	//{
	//	Server server;
	//	server.Update();
	//}
	//else
	//{
	//	std::string send = "hello world";
	//	sock.Create(Socket::Family::INET, Socket::Type::STREAM);
	//	sock.Connect(Address("127.0.0.1", 5550));
	//	sock.Send(send.c_str(), send.size());
	//	int recvdBytes = sock.Recv(buffer, sizeof(buffer));
	//	std::string recvd(buffer, recvdBytes);
	//	std::cout << recvd << std::endl;
	//}

	// Initialize resource path
	std::string resourcePath = argv[0];
	int lastSection = resourcePath.find_last_of('\\');
	resourcePath = resourcePath.substr(0, lastSection);
	std::replace(resourcePath.begin(), resourcePath.end(), '\\', '/');
	resourcePath += "/../../resources/";
	con::RESOURCE_PATH = resourcePath;


	Init();

	SockLibShutdown();

	return 0;
}
