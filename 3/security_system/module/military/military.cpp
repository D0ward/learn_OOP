#include "military.hpp"

namespace Security_system
{
    void Military::kill_intruder(std::shared_ptr<Intruder> intruder, std::pair<size_t, size_t> pos) const
    {
        // charge();

        const std::pair<size_t, size_t> pos_int = intruder->get_pos();
        if (pow(pos_int.first - pos.first, 2) + pow(pos_int.second - pos.second, 2) <= pow(get_radius(), 2))
        {
            intruder->kill();
        }
    }
}