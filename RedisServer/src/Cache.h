#ifndef SOBA_CACHE_H
#define SOBA_CACHE_H

#include <mutex>
#include <winsock2.h>
#include <ws2tcpip.h>

namespace soba
{
	class Cache
	{
	public:

		using RespFormat = std::string;

		std::string HandleUserRequest(SOCKET clientSocket);
		
	private:

		enum class RequestType : uint8_t
		{
			SET = 0,
			REMOVE,
			GET,
			EXIT
		};

		std::pair<RequestType, RespFormat> InterpretUserRequest(const std::string& request);

		std::string GetData(const RespFormat& request);

		void SetData(const RespFormat& request);

		void RemoveData(const RespFormat& request);

	private:

		std::mutex m_Lock;
	};
}

#endif