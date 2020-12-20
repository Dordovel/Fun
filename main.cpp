#include "./header/app.hpp"
#include "./header/loader.hpp"
#include "./header/converter.hpp"
#include "./header/star.hpp"

const int WIDTH = 400;
const int HEIGHT = 400;

const int cellPadding = 1;

int main()
{
	App app;

	if(app.open("Star", WIDTH, HEIGHT))
		return 1;


	SDL_Event event;
	bool RUN = true;

	Loader loader;

	auto val = loader.load("./map.txt");
	const int rectangleCountY = val.size();
	const int rectangleCountX = val.front().size();

    Converter converter;

	auto rectangles = converter.convert(val);
	const int rectangleHeight = std::ceil(float(HEIGHT -
                                                        (cellPadding >0 ? (rectangleCountY * cellPadding) : 0)
                                                        ) / rectangleCountY);

    const int rectangleWidth = std::ceil(float(WIDTH -
                                                (cellPadding >0 ? (rectangleCountX * cellPadding) : 0)
                                                ) / rectangleCountX);

	int x,y;
	x = y = 0;

	Rectangle* start = nullptr;
    Rectangle* end = nullptr;
	std::vector<Rectangle*> ends;

	for(auto& line : rectangles)
	{
		for(auto& column : line)
		{
			column.rect.x = x;
			column.rect.y = y;
			column.rect.w = rectangleWidth;
			column.rect.h = rectangleHeight;

			x += rectangleWidth + cellPadding;

			if(column.type == 2)
				start = &column;
			if(column.type == 3)
				ends.push_back(&column);
		}

		y += rectangleHeight + cellPadding;
		x = 0;
	}

	Star star;
	star.init(rectangles);

	std::vector<Star::Result> path;
    std::vector<Star::Result> visited;

	end = ends.back();
	ends.pop_back();

	auto build_path = [&star, &path, &visited, &end, &start, &rectangles]
                    {
                        path = star.find_path(*start, *end);
                        visited = star.get_visited();

                        for ( const auto& visit : visited )
                        {
                            rectangles[ visit.localY ][ visit.localX ].color.b = 50;
                            rectangles[ visit.localY ][ visit.localX ].color.r = 50;
                            rectangles[ visit.localY ][ visit.localX ].color.g = 50;
                        }

                        for ( std::size_t i = 1; i < path.size(); ++i )
                        {
                            Star::Result res = path[ i ];
                            rectangles[ res.localY ][ res.localX ].color.b = 0;
                            rectangles[ res.localY ][ res.localX ].color.r = 255;
                            rectangles[ res.localY ][ res.localX ].color.g = 255;
                        }

                        end->color.b = 0;
                        end->color.r = 0;
                        end->color.g = 255;
                    };

	if(start && end)
    {
	    build_path();
    }

    int step = 0;

	while(RUN)
	{
		while(SDL_PollEvent(&event))
		{
			if(event.type == SDL_QUIT)
			{
				RUN = false;
				break;
			}
		}

        if(step < path.size())
        {
            start->color.b = 0;
            start->color.r = 150;
            start->color.g = 150;

            Star::Result res = path[ step++ ];
            start = &rectangles[ res.localY ][ res.localX ];

            start->color.b = 255;
            start->color.r = 0;
            start->color.g = 0;

            SDL_Delay(500);
        }
        else
        {
            if(!ends.empty())
            {
                for ( const auto& visit : visited)
                {
                    rectangles[ visit.localY ][ visit.localX ].color.b = 255;
                    rectangles[ visit.localY ][ visit.localX ].color.r = 255;
                    rectangles[ visit.localY ][ visit.localX ].color.g = 255;
                }

                step = 0;
                end = ends.back();
                ends.pop_back();

                if(start && end)
                {
                    build_path();
                }
            }
        }


		app.draw(rectangles);
	}

	app.close();
	return 0;
}
