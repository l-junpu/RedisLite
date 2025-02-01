// Server

#include "src/Server.h"
#include "src/Server.h"

#include <iostream>

int main()
{
	soba::TcpServer server;

	server.InitializeServer("127.0.0.1", 27015);
	server.Run();
}