#include "Cache.h"

#include "Common/SenderReceiver.h"

#include <thread>
#include <iostream>

namespace soba
{
	void Cache::HandleUserRequest(SOCKET clientSocket)
	{
		Sender   sender   = Sender(clientSocket);
		Receiver receiver = Receiver(clientSocket);

		std::string request = {};

		while (true) {
			request = receiver.ReceiveData();

			std::cout << "Received request: " << request << std::endl;

			if (request == "/exit") break;
			else {
				sender.SendData(request);
			}
		}

		closesocket(clientSocket);
	}

	std::pair<Cache::RequestType, Cache::RespFormat> Cache::InterpretUserRequest(const std::string& request)
	{
		return std::pair<RequestType, RespFormat>();
	}

	std::string Cache::GetData(const RespFormat& request)
	{
		return std::string();
	}

	void Cache::SetData(const RespFormat& request)
	{

	}

	void Cache::RemoveData(const RespFormat& request)
	{

	}
}