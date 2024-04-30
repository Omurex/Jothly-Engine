#pragma once
#include "socklib.h"
#include "SnakeHead.h"


namespace jothly
{
	struct SnakeServer
	{
		Socket serverSock;
		char buffer[4096];

		GameObject player1;
		GameObject player2;

		SnakeServer() : serverSock(Socket::Family::INET, Socket::Type::STREAM)
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
}