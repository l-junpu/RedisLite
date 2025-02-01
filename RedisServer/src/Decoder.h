#ifndef SOBA_RESP_DECODER_H
#define SOBA_RESP_DECODER_H

#include <string>
#include <vector>

namespace soba::decoder
{
	std::vector<std::string> DecodeRESP(const std::string& info);
}

#endif