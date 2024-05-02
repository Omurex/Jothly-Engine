#pragma once
#include "socklib.h"
#include "Vector2.h"
#include "Input.h"


namespace jothly
{
	struct SnakeClient
	{
		char buffer[4096];

		Socket sock;

		KeyCode up, down, left, right;

		int playerNum = -1;


		SnakeClient() {}

		
		void Init(KeyCode _up, KeyCode _down, KeyCode _left, KeyCode _right)
		{
			sock.Create(Socket::Family::INET, Socket::Type::STREAM);
			sock.Connect(Address("127.0.0.1", 5643));

			up = _up;
			down = _down;
			left = _left;
			right = _right;

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


		void Update(float dt)
		{
			int numBytesRecvd = sock.Recv(buffer, sizeof(buffer));

			if (numBytesRecvd == -1) // Some sort of error
			{
				int errCode = sock.GetLastError();
				if (errCode != Socket::Error::SOCKLIB_ETIMEDOUT)
				{
					std::cerr << "Unexpected error, terminating" << std::endl;
					abort();
				}
			}
			else if (numBytesRecvd == 0) // Connection closed
			{
				std::cerr << "Unexpected connection closure, terminating" << std::endl;
				abort();
			}
			else
			{
				std::cout << numBytesRecvd << std::endl;
			}
		}


		void Draw()
		{

		}
	};
}