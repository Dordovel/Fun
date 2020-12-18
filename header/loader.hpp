#ifndef LOADER_HEADER
#define LOADER_HEADER

#include "./rectangle.hpp"

#include <vector>
#include <string>

class Loader
{
    public:
        std::vector<std::vector<char>> load(const char* path);

};

#endif //LOADER_HEADER
