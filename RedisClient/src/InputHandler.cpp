#include "InputHandler.h"

#include "Common/Utils.h"

#include <iostream>

namespace soba
{
	std::string InputHandler::AwaitUserCommand()
	{
		std::string command = {};

		std::cout << "Type /help to view all available commands." << std::endl;
		std::cout << "RedisLite> ";

		std::getline(std::cin, command);
		if (tolower(command) == "/help") DisplayAvailableCommands();
		else                             return command;

		return {};
	}

	void InputHandler::DisplayAvailableCommands()
	{
		std::cout << "\nAvailable commands:\n"
			      << "/exit - Terminates the client application\n"
			      << "GET <key> - Retrieves the value assigned to the key if it exists, null otherwise\n"
			      << "SET <key> <value> - Sets the key and value, overwriting the value if the key exists\n"
			      << "DEL <key> - Removes the key and value pair if it exists" << std::endl;
	}
}