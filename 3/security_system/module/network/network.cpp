#include "network.hpp"
#include <iostream>
namespace Security_system
{
    void Network::connect(size_t ind)
    {
        if (ind >= switching_table.size())
        {
            throw std::out_of_range("Network::connect: index " + std::to_string(ind) +
                                    " out of range (size: " + std::to_string(switching_table.size()) + ")");
        }
        active_session.add_elem(switching_table[ind]);
    }
    

    void Network::create_switching_table(const std::vector<std::vector<std::shared_ptr<Component>>> &map, std::pair<size_t, size_t> pos) noexcept
    {

        if (map.empty() || map[0].empty())
        {
            return;
        }

        std::pair<size_t, size_t> env_size(map.size(), map[0].size());
        unsigned radius = get_radius();

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

                    std::shared_ptr<Platform> p = std::dynamic_pointer_cast<Platform>(comp);
                    if (p != nullptr)
                    {
                        std::cout << "find " << p->get_pos().first << ' ' << p->get_pos().second << std::endl;
                        std::vector<std::shared_ptr<Network>> modules = p->find_network();

                        if (!modules.empty())
                        {
                            switching_table.push_back(p);
                        }
                    }
                }
                else
                {

                    break;
                }
            }
        }
    }

    // void Network::turn_off()
    // {
    //     state = false;
    //     std::for_each(active_session.begin(), active_session.end(), [](const Platform *p)
    //                   { p-> })
    // }
}