#include "../header/app.hpp"

int App::init()
{
	if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
		return 1;

    return 0;
}

int App::open(const std::string& name, int width, int height)
{
    return this->open(name.c_str(), width, height);
}

int App::open(const char* name, int width, int height)
{
    if(this->init()) return 1;

	this->_window = SDL_CreateWindow(name, SDL_WINDOWPOS_UNDEFINED,
								SDL_WINDOWPOS_UNDEFINED,
								width, height, SDL_WINDOW_SHOWN);

    this->_render = SDL_CreateRenderer(this->_window, -1, SDL_RENDERER_ACCELERATED);

    if(!this->_window || !this->_render)
        return 1;
    else
        return 0;
}

void App::draw(const Rectangle& rectangle)
{
    SDL_SetRenderDrawColor(this->_render, 0, 0, 0, 0);
    SDL_RenderClear(this->_render);

    SDL_SetRenderDrawColor(this->_render, rectangle.color.r, rectangle.color.g, rectangle.color.b, rectangle.color.a);
    SDL_RenderFillRects(this->_render, &rectangle.rect, 1);

    SDL_RenderPresent(this->_render);

    SDL_UpdateWindowSurface(this->_window);
}

void App::draw(const std::vector<std::vector<Rectangle>>& rectangle)
{
    SDL_SetRenderDrawColor(this->_render, 0, 0, 0, 0);
    SDL_RenderClear(this->_render);

    for(auto& line : rectangle)
    {
		for(auto& column : line)
		{
			SDL_SetRenderDrawColor(this->_render, column.color.r, column.color.g, column.color.b, column.color.a);
			SDL_RenderFillRects(this->_render, &column.rect, 1);
		}
    }

    SDL_RenderPresent(this->_render);

    SDL_UpdateWindowSurface(this->_window);
}

void App::close()
{
	SDL_DestroyWindow(this->_window);

	SDL_DestroyRenderer(this->_render);
	SDL_Quit();
}
