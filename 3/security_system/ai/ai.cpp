#include "ai.hpp"
#include "../module/military/military.hpp"
#include "../module/sensor/sensor.hpp"
#include "../module/network/network.hpp"
#include "../component/platform/base/platform.hpp"
#include "../environment/environment.hpp"
#include <list>
#include <execution>
#include <thread>

namespace Security_system
{
    void AI::connect_platform(std::shared_ptr<Platform> platform)
    {
        this->connected_platform.push_back(platform);
    }
    void AI::kill_intruders(std::shared_ptr<Platform> platform) const
    {
        auto map = this->env->get_map();
        for (auto sens : platform->find_sensor())
        {

            std::list<std::shared_ptr<Intruder>> intruders = sens->scan(map, platform->get_pos());
            for (auto military : platform->find_military())
            {
                for (auto intruder : intruders)
                {
                    military->kill_intruder(intruder, platform->get_pos());
                }
            }
        }
    }
    
    void AI::kill_intruders_all() const
    {
        const unsigned cnt_treads = std::thread::hardware_concurrency();
        size_t chunk_size = (connected_platform.size() + cnt_treads - 1) / cnt_treads;
        std::vector<std::thread> threads;

        for (size_t i = 0; i < connected_platform.size(); i += chunk_size)
        {
            threads.emplace_back([this, i, chunk_size]() {
                kill_intruders(connected_platform[i]);
                for (auto network : (connected_platform[i])->find_network())
                {
                    for (auto platform_2 : network->get_active_session())
                    {
                        kill_intruders(platform_2);
                    }
                }
            });

        }

        for (auto& thread : threads)
        {
            thread.join();
        }

    }
}
