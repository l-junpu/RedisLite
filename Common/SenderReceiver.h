#ifndef SOBA_SENDER_RECEIVER_H
#define SOBA_SENDER_RECEIVER_H

#include <string>
#include <winsock2.h>

namespace soba
{
	static const int BUFFER_SIZE = 1024;

	class Sender final
	{
	public:

		Sender(SOCKET socket);
		void SendData(const std::string& data) const;

	private:

		SOCKET m_Socket;
	};

	class Receiver final
	{
	public:

		Receiver(SOCKET socket);
		std::string ReceiveData() const;

	private:

		SOCKET m_Socket;
	};
}

#endif