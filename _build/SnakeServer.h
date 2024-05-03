#pragma once
#include "socklib.h"
#include "SnakeHead.h"
#include "Input.h"
#include "SpriteRenderer.h"


namespace jothly
{
	struct SnakeServer
	{
		Socket serverSock;
		char buffer[4096];

		GameObject player1;
		GameObject player2;

		SnakeHead* player1Snake;
		SnakeHead* player2Snake;

		Socket player1Socket;
		Socket player2Socket;

		bool player1Connected = false;
		bool player2Connected = false;

		Texture* snakeHeadTexture;
		Texture* snakeBodyTexture;

		bool gameOver = false;
		bool player1Win = false;

		bool shouldRestart = false;

		Vector2 screenSize;

		float timePassedSinceLastGrow = 0;
		float timeForGrowth = 0;


		SnakeServer()
		{
			// WaitForConnections
		}


		void ResetSnakePositions()
		{
			player1.transform.pos = Vector2(screenSize.x / 3, screenSize.y / 2);
			player2.transform.pos = Vector2(screenSize.x * 2 / 3, screenSize.y / 2);
		}


		void Init(Texture* _snakeHeadTexture, Texture* _snakeBodyTexture, Vector2 _screenSize, float _timeForGrowth)
		{
			serverSock.Create(Socket::Family::INET, Socket::Type::STREAM);

			serverSock.Bind(Address("127.0.0.1", 5643));
			serverSock.Listen();

			snakeHeadTexture = _snakeHeadTexture;
			snakeBodyTexture = _snakeBodyTexture;

			screenSize = _screenSize;
			timeForGrowth = _timeForGrowth;

			std::cout << "Waiting for connections..." << std::endl;

			serverSock.AcceptInto(player1Socket);
			player1Socket.Send("0", 1);
			player1Connected = true;

			std::cout << "Player 1 connected!" << std::endl;

			serverSock.AcceptInto(player2Socket);
			player2Socket.Send("1", 1);
			player2Connected = true;

			std::cout << "Player 2 connected!" << std::endl;

			ResetSnakePositions();

			SetUpSnake(player1, true, &player1Snake);
			SetUpSnake(player2, false, &player2Snake);
		}


		void SetUpSnake(GameObject& obj, bool player1, SnakeHead** out_snakeHeadVar)
		{
			*out_snakeHeadVar = obj.CreateComponent<SnakeHead>()->Init(snakeHeadTexture, snakeBodyTexture, player1);
		}


		void TestConnect()
		{
			if ((player1Connected == false && Input::GetKeyJustPressed(KeyCode::NUM_1)) || shouldRestart)
			{
				player1Connected = true;
				SetUpSnake(player1, true, &player1Snake);
			}

			if ((player2Connected == false && Input::GetKeyJustPressed(KeyCode::NUM_2)) || shouldRestart)
			{
				player2Connected = true;
				SetUpSnake(player2, false, &player2Snake);
			}

			shouldRestart = false;
		}


		void RestartGame()
		{
			if (!shouldRestart) return;

			SetUpSnake(player1, true, &player1Snake);

			SetUpSnake(player2, false, &player2Snake);

			shouldRestart = false;
		}


		void CheckForSnakeDead()
		{
			if (player1Snake->CheckIfHeadCollidingWithSnake(player1Snake) || player1Snake->CheckIfHeadCollidingWithSnake(player2Snake) ||
				player1.transform.pos.x < 0 || player1.transform.pos.x > screenSize.x || player1.transform.pos.y < 0 || player1.transform.pos.y > screenSize.y)
			{
				std::cout << "PLAYER 1 DIED" << std::endl;
				gameOver = true;
				player1Win = false;
			}
			else if (player2Snake->CheckIfHeadCollidingWithSnake(player1Snake) || player2Snake->CheckIfHeadCollidingWithSnake(player2Snake) ||
				player2.transform.pos.x < 0 || player2.transform.pos.x > screenSize.x || player2.transform.pos.y < 0 || player2.transform.pos.y > screenSize.y)
			{
				std::cout << "PLAYER 2 DIED" << std::endl;
				gameOver = true;
				player1Win = true;
			}

			if (gameOver)
			{
				if (player1Win)
				{
					player2Snake->SetEnabled(false);
				}
				else
				{
					player1Snake->SetEnabled(false);
				}
			}
		}


		void CheckForRestart()
		{
			if (!Input::GetKeyJustPressed(KeyCode::SPACE)) return;

			player1.DestroyAllComponents();
			player2.DestroyAllComponents();

			shouldRestart = true;
			gameOver = false;

			timePassedSinceLastGrow = 0;

			ResetSnakePositions();
		}


		Vector2 GetInputFromPlayer()
		{
			//int numBytesRecvd = serverSock.Recv(buffer, sizeof(buffer));

			//serverSock.AcceptInto(player1Socket);
			//int numBytesRecvd = player1Socket.Recv(buffer, sizeof(buffer));

			//if (numBytesRecvd == -1) // Some sort of error
			//{
			//	int errCode = serverSock.GetLastError();
			//	if (errCode != Socket::Error::SOCKLIB_ETIMEDOUT)
			//	{
			//		std::cerr << "Unexpected error, terminating" << std::endl;
			//		abort();
			//	}
			//}
			//else if (numBytesRecvd == 0) // Connection closed
			//{
			//	std::cerr << "Unexpected connection closure, terminating" << std::endl;
			//	abort();
			//}

			std::string message = "hello world, constant connection";
			int numBytesRecvd = player1Socket.Recv(buffer, sizeof(buffer));
			//player1Socket.Send(message.c_str(), message.size());

			return Vector2(0);
		}


		void Update(float dt)
		{
			//WaitForConnections();

			std::cout << "PLAYER 1 RECVD: " << GetInputFromPlayer().ToString() << std::endl;

			if (player1Connected && player2Connected)
			{
				if (!gameOver)
				{
					player1.Update(dt);
					player2.Update(dt);
					CheckForSnakeDead();
				}
				else
				{
					CheckForRestart();
				}

				timePassedSinceLastGrow += dt;
				if (timePassedSinceLastGrow > timeForGrowth)
				{
					player1Snake->GrowSnake();
					player2Snake->GrowSnake();
					timePassedSinceLastGrow = 0;
				}
			}
		}


		void Draw() // Note: This is for debugging what's happeniing on the server, theoretically don't
		{
			if (player1Connected && player2Connected)
			{
				player1.Draw();
				player2.Draw();
			}
		}
	};
}