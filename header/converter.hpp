#ifndef CONVERTER_HEADER
#define CONVERTER_HEADER

#include "./rectangle.hpp"

#include <vector>

class Converter
{
    public:
        std::vector<std::vector<Rectangle>> convert(const std::vector<std::vector<char>>& v);
};


#endif //CONVERTER_HEADER
