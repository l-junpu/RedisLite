#ifndef SOBA_UTILS_H
#define SOBA_UTILS_H

#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

namespace soba::utils
{
	inline std::string tolower(std::string& data)
	{
		std::transform(data.begin(), data.end(), data.begin(),
			[](unsigned char c) { return std::tolower(c); }
		);
		return data;
	}

	inline std::vector<std::string> split(const std::string& str)
	{
		std::string word;
		std::vector<std::string> words;

		std::istringstream iss(str);
		while (iss >> word) {
			words.push_back(word);
		}

		return words;
	}
}

#endif