#ifndef SOBA_CACHE_H
#define SOBA_CACHE_H

#include "Common/RespTypes.h"

#include <mutex>
#include <string>
#include <vector>
#include <chrono>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <unordered_map>

namespace soba
{
	class Cache
	{
	public:

		using RespFormat = std::vector<std::string>;

		void HandleUserRequest(SOCKET clientSocket);
		
	private:

		struct DataInfo
		{
			std::string                           Data;
			std::chrono::milliseconds             Expiry;     // If Expiry is not set by the Client, it is set to - std::chrono::milliseconds::max()
			std::chrono::steady_clock::time_point StartTime;
		};

		std::string GetData(const RespArray& request);

		std::string SetData(const RespArray& request);

		std::string DeleteData(const RespArray& request);

	private:

		std::mutex                                m_Lock;
		std::unordered_map<std::string, DataInfo> m_Cache;
	};
}

#endif