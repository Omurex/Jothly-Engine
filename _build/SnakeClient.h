#pragma once
#include "socklib.h"
#include "Vector2.h"
#include "Input.h"
#include "TextureDrawing.h"


namespace jothly
{
	struct SnakeClient
	{
		char buffer[4096];
		
		// Index 0 is head
		std::vector<Vector2> player1Positions;
		std::vector<Vector2> player2Positions;

		Texture* snakeHeadTex = nullptr;
		Texture* snakeBodyTex = nullptr;

		Socket sock;

		KeyCode up, down, left, right;

		int playerNum = -1;

		bool gameOver = false;


		SnakeClient() {}

		
		void Init(KeyCode _up, KeyCode _down, KeyCode _left, KeyCode _right, Texture* _snakeHeadTex, Texture* _snakeBodyTex)
		{
			sock.Create(Socket::Family::INET, Socket::Type::STREAM);
			sock.Connect(Address("127.0.0.1", 5643));

			up = _up;
			down = _down;
			left = _left;
			right = _right;

			snakeHeadTex = _snakeHeadTex;
			snakeBodyTex = _snakeBodyTex;

			do
			{
				std::string notification = "NEW PLAYER";
				sock.Send(notification.c_str(), notification.length());

				std::cout << "Waiting to connect..." << std::endl;

				int numBytesRecvd = sock.Recv(buffer, sizeof(buffer));
				std::string recvd(buffer, numBytesRecvd);

				const char* beg = recvd.c_str();
				char* end;
				int possiblePlayerNum = strtol(beg, &end, 10);

				if (beg != end && beg + recvd.size() == end && (possiblePlayerNum == 0 || possiblePlayerNum == 1)) // Make sure just number was given back
				{
					playerNum = possiblePlayerNum;
				}

			} while (playerNum < 0);
			
			std::cout << "Player Num: " << playerNum << std::endl;

			sock.SetNonBlockingMode(true);
		}


		Vector2 GetMoveInput()
		{
			Vector2 input;

			if (Input::GetKeyDown(up))
			{
				input += Vector2(0, -1);
			}

			if (Input::GetKeyDown(down))
			{
				input += Vector2(0, 1);
			}

			if (Input::GetKeyDown(left))
			{
				input += Vector2(-1, 0);
			}

			if (Input::GetKeyDown(right))
			{
				input += Vector2(1, 0);
			}

			return input;
		}


		bool GetRestartInput()
		{
			if (Input::GetKeyJustPressed(KeyCode::SPACE))
			{
				return true;
			}

			return false;
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


		void ConvertStringToBodyPositions(std::string str)
		{
			std::vector<std::string> subStrs = SplitByDelimiter(str, "|");

			player1Positions.clear();
			player2Positions.clear();

			std::vector<Vector2>* positions = &player1Positions;

			if(subStrs.size() < 1 || subStrs[0] != "PLAYER1") return;

			for (int i = 1; i < subStrs.size() - 1;)
			{
				if (subStrs[i] == "PLAYER2")
				{
					positions = &player2Positions;
					i++;
				}
				else
				{
					char* end;
					positions->push_back(Vector2(strtof(subStrs[i].data(), &end), strtof(subStrs[i + 1].data(), &end)));
					i += 2;
				}
			}
		}


		void Update(float dt)
		{
			//int numBytesRecvd = sock.Recv(buffer, sizeof(buffer));

			//if (numBytesRecvd == -1) // Some sort of error
			//{
			//	int errCode = sock.GetLastError();
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
			//else
			//{
			//	std::cout << numBytesRecvd << std::endl;
			//}

			if (!gameOver)
			{
				Vector2 input = GetMoveInput();
				std::string sendStr = std::to_string(input.x) + "|" + std::to_string(input.y);
				sock.Send(sendStr.c_str(), sendStr.size());

				std::string message;
				if (GetSocketRecv(sock, message))
				{
					if (message == "DEAD")
					{
						gameOver = true;
					}
					else
					{
						ConvertStringToBodyPositions(message);
					}
				}
			}
			else
			{
				// Poll for space
				if (GetRestartInput())
				{
					std::string message = "RESTART";
					sock.Send(message.data(), message.size());
				}

				std::string message;
				if (GetSocketRecv(sock, message) && message == "RESTART")
				{
					gameOver = false;
				}
			}

			
		}


		void Draw()
		{

			Vector2 headHalfSize = snakeHeadTex->GetSize() / 2.0f;
			Vector2 bodyHalfSize = snakeBodyTex->GetSize() / 2.0f;

			if (player1Positions.size() > 0) TextureDrawing::DrawTexture(*snakeHeadTex, player1Positions[0], headHalfSize);
			if (player2Positions.size() > 0) TextureDrawing::DrawTexture(*snakeHeadTex, player2Positions[0], headHalfSize);

			for (int i = 1; i < player1Positions.size(); i++)
			{
				TextureDrawing::DrawTexture(*snakeBodyTex, player1Positions[i], bodyHalfSize);
			}

			for (int i = 1; i < player2Positions.size(); i++)
			{
				TextureDrawing::DrawTexture(*snakeBodyTex, player2Positions[i], bodyHalfSize);
			}
		}
	};
}