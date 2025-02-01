#ifndef SOBA_UTILS_H
#define SOBA_UTILS_H

#include <string>
#include <algorithm>

namespace soba::utils
{
	std::string tolower(std::string& data) {
		std::transform(data.begin(), data.end(), data.begin(),
			[](unsigned char c) { return std::tolower(c); });
		return data;
	}
}

#endif