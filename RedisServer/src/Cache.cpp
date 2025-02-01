#include "Cache.h"
#include "Decoder.h"

#include "Common/Utils.h"
#include "Common/SenderReceiver.h"

#include <thread>
#include <iostream>

namespace soba
{
	void Cache::HandleUserRequest(SOCKET clientSocket)
	{
		Sender   sender   = Sender(clientSocket);
		Receiver receiver = Receiver(clientSocket);

		std::string request  = {};
		std::string response = {};

		// Loop until Client requests to "/exit"
		while (true) {
			// Receive Client request
			request = receiver.ReceiveData();
			std::cout << "Received request: " << request << std::endl;

			// Parse Client request
			RespFormat command = decoder::DecodeRESP(request);

			// Client messed up - No request
			if (command.empty()) continue;

			// Handle actual requests
			if (command[0] == "/exit") {
				break;
			}
			else if (command[0] == "get" && command.size() == 2) {
				response = GetData(command);
			}
			else if (command[0] == "del" && command.size() == 2) {
				response = DeleteData(command);
			}
			// Either "set <key> <value>" or "set <key> <value> <expiry>"
			else if (command[0] == "set" && (command.size() == 3 || command.size() == 4)) {
				response = SetData(command);
			}
			else {
				sender.SendData("Invalid request: " + request);
				continue;
			}

			// Send our response if the request was valid, and handled
			sender.SendData(response);
		}

		closesocket(clientSocket);
	}

	std::string Cache::GetData(const RespFormat& request)
	{
		return std::string();
	}

	std::string Cache::SetData(const RespFormat& request)
	{
		return std::string();
	}

	std::string Cache::DeleteData(const RespFormat& request)
	{
		return std::string();
	}
}