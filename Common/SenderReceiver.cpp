#include "SenderReceiver.h"

#include <stdexcept>

namespace soba
{
	Sender::Sender(SOCKET socket) : m_Socket{ socket } {}

	void Sender::SendData(const std::string& data) const
	{
		if (send(m_Socket, data.c_str(), data.size(), 0) == SOCKET_ERROR) {
			throw std::runtime_error("Failed to send data: " + std::to_string(WSAGetLastError()));
		}
	}

	Receiver::Receiver(SOCKET socket) : m_Socket{socket} {}

	std::string Receiver::ReceiveData() const
	{
		char buffer[BUFFER_SIZE] = {0};
		int bytesReceived = recv(m_Socket, buffer, BUFFER_SIZE, 0);
		if (bytesReceived == SOCKET_ERROR) {
			throw std::runtime_error("Failed to receive data: " + std::to_string(WSAGetLastError()));
		}
		return std::string(buffer, bytesReceived);
	}
}