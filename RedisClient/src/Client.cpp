#include "Client.h"

#include <iostream>
#include <stdexcept>

namespace soba
{
	void TcpClient::InitializeClient(const std::string& serverHost, const int serverPort)
	{
		// Initialize Winsock
		WSADATA wsaData;
		if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
			throw std::runtime_error("WSAStartup failed: " + std::to_string(WSAGetLastError()));
		}

		// Create the Socket
		m_ClientSocket.CreateSocket();
		m_ClientSocket.EstablishConnectionToServer(serverHost, serverPort);
	}

	void TcpClient::Run()
	{
		int count = 0;

		Sender   sender   = Sender(m_ClientSocket.GetSocket());
		Receiver receiver = Receiver(m_ClientSocket.GetSocket());

		while (count < 5) {
			try {
				sender.SendData("hello hello from client");

				std::string response = receiver.ReceiveData();
				std::cout << "Received response: " << response << std::endl;

				++count;
				Sleep(1000);
			}
			catch (const std::exception& e) {
				std::cout << "Client error: " << e.what() << std::endl;
			}
		}

		sender.SendData("exit");
		closesocket(m_ClientSocket.GetSocket());
		WSACleanup();
	}
}