#include "Cache.h"
#include "Common/Decoder.h"
#include "Common/Encoder.h"

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
			std::cout << "Recived request (raw):\n" << request << std::endl;

			// Parse Client request
			Decoder decoder(request);
			std::shared_ptr<RespElement> resp = decoder.DecodeRESP();

			// Handle actual requests
			if (resp->Type == RespType::EXIT) {
				break;
			}
			else if (resp->Type == RespType::ARRAY) {
				RespArray* arr      = reinterpret_cast<RespArray*>(resp.get());
				auto       commands = arr->Elements;

				std::cout << "Received request (decoded):\n" << arr->ToString() << std::endl;
				std::cout << "\n-------------------------------------------\n" << std::endl;

				if (commands.size() < 2) continue; // throw an error

				std::string command = commands[0]->ToString();
				command = utils::tolower(command);

				if (command == "get") {
					response = GetData(*arr);
				}
				else if (command == "del") {
					response = DeleteData(*arr);
				}
				// Either "set <key> <value>" or "set <key> <value> <expiry>"
				else if (command == "set") {
					response = SetData(*arr);
				}
			}
			else {
				sender.SendData("Invalid request: " + request);
				std::cout << "Invalid request: " + request << std::endl;
				std::cout << "\n-------------------------------------------\n" << std::endl;
				continue;
			}

			// Send our response if the request was valid, and handled
			sender.SendData(Encoder::EncodeRESP(response));
		}

		closesocket(clientSocket);
		std::cout << "Client disconnected" << std::endl;
		std::cout << "\n-------------------------------------------\n" << std::endl;
	}

	std::string Cache::GetData(const RespArray& request)
	{
		std::string key    = request.Elements[1]->ToString();
		bool        exists = m_Cache.find(key) != m_Cache.end();

		if (exists) {
			DataInfo& instance = m_Cache[key];
			auto now = std::chrono::high_resolution_clock::now();
			auto elapsedMs = std::chrono::duration_cast<std::chrono::milliseconds>(now - instance.StartTime);
			if (elapsedMs > instance.Expiry) {
				m_Cache.erase(key);
				return { "nil" };
			}
			return instance.Data;
		}
		else {
			return "nil";
		}
	}

	std::string Cache::SetData(const RespArray& request)
	{
		// Has to either be "set <key> <val>" or "set <key> <val> <expiration>"
		if (request.Elements.size() < 3 ||
			request.Elements.size() > 4) return { "Err: " + request.ToString() };

		std::string key = request.Elements[1]->ToString();
		std::string val = request.Elements[2]->ToString();

		bool exists = m_Cache.find(key) != m_Cache.end();
		auto now = std::chrono::high_resolution_clock::now();

		// Update data
		DataInfo& instance = m_Cache[key];
		instance.Data = val;
		instance.Expiry = (std::chrono::milliseconds::max)();
		instance.StartTime = now;

		// Update expiration timer if user specified it
		if (request.Elements.size() == 4) {
			int expMs = std::stoi(request.Elements[3]->ToString());
			instance.Expiry = std::chrono::milliseconds(expMs);
		}

		return { "Ok" };
	}

	std::string Cache::DeleteData(const RespArray& request)
	{
		std::string key = request.Elements[1]->ToString();
		if (m_Cache.find(key) != m_Cache.end()) {
			m_Cache.erase(key);
			return { "Ok" };
		}
		return { "Err" };
	}
}