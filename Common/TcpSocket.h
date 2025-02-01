#ifndef SOBA_SOCKET_H
#define SOBA_SOCKET_H

#include <string>
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "ws2_32.lib") // Link with Winsock library

namespace soba
{
	class TcpSocket
	{
	public:

		TcpSocket(const std::string& host, const int port, const int backlog);

		SOCKET AcceptConnection();
		
	private:

		void CreateSocket();
		void BindSocket(const std::string& host, const int port);
		void ListenSocket(const int backlog);

	private:

		SOCKET m_Socket;
	};
}

#endif