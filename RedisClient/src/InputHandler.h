#ifndef SOBA_INPUT_HANDLER
#define SOBA_INPUT_HANDLER

#include <string>

namespace soba
{
	struct InputHandler final
	{
	public:

		std::string AwaitUserCommand();

	private:

		void DisplayAvailableCommands();
	};
}

#endif