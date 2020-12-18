#ifndef STAR_HEADER
#define STAR_HEADER

#include "./rectangle.hpp"

#include <vector>

class Star
{
	private:

		struct Node
		{
			bool visited = false;
			float globalGoal;
			float localGoal;
			bool obstacle = false;
			int localX, localY, globalX, globalY;

			std::vector<Node*> vecNeighbours;

			Node* parent;
		};

		int _width;
		int _height;

		std::vector<Node> _nodes;


		float distance(Node* lv, Node* rv);

		void reset_node();

		void find_pointers();

	public:

        struct Result
        {
            int localX, localY, globalX, globalY;
        };

		void init(const std::vector<std::vector<Rectangle>>& map);

		std::vector<Result> find_path(const Rectangle& s, const Rectangle& d);

        std::vector<Result> get_visited();
};

#endif //STAR_HEADER
