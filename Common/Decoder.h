#ifndef SOBA_RESP_DECODER_H
#define SOBA_RESP_DECODER_H

#include "RespTypes.h"

#include <string>
#include <vector>
#include <memory>
#include <sstream>

namespace soba
{
	struct Decoder final
	{
		Decoder(const std::string& resp) : iss{ resp } { }

		//*3\r\n$3\r\nSET\r\n$5\r\nmykey\r\n$2\r\n42\r\n
		std::shared_ptr<RespElement> DecodeRESP()
		{
			char op;
			iss >> op;

			switch (op)
			{
				case '*': return DecodeArray();
				case '$': return DecodeBulkString();
				default:
				{
					return std::make_shared<RespElement>(RespType::EXIT);
				}
			}
		}

	private:

		std::shared_ptr<RespElement> DecodeBulkString()
		{
			// Read number of letters in Bulk String
			int len;
			iss >> len;
			iss.ignore(2);
			
			// Read stream into value
			std::string value(len, '\0');
			iss.read(&value[0], len);
			iss.ignore(2);
			
			return std::make_shared<RespBulkString>(RespType::BULK_STRING, value);
		}

		std::shared_ptr<RespElement> DecodeArray()
		{
			// Read number of elements in Array
			int len;
			iss >> len;
			iss.ignore(2);

			std::shared_ptr<RespArray> arr = std::make_shared<RespArray>(RespType::ARRAY);
			for (int i = 0; i < len; ++i) {
				(*arr).Elements.push_back( DecodeRESP() );
			}

			return arr;
		}

	private:

		std::istringstream iss;
	};
}

#endif