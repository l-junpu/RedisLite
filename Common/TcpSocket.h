#ifndef SOBA_SOCKET_5
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

		// Server Use Only
		SOCKET AcceptConnectionFromClient();

		// Client Use Only
		void EstablishConnectionToServer(const std::string& host, const int port);
		
		// Socket Management
		void CreateSocket();
		void BindSocket(const std::string& host, const int port);
		void ListenSocket(const int backlog = 5);

		SOCKET GetSocket() const;

	private:

		SOCKET m_Socket;
	};
}

#endif