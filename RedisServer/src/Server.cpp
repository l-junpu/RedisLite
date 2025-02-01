#include "Server.h"

#include <thread>
#include <iostream>

namespace soba
{
	void TcpServer::InitializeServer(const std::string& host, const int port, const int backlog)
	{
		// Initialize Winsock
		WSADATA wsaData;
		if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
			throw std::runtime_error("WSAStartup failed: " + std::to_string(WSAGetLastError()));
		}

		m_ServerSocket.CreateSocket();
		m_ServerSocket.BindSocket(host, port);
		m_ServerSocket.ListenSocket(backlog);
	}

	void TcpServer::Run()
	{
		try {
			while (true) {
				SOCKET clientSocket = m_ServerSocket.AcceptConnectionFromClient();
				std::thread clientThread(&Cache::HandleUserRequest, &m_DatabaseLite, clientSocket);
				clientThread.detach();

				// Note that we still have not closed the client socket yet, still thinking of where
				// is the best place for it - Probably in cache where we shut down the clientSocket
				// at the same time we can use that to break out of the thread
				// Remember to use to_lower() to cast command before comparing
			}
		}
		catch (const std::exception& e) {
			std::cerr << "Server error: " << e.what() << std::endl;
		}

		WSACleanup();
	}
}