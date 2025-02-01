#include "Server.h"

#include <thread>
#include <iostream>

namespace soba
{
	TcpServer::TcpServer(const std::string& host, const int port, const int backlog) :
		m_ServerSocket(host, port, backlog)
	{ }

	void TcpServer::Run()
	{
		try {
			WSADATA wsaData;
			if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
				throw std::runtime_error("WSAStartup failed: " + std::to_string(WSAGetLastError()));
			}

			while (true) {
				SOCKET clientSocket = m_ServerSocket.AcceptConnection();
				std::thread clientThread(&Cache::HandleUserRequest, &m_DatabaseLite, clientSocket);
				clientThread.detach();

				// Note that we still have not closed the client socket yet, still thinking of where
				// is the best place for it - Probably in cache where we shut down the clientSocket
			}
		}
		catch (const std::exception& e) {
			std::cerr << "Server error: " << e.what() << std::endl;
		}

		WSACleanup();
	}
}