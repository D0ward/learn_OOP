
#include <stdexcept>
#include "mobile.hpp"

namespace Security_system
{
    void Mobile::move(std::shared_ptr<Environment> map, std::pair<size_t, size_t> new_pos)
    {
        std::pair<size_t, size_t> old_pos = get_pos();
        if (pow((new_pos.first - old_pos.first), 2) + pow((new_pos.second - old_pos.second), 2) <= speed * speed)
        {
            this->set_pos(new_pos, map);
        }
        else
        {
            throw std::invalid_argument("New position to far away");
        }
    }
}
