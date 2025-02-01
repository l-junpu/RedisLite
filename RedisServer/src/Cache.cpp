#include "Cache.h"

#include <thread>
#include <iostream>

namespace soba
{
	std::string Cache::HandleUserRequest(SOCKET clientSocket)
	{
		return std::string();
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