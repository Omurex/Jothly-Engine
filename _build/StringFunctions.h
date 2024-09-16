#pragma once
#include <vector>
#include <string>


namespace jothly
{
	std::vector<std::string> SplitByDelimiter(std::string str, std::string delimiter)
	{
		std::vector<std::string> vec;

		size_t pos = 0;
		std::string token;
		while ((pos = str.find(delimiter)) != std::string::npos) {
			token = str.substr(0, pos);
			vec.push_back(token);
			str.erase(0, pos + delimiter.length());
		}
		
		vec.push_back(str);
		return vec;
	}
}