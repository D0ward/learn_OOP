#include "sensor.hpp"

namespace Security_system
{
    std::list<std::shared_ptr<Intruder>> X_ray::scan(std::vector<std::vector<std::shared_ptr<Component>>> &map, const std::pair<size_t, size_t> pos) const
    {
        if (!state)
            throw std::invalid_argument("Модуль выключен");
        std::list<std::shared_ptr<Intruder>> res;
        unsigned radius = get_radius();
        std::pair<size_t, size_t> env_size(map.size(), map[0].size());

        for (int dx = -static_cast<int>(radius); dx <= static_cast<int>(radius); dx++)
        {
            for (int dy = -static_cast<int>(radius); dy <= static_cast<int>(radius); dy++)
            {

                if (dx * dx + dy * dy > static_cast<int>(radius * radius))
                {
                    continue;
                }

                size_t x = static_cast<size_t>(static_cast<int>(pos.first) + dx);
                size_t y = static_cast<size_t>(static_cast<int>(pos.second) + dy);

                if (x < env_size.first && y < env_size.second)
                {
                    auto comp = map[x][y];

                    std::shared_ptr<Intruder> intruder = std::dynamic_pointer_cast<Intruder>(comp);
                    if (intruder != nullptr)
                    {
                        res.push_back(intruder);
                    }
                }
            }
        }

        return res;
    }

    std::list<std::shared_ptr<Intruder>> Optical::scan(std::vector<std::vector<std::shared_ptr<Component>>> &map, const std::pair<size_t, size_t> pos) const
    {
        if (!state)
            throw std::invalid_argument("Модуль выключен");

        std::list<std::shared_ptr<Intruder>> res;
        unsigned radius = get_radius();
        std::pair<size_t, size_t> env_size(map.size(), map[0].size());

        const std::vector<std::pair<int, int>> directions = {
            {0, 1}, {0, -1}, {1, 0}, {-1, 0}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};

        for (const auto &dir : directions)
        {
            for (unsigned dist = 1; dist <= radius; dist++)
            {
                int x = static_cast<int>(pos.first) + dir.first * static_cast<int>(dist);
                int y = static_cast<int>(pos.second) + dir.second * static_cast<int>(dist);

                if (x >= 0 && x < static_cast<int>(env_size.first) &&
                    y >= 0 && y < static_cast<int>(env_size.second))
                {

                    auto comp = map[x][y];
                    std::shared_ptr<Intruder> intruder = std::dynamic_pointer_cast<Intruder>(comp);
                    if (intruder != nullptr)
                    {
                        res.push_back(intruder);
                    }
                }
                else
                {
                    break;
                }
            }
        }

        return res;
    }

}