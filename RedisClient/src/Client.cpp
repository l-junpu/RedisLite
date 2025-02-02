#include "Client.h"
#include "Common/Decoder.h"
#include "Common/Encoder.h"

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
		std::string command  = {};
		Sender      sender   = Sender(m_ClientSocket.GetSocket());
		Receiver    receiver = Receiver(m_ClientSocket.GetSocket());

		while (true) {
			try {
				// Wait for Client's comamnd
				command = m_InputHandler.AwaitUserCommand();

				// This happens only if the Client types "/help" or <Enter> by accident 
				if (command.empty()) {
					std::cout << "\n-------------------------------------------\n" << std::endl;
					continue;
				}

				// Send the Client's command over - If "/exit", we can just terminate and cleanup
				std::cout << "Sending command: " << command << std::endl;
				sender.SendData( Encoder::EncodeRESP(command) );
				if (command == "/exit") break;

				// Receive Server's response
				std::string response = receiver.ReceiveData();
				std::cout << "Received response (raw):\n" << response << std::endl;

				Decoder decoder(response);
				std::cout << "Received response (decoded):\n" << decoder.DecodeRESP()->ToString() << std::endl;
				std::cout << "\n-------------------------------------------\n" << std::endl;
			}
			catch (const std::exception& e) {
				std::cout << "Client error: " << e.what() << std::endl;
			}
		}

		closesocket(m_ClientSocket.GetSocket());
		WSACleanup();
	}

	bool TcpClient::ValidCommand(const std::string& command) const
	{
		return false;
	}
}