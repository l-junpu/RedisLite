#ifndef SOBA_RESP_ENCODER_H
#define SOBA_RESP_ENCODER_H

#include "Common/Utils.h"

#include <string>
#include <vector>

namespace soba
{
	// Refer to - https://redis.io/docs/latest/develop/reference/protocol-spec/
	struct Encoder final
	{
	public:

		static std::string EncodeRESP(const std::string& fullRequest)
		{
			// Do not encode "/exit"
			if (fullRequest == "/exit") return fullRequest;

			// Separate each input by whitespaces
			std::vector<std::string> inputs = utils::split(fullRequest);

			// Encode in RESP format - Currently only as Array + Bulk String
			return EncodeArray(inputs);
		}

	private:

		static std::string EncodeArray(const std::vector<std::string>& inputs)
		{
			// Initial array count
			std::string result = "*" + std::to_string(inputs.size()) + "\r\n";

			// Encode each array element
			for (const auto& input : inputs) {
				result += EncodeBulkString(input);
			}

			return result;
		}

		static std::string EncodeBulkString(const std::string& value)
		{
			return "$" + std::to_string(value.size()) + "\r\n" + value + "\r\n";
		}
	};
}

#endif