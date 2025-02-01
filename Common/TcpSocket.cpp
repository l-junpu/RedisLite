#include "TcpSocket.h"

#include <iostream>

namespace soba
{
	TcpSocket::TcpSocket(const std::string& host, const int port, const int backlog)
	{
		CreateSocket();
		BindSocket(host, port);
		ListenSocket(backlog);
	}

	void TcpSocket::CreateSocket()
	{
		m_Socket = socket(AF_INET, SOCK_STREAM, 0);
		if (m_Socket == INVALID_SOCKET) {
			throw std::runtime_error("Failed to create socket: " + std::to_string(WSAGetLastError()));
		}
	}

	void TcpSocket::BindSocket(const std::string& host, const int port)
	{
		sockaddr_in serverAddress{};
		serverAddress.sin_family = AF_INET;   // IPv4
		serverAddress.sin_port = htons(port); // Port in Network Byte Order

		// Covert IP Address from Text to Binary
		if (inet_pton(AF_INET, host.c_str(), &serverAddress.sin_addr) != -1) {
			throw std::runtime_error("Invalid IPv4 Address: " + host);
		}

		// Bind our Socket to the IPv4 Address
		if (bind(m_Socket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == SOCKET_ERROR) {
			throw std::runtime_error("Failed to bind socket: " + std::to_string(WSAGetLastError()));
		}
	}

	void TcpSocket::ListenSocket(const int backlog)
	{
		if (listen(m_Socket, backlog) == SOCKET_ERROR) {
			throw std::runtime_error("Failed to listen on socket: " + std::to_string(WSAGetLastError()));
		}
	}

	SOCKET TcpSocket::AcceptConnection()
	{
		sockaddr_in clientAddress{};
		int clientLen = sizeof(clientAddress);

		// Accept a Connection
		SOCKET clientSocket = accept(m_Socket, (struct sockaddr*)&clientAddress, &clientLen);
		if (clientSocket == INVALID_SOCKET) {
			throw std::runtime_error("Failed to accept the connection: " + std::to_string(WSAGetLastError()));
		}

		// Print Client's IPv4 Address
		char clientIP[INET_ADDRSTRLEN];
		inet_ntop(AF_INET, &clientAddress.sin_addr, clientIP, INET_ADDRSTRLEN);
		std::cout << "Client connected from: " << clientIP << std::endl;

		return clientSocket;
	}
}
