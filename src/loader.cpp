#include "../header/loader.hpp"

#include <fstream>

std::vector<std::vector<char>> Loader::load(const char* path)
{
	std::vector<std::vector<char>> result;
	std::ifstream stream(path);

	if(stream.is_open())
	{
		std::string buffer;
		while(!stream.eof())
		{
			std::getline(stream, buffer);

			if(!buffer.empty())
				result.emplace_back(std::vector<char>(std::begin(buffer), std::end(buffer)));
		}
	}

	return result;
}

