#include "../header/star.hpp"

#include <list>
#include <cmath>
#include <algorithm>

float Star::distance(Node* lv, Node* rv)
{
    return std::sqrt(std::pow((lv->localX - rv->localX), 2.f)
                     + std::pow((lv->localY - rv->localY), 2.f));
}

void Star::reset_node()
{
    for(int x = 0; x < this->_width; x++)
    {
        for(int y = 0; y < this->_height; y++)
        {
            Node* node = &this->_nodes[y * this->_width + x];

            node->parent = nullptr;
            node->visited = false;
            node->globalGoal = INFINITY;
            node->localGoal = INFINITY;
        }
    }
}

void Star::find_pointers()
{
    for(int x = 0; x < this->_width; x++)
    {
        for(int y = 0; y < this->_height; y++)
        {
			Node& node = this->_nodes[y * this->_width + x];

            if(y > 0)
                node.vecNeighbours.push_back(&this->_nodes[(y - 1) * this->_width + x]);
            if(y < this->_height - 1)
                node.vecNeighbours.push_back(&this->_nodes[(y + 1) * this->_width + x]);
            if(x > 0)
                node.vecNeighbours.push_back(&this->_nodes[y * this->_width + (x - 1)]);
            if(x < this->_width - 1)
                node.vecNeighbours.push_back(&this->_nodes[y * this->_width + (x + 1)]);
        }
    }
}

void Star::init(const std::vector<std::vector<Rectangle>>& map)
{
    if(map.empty()) return;

    this->_height = map.size();
    this->_width = map.front().size();

    this->_nodes.clear();
    this->_nodes.reserve(this->_height * this->_width);

    for(const auto& line : map)
    {
        for(const auto& column : line)
        {
            this->_nodes.emplace_back();

            Node& node = this->_nodes.back();

            node.parent = nullptr;
            node.visited = false;
            node.localX = column.localX;
            node.localY = column.localY;
            node.globalX = column.rect.x;
            node.globalY = column.rect.y;
            node.obstacle = column.obstacle;
        }
    }

    this->find_pointers();

}

std::vector<Star::Result> Star::find_path(const Rectangle& s, const Rectangle& d)
{
    this->reset_node();

    Node* start = &this->_nodes[s.localY * this->_width + s.localX];
    Node* end = &this->_nodes[d.localY * this->_width + d.localX];

    Node* current = start;
    start->localGoal = 0.f;
    start->globalGoal = distance(start, end);

    std::list<Node*> buffer;
    buffer.push_back(start);

    while(!buffer.empty() && current != end)
    {
        buffer.sort([](const auto* lv, const auto* rv){return lv->globalGoal < rv->globalGoal;});

        if(!buffer.empty() && buffer.front()->visited)
            buffer.pop_front();

        if(buffer.empty())
            break;

        current = buffer.front();
        current->visited = true;

        for(auto nodeNeighbour : current->vecNeighbours)
        {
            if(!nodeNeighbour->visited && !nodeNeighbour->obstacle)
                buffer.push_back(nodeNeighbour);

            float lowerGoal = current->localGoal + distance(current, nodeNeighbour);

            if(lowerGoal < nodeNeighbour->localGoal)
            {
                nodeNeighbour->parent = current;
                nodeNeighbour->localGoal = lowerGoal;

                nodeNeighbour->globalGoal = nodeNeighbour->localGoal + distance(nodeNeighbour, end);
            }
        }
    }

    std::vector<Result> path;

    path.emplace_back(Result{end->localX, end->localY, end->globalX, end->globalY});

    while(end->parent)
    {
        end = end->parent;
        path.emplace_back(Result{end->localX, end->localY, end->globalX, end->globalY});
    }

    std::reverse(std::begin(path), std::end(path));

    return path;
}

std::vector<Star::Result> Star::get_visited()
{
    std::vector <Result> result;
    Result res;

    for(auto& iter : this->_nodes)
    {
        if(iter.visited)
        {
            res.localX = iter.localX;
            res.localY = iter.localY;
            res.globalX = iter.globalX;
            res.globalY = iter.globalY;

            result.push_back(res);
        }
    }

    return result;
}
