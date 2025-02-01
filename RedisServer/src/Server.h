#ifndef SOBA_SERVER_H
#define SOBA_SERVER_H

#include "Cache.h"
#include "Common/TcpSocket.h"

#include <string>
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "Ws2_32.lib")

namespace soba
{
	class TcpServer
	{
	public:

		TcpServer(const std::string& host, const int port, const int backlog = 5);

		void Run();

	private:

		Cache             m_DatabaseLite;
		TcpSocket         m_ServerSocket;
	};
}

#endif