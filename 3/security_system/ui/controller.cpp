#include "controller.hpp"

namespace Security_system
{
    void Controller::set_size(size_t x, size_t y)
    {
        env->set_size(x, y);
    }

    std::vector<std::shared_ptr<Module>> Controller::get_modules(std::pair<size_t, size_t> p)
    {
        auto platform = std::dynamic_pointer_cast<Platform>(env->operator[](p));
        return platform ? platform->get_modules() : std::vector<std::shared_ptr<Module>>();
    }

    void Controller::kill_intruders()
    {
        ai.kill_intruders_all();
    }

    std::vector<std::pair<size_t, size_t>> Controller::get_component(const char type)
    {
        std::vector<std::pair<size_t, size_t>> result;

        auto map = env->get_map();
        for (size_t i = 0; i < map.size(); i++)
        {
            for (size_t j = 0; j < map[0].size(); j++)
            {
                if (!map[i][j]) continue;

                switch (type)
                {
                case 'i':
                    if (std::dynamic_pointer_cast<Intruder>(map[i][j]))
                    {
                        result.push_back(std::make_pair(i, j));
                    }
                    break;
                case 'p':
                    if (std::dynamic_pointer_cast<Platform>(map[i][j]))
                    {
                        result.push_back(std::make_pair(i, j));
                    }
                    break;
                case 's':
                    if (std::dynamic_pointer_cast<Static>(map[i][j]))
                    {
                        result.push_back(std::make_pair(i, j));
                    }
                    break;
                case 'm':
                    if (std::dynamic_pointer_cast<Mobile>(map[i][j]))
                    {
                        result.push_back(std::make_pair(i, j));
                    }
                    break;
                case 'w':
                    if (std::dynamic_pointer_cast<Wall>(map[i][j]))
                    {
                        result.push_back(std::make_pair(i, j));
                    }
                    break;
                default:
                    break;
                }
            }
        }

        return result;
    }

    void Controller::connect_network(std::pair<size_t, size_t> pos, size_t ind, size_t ind2)
    {
        auto platform = std::dynamic_pointer_cast<Platform>(env->operator[](pos));
        if (!platform) return;

        auto network = std::dynamic_pointer_cast<Network>(platform->operator[](ind));
        if (network)
        {
            network->connect(ind2);
        }
    }

    std::vector<std::shared_ptr<Platform>> Controller::get_active_session(std::pair<size_t, size_t> pos, size_t ind)
    {
        auto platform = std::dynamic_pointer_cast<Platform>(env->operator[](pos));
        if (!platform) return {};

        auto network = std::dynamic_pointer_cast<Network>(platform->operator[](ind));
        if (!network) return {};

        network->create_switching_table(env->get_map(), pos);
        return network->get_switching_table();
    }

    void Controller::move_platform(std::pair<size_t, size_t> p, std::pair<size_t, size_t> new_p)
    {
        auto mobile = std::dynamic_pointer_cast<Mobile>(env->operator[](p));
        if (mobile)
        {
            mobile->move(env, new_p);
        }
    }

    void Controller::add_intruder(std::pair<size_t, size_t> p)
    {
        auto new_component = std::make_shared<Intruder>(p);
        env->add_component(new_component);
    }

    void Controller::add_static(const std::string &desc, unsigned energy, unsigned cap, std::pair<size_t, size_t> p)
    {
        auto new_component = std::make_shared<Static>(desc, energy, cap, p);
        ai.connect_platform(std::dynamic_pointer_cast<Platform>(new_component));
        env->add_component(new_component);
    }

    void Controller::add_mobile(const std::string &desc, unsigned energy, unsigned cap, unsigned spd, std::pair<size_t, size_t> p)
    {
        auto new_component = std::make_shared<Mobile>(desc, energy, cap, spd, p);
        ai.connect_platform(std::dynamic_pointer_cast<Platform>(new_component));
        env->add_component(new_component);
    }

    void Controller::add_wall(std::pair<size_t, size_t> p)
    {
        auto new_component = std::make_shared<Wall>(p);
        env->add_component(new_component);
    }

    void Controller::add_network(std::pair<size_t, size_t> p, unsigned power, unsigned cnt, unsigned r)
    {
        auto new_module = std::make_shared<Network>(power, cnt, r);
        auto platform = std::dynamic_pointer_cast<Platform>(env->operator[](p));
        if (platform)
        {
            platform->add_module(new_module);
        }
        else
        {
            throw std::runtime_error("No platform at specified position");
        }
    }

    void Controller::add_x_ray(std::pair<size_t, size_t> p, unsigned power, unsigned cnt, unsigned r)
    {
        auto new_module = std::make_shared<X_ray>(power, cnt, r);
        auto platform = std::dynamic_pointer_cast<Platform>(env->operator[](p));
        if (platform)
        {
            platform->add_module(new_module);
        }
        else
        {
            throw std::runtime_error("No platform at specified position");
        }
    }

    void Controller::add_optical(std::pair<size_t, size_t> p, unsigned power, unsigned cnt, unsigned r)
    {
        auto new_module = std::make_shared<Optical>(power, cnt, r);
        auto platform = std::dynamic_pointer_cast<Platform>(env->operator[](p));
        if (platform)
        {
            platform->add_module(new_module);
        }
        else
        {
            throw std::runtime_error("No platform at specified position");
        }
    }

    void Controller::add_military(std::pair<size_t, size_t> p, unsigned power, unsigned cnt, unsigned r, unsigned time)
    {
        auto new_module = std::make_shared<Military>(power, cnt, r, time);
        auto platform = std::dynamic_pointer_cast<Platform>(env->operator[](p));
        if (platform)
        {
            platform->add_module(new_module);
        }
        else
        {
            throw std::runtime_error("No platform at specified position");
        }
    }
}