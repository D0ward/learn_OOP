#include "../../../module/base/module.hpp"
#include "platform.hpp"
#include "../../base/component.hpp"
#include "../../../module/military/military.hpp"
#include "../../../module/network/network.hpp"
#include "../../../module/sensor/sensor.hpp"

namespace Security_system
{

    void Platform::add_module(std::shared_ptr<Module> module)
    {
        if (module->get_power() <= energy_level && module->get_slots() <= capacity)
        {
            this->modules.push_back(module);
            capacity -= module->get_slots();
            energy_level -= module->get_power();
        }
        else if (module->get_power() > energy_level)
        {
            throw std::invalid_argument("low energy level platform");
        }
        else
        {
            throw std::invalid_argument("small capacity platform");
        }
    }

    void Platform::remove_module(size_t index)
    {
        if (index >= modules.size())
            throw std::out_of_range("index out of range");
        auto it = modules.begin();
        std::advance(it, index);
        modules.erase(it);
    }


    std::vector<std::shared_ptr<Network>> Platform::find_network() const noexcept
    {
        std::vector<std::shared_ptr<Network>> res;
        for (auto module : modules)
        {
            auto n = std::dynamic_pointer_cast<Network>(module);
            if (n)
            {
                res.push_back(n);
            }
        }
        return res;
    }

    std::vector<std::shared_ptr<Military>> Platform::find_military() const noexcept
    {
        std::vector<std::shared_ptr<Military>> res;
        for (auto module : modules)
        {
            auto n = std::dynamic_pointer_cast<Military>(module);
            if (n)
            {
                res.push_back(n);
            }
        }
        return res;
    }

    std::vector<std::shared_ptr<Sensor>> Platform::find_sensor() const noexcept
    {
        std::vector<std::shared_ptr<Sensor>> res;
        for (auto module : modules)
        {
            auto n = std::dynamic_pointer_cast<Sensor>(module);
            if (n)
            {
                res.push_back(n);
            }
        }
        return res;
    }
}