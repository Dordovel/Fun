#include "../header/converter.hpp"

std::vector<std::vector<Rectangle>> Converter::convert(const std::vector<std::vector<char>>& v)
{
    std::vector<std::vector<Rectangle>> result;
    result.reserve(v.size());

    for(std::size_t y = 0; y < v.size(); ++y)
    {
        result.emplace_back();
        std::vector<Rectangle>& last = result.back();
        last.reserve(v[y].size());

        for(std::size_t x = 0; x < v[y].size(); ++x)
        {
            Rectangle rectangle;
            if(v[y][x] == '*')
            {
                rectangle.color = SDL_Color{255, 0, 0, 1};
                rectangle.obstacle = true;
                rectangle.type = 1;
            }
            else if(v[y][x] == '#')
            {
                rectangle.color = SDL_Color{0, 0, 255, 1};
                rectangle.type = 2;
            }
            else if(v[y][x] == '%')
            {
                rectangle.color = SDL_Color{0, 255, 0, 1};
                rectangle.type = 3;
            }
            else
            {
                rectangle.color = SDL_Color{255, 255, 255, 1};
                rectangle.type = 0;
            }

            rectangle.localY = y;
            rectangle.localX = x;

            last.push_back(rectangle);
        }
    }

    return result;
}
