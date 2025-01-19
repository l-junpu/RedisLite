#include "Server.h"

#include <thread>
#include <iostream>

namespace soba
{
	TcpServer::TcpServer(HandleUserRequest requestHandler, Cache* cache) :
		m_Socket{ NULL },
		m_ServerSocket{ INVALID_SOCKET },
		m_ActiveServer{ true },
		m_Cache{ cache },
		m_HandleUserRequest{ requestHandler }
	{ }

	bool TcpServer::Initialize()
	{
		if (!InitializeWSAStartup()) return false;
		if (!CreateServerSocket())   return false;
		if (!ListenToConnections())  return false;

		return true;
	}

	void TcpServer::HandleClientConnections()
	{
		while (m_ActiveServer)
		{
			// Attempt to Accept Connection with Client
			SOCKET ClientSocket = accept(m_ServerSocket, NULL, NULL);
			if (ClientSocket == INVALID_SOCKET) {
				std::cout << "Accept Connection failed: " << WSAGetLastError() << std::endl;
				closesocket(m_ServerSocket);
				WSACleanup();
				return;
			}

			std::cout << "Client Connected!" << std::endl;

			// Spawn a Thread to handle any Incoming Requests Persistently
			std::thread ClientThread(m_HandleUserRequest, ClientSocket, m_Cache);
			ClientThread.detach();
		}

		// Graceful Termination
		return;
	}

	bool TcpServer::Terminate()
	{
		return true;
	}

	bool TcpServer::InitializeWSAStartup()
	{
		WSADATA wsaData;
		int status = WSAStartup(MAKEWORD(2, 2), &wsaData);
		if (status != 0) {
			std::cout << "WSAStartup failed: " << status << std::endl;
			WSACleanup();
			return false;
		}
		return true;
	}

	bool TcpServer::CreateServerSocket()
	{
		int status = 0;

		// Attempt to Create Socket
		addrinfo hints;
		ZeroMemory(&hints, sizeof(hints));
		hints.ai_family = AF_INET;
		hints.ai_socktype = SOCK_STREAM;
		hints.ai_protocol = IPPROTO_TCP;
		hints.ai_flags = AI_PASSIVE;
		status = getaddrinfo(NULL, "27015", &hints, &m_Socket);
		if (status != 0) {
			std::cout << "Getaddrinfo failed: " << status << std::endl;
			WSACleanup();
			return false;
		}

		// Attempt to Create Socket Object
		m_ServerSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (m_ServerSocket == INVALID_SOCKET) {
			std::cout << "Create Socket failed: " << WSAGetLastError() << std::endl;
			WSACleanup();
			return false;
		}

		return true;
	}

	bool TcpServer::ListenToConnections()
	{
		// Attempt to Bind Socket
		int result = bind(m_ServerSocket, m_Socket->ai_addr, (int)m_Socket->ai_addrlen);
		if (result == SOCKET_ERROR) {
			std::cout << "Bind failed: " << WSAGetLastError() << std::endl;
			freeaddrinfo(m_Socket);
			closesocket(m_ServerSocket);
			WSACleanup();
			return false;
		}

		// Listen to Connections
		if (listen(m_ServerSocket, SOMAXCONN) == SOCKET_ERROR) {
			std::cout << "Listen to Connection failed: " << WSAGetLastError() << std::endl;
			closesocket(m_ServerSocket);
			WSACleanup();
			return false;
		}

		std::cout << "Server is now listening on port 27015" << std::endl;

		return true;
	}
}