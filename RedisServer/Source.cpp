// Server

#include "src/Server.h"
#include "src/Server.h"

#include <iostream>

int main()
{
	std::string host = "127.0.0.1";
	soba::TcpServer server;

	server.InitializeServer(host, 27015);
	server.Run();
}