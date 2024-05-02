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

		SnakeServer()
		{
			// WaitForConnections
		}


		void TempInit(Texture* _snakeHeadTexture, Texture* _snakeBodyTexture)
		{
			serverSock.Create(Socket::Family::INET, Socket::Type::STREAM);

			serverSock.Bind(Address("127.0.0.1", 5643));
			serverSock.Listen();

			player1.transform.pos = Vector2(150, 300);
			player2.transform.pos = Vector2(450, 300);

			snakeHeadTexture = _snakeHeadTexture;
			snakeBodyTexture = _snakeBodyTexture;
		}


		void SetUpSnake(GameObject& obj, SnakeHead** out_snakeHeadVar)
		{
			*out_snakeHeadVar = obj.CreateComponent<SnakeHead>()->Init(snakeHeadTexture, snakeBodyTexture);
		}


		void TestConnect()
		{
			if (player1Connected == false && Input::GetKeyJustPressed(KeyCode::NUM_1))
			{
				player1Connected = true;
				SetUpSnake(player1, &player1Snake);
			}

			if (player2Connected == false && Input::GetKeyJustPressed(KeyCode::NUM_2))
			{
				player2Connected = true;
				SetUpSnake(player2, &player2Snake);
			}
		}


		void WaitForConnections()
		{
			
		}


		void Update(float dt)
		{
			TestConnect();

			if (player1Connected && player2Connected)
			{
				player1.Update(dt);
				player2.Update(dt);
				CheckForSnakeDead();
			}
		}


		void CheckForSnakeDead()
		{
			if (player1Snake->CheckIfCollidingWithSnake(player1Snake) || player1Snake->CheckIfCollidingWithSnake(player2Snake))
			{
				std::cout << "PLAYER 1 DIED" << std::endl;
			}
			else if (player2Snake->CheckIfCollidingWithSnake(player1Snake) || player2Snake->CheckIfCollidingWithSnake(player2Snake))
			{
				std::cout << "PLAYER 2 DIED" << std::endl;
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