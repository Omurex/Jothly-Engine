#pragma once
#include "socklib.h"
#include "SnakeHead.h"
#include "Input.h"
#include "SpriteRenderer.h"
#include "StringFunctions.h"


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
			player1Socket.SetNonBlockingMode(true);
			player1Connected = true;

			std::cout << "Player 1 connected!" << std::endl;

			serverSock.AcceptInto(player2Socket);
			player2Socket.Send("1", 1);
			player2Socket.SetNonBlockingMode(true);
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

				std::string message = "DEAD";
				player1Socket.Send(message.data(), message.size());
				player2Socket.Send(message.data(), message.size());
			}
		}


		bool GetSocketRecv(Socket& socket, std::string& out_str) // True if successful
		{
			int numBytesRecvd = socket.Recv(buffer, sizeof(buffer));

			if (numBytesRecvd == -1) // Some sort of error
			{
				int errCode = socket.GetLastError();
				if (errCode != Socket::Error::SOCKLIB_ETIMEDOUT)
				{
					std::cerr << "Unexpected error, terminating" << std::endl;
					abort();
				}
				else
				{
					return false;
				}
			}
			else if (numBytesRecvd == 0) // Connection closed
			{
				std::cerr << "Unexpected connection closure, terminating" << std::endl;
				abort();
			}
			else
			{
				out_str = std::string(buffer, numBytesRecvd);
				return true;
			}
		}


		Vector2 GetMoveInputFromPlayer(Socket& playerSocket)
		{
			Vector2 input = Vector2(0);
			std::string recvdStr;

			if(GetSocketRecv(playerSocket, recvdStr))
			{
				std::vector<std::string> strInput = SplitByDelimiter(recvdStr, "|");
				char* end;

				if (strInput.size() == 2)
				{
					input = Vector2(strtof(strInput[0].data(), &end), strtof(strInput[1].data(), &end));
				}

			}

			return input;
		}


		bool GetRestartSignal(Socket& playerSocket)
		{
			std::string recvdStr;

			if (GetSocketRecv(playerSocket, recvdStr))
			{
				if (recvdStr == "RESTART")
				{
					return true;
				}
			}

			return false;
		}


		void CheckForRestart()
		{
			//if (!Input::GetKeyJustPressed(KeyCode::SPACE)) return;

			if(!GetRestartSignal(player1Socket) && !GetRestartSignal(player2Socket)) return;

			player1.DestroyAllComponents();
			player2.DestroyAllComponents();

			SetUpSnake(player1, true, &player1Snake);
			SetUpSnake(player2, false, &player2Snake);

			gameOver = false;

			std::string message = "RESTART";
			player1Socket.Send(message.data(), message.size());
			player2Socket.Send(message.data(), message.size());

			timePassedSinceLastGrow = 0;

			ResetSnakePositions();
		}


		std::string CreateSnakeVisualString()
		{
			std::string ret = "";
			ret += "PLAYER1|";
			ret += player1Snake->CreateVisualRepresentationString();
			ret += "|PLAYER2|";
			ret += player2Snake->CreateVisualRepresentationString();

			return ret;
		}


		void Update(float dt)
		{
			//WaitForConnections();

			if (player1Connected && player2Connected)
			{
				if (!gameOver)
				{
					Vector2 player1Input = GetMoveInputFromPlayer(player1Socket);
					Vector2 player2Input = GetMoveInputFromPlayer(player2Socket);

					std::cout << "PLAYER 1 RECVD: " << GetMoveInputFromPlayer(player1Socket).ToString() << std::endl;
					std::cout << "PLAYER 2 RECVD: " << GetMoveInputFromPlayer(player2Socket).ToString() << std::endl;

					player1Snake->UpdateVelocityFromInput(player1Input, dt);
					player2Snake->UpdateVelocityFromInput(player2Input, dt);


					player1.Update(dt);
					player2.Update(dt);
					CheckForSnakeDead();

					timePassedSinceLastGrow += dt;
					if (timePassedSinceLastGrow > timeForGrowth)
					{
						player1Snake->GrowSnake();
						player2Snake->GrowSnake();
						timePassedSinceLastGrow = 0;
					}

					// SEND SNAKE POS DATA
					std::string message = CreateSnakeVisualString();
					player1Socket.Send(message.data(), message.size());
					player2Socket.Send(message.data(), message.size());
				}
				else
				{
					CheckForRestart();
				}
			}
		}


		void Draw() // Note: This is for debugging what's happening on the server, theoretically don't need to draw on server
		{
			if (player1Connected && player2Connected)
			{
				player1.Draw();
				player2.Draw();
			}
		}
	};
}