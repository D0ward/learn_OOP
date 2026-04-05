#include "environment.hpp"

namespace Security_system
{
    void Environment::add_component(std::shared_ptr<Component> comp)
    {
        std::pair<size_t, size_t> pos = comp->get_pos();

        if (pos.first < size.first && pos.second < size.second && is_empty(pos.first, pos.second))
        {
            map[pos.first][pos.second] = comp;
        }
    }

    bool Environment::is_empty(size_t x, size_t y) const
    {
        return x < size.first && y < size.second && !map[x][y];
    }
}