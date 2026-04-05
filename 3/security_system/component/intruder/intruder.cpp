#include "intruder.hpp"
#include "../../environment/environment.hpp"
namespace Security_system
{
    void Intruder::move(std::shared_ptr<Environment> map)
    {
        std::pair<size_t, size_t> pos = get_pos();

        if (map->is_empty(pos.first + 1, pos.second))
        {
            set_pos(std::make_pair(pos.first + 1, pos.second), map);
            return;
        }
        else if (map->is_empty(pos.first - 1, pos.second))
        {
            set_pos(std::make_pair(pos.first - 1, pos.second), map);
            return;
        }
        else if (map->is_empty(pos.first, pos.second + 1))
        {
            set_pos(std::make_pair(pos.first, pos.second + 1), map);
            return;
        }
        else if (map->is_empty(pos.first, pos.second - 1))
        {
            set_pos(std::make_pair(pos.first, pos.second - 1), map);
            return;
        }
    }
}