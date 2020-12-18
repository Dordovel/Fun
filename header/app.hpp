#ifndef APP_HEADER
#define APP_HEADER

#include "./rectangle.hpp"

#include <vector>
#include <string>

class App 
{
    private:
        SDL_Renderer* _render;
        SDL_Window* _window;

        int init();

    public:
        int open(const std::string& name, int width, int height);
        int open(const char* name, int width, int height);

        void draw(const Rectangle& rectangle);
        void draw(const std::vector<std::vector<Rectangle>>& rectangle);

        void close();
};

#endif //APP_HEADER
