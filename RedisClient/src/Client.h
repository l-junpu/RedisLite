#ifndef SOBA_CLIENT_H
#define SOBA_CLIENT_H

#include "InputHandler.h"
#include "Common/TcpSocket.h"
#include "Common/SenderReceiver.h"

#include <string>
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "Ws2_32.lib")

namespace soba
{
	class TcpClient final
	{
	public:

		void InitializeClient(const std::string& serverHost, const int serverPort);

		void Run();

	private:

		bool ValidCommand(const std::string& command) const;

	private:

		InputHandler m_InputHandler;
		TcpSocket    m_ClientSocket;
	};
}

#endif