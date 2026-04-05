#pragma once
#include <yaml-cpp/yaml.h>
#include <memory>

#include "../module/base/module.hpp"
#include "../module/sensor/sensor.hpp"
#include "../module/military/military.hpp"
#include "../module/network/network.hpp"

namespace YAML
{
    /**
     * @brief Специализация для сохранения и загрузки Module
     */
    template <>
    struct convert<Security_system::Module>
    {
        static Node encode(const Security_system::Module &module)
        {
            Node node;
            node["power"] = module.get_power();
            node["slots"] = module.get_slots();
            node["radius"] = module.get_radius();
            node["state"] = module.get_state();
            node["type"] = "Module";
            return node;
        }

        static bool decode(const Node &node, Security_system::Module &module)
        {
            if (node["power"])
                module.set_power(node["power"].as<unsigned>());
            if (node["slots"])
                module.set_slots(node["slots"].as<unsigned>());
            if (node["radius"])
                module.set_radius(node["radius"].as<unsigned>());
            if (node["state"])
            {
                bool state = node["state"].as<bool>();
                if (state)
                    module.turn_on();
                else
                    module.turn_off();
            }
            return true;
        }
    };

    /**
     * @brief Специализация для сохранения и загрузки Network
     */
    template <>
    struct convert<Security_system::Network>
    {
        static Node encode(const Security_system::Network &network)
        {
            Node node;
            node["power"] = network.get_power();
            node["slots"] = network.get_slots();
            node["radius"] = network.get_radius();
            node["state"] = network.get_state();
            node["type"] = "Network";
            return node;
        }

        static bool decode(const Node &node, Security_system::Network &network)
        {
            if (node["power"])
                network.set_power(node["power"].as<unsigned>());
            if (node["slots"])
                network.set_slots(node["slots"].as<unsigned>());
            if (node["radius"])
                network.set_radius(node["radius"].as<unsigned>());
            if (node["state"])
            {
                bool state = node["state"].as<bool>();
                if (state)
                    network.turn_on();
                else
                    network.turn_off();
            }
            return true;
        }
    };

    /**
     * @brief Специализация для сохранения и загрузки X_ray
     */
    template <>
    struct convert<Security_system::X_ray>
    {
        static Node encode(const Security_system::X_ray &xray)
        {
            Node node;
            node["power"] = xray.get_power();
            node["slots"] = xray.get_slots();
            node["radius"] = xray.get_radius();
            node["state"] = xray.get_state();
            node["type"] = "X_ray";
            return node;
        }

        static bool decode(const Node &node, Security_system::X_ray &xray)
        {
            if (node["power"])
                xray.set_power(node["power"].as<unsigned>());
            if (node["slots"])
                xray.set_slots(node["slots"].as<unsigned>());
            if (node["radius"])
                xray.set_radius(node["radius"].as<unsigned>());
            if (node["state"])
            {
                bool state = node["state"].as<bool>();
                if (state)
                    xray.turn_on();
                else
                    xray.turn_off();
            }
            return true;
        }
    };

    /**
     * @brief Специализация для сохранения и загрузки Optical
     */
    template <>
    struct convert<Security_system::Optical>
    {
        static Node encode(const Security_system::Optical &optical)
        {
            Node node;
            node["power"] = optical.get_power();
            node["slots"] = optical.get_slots();
            node["radius"] = optical.get_radius();
            node["state"] = optical.get_state();
            node["type"] = "Optical";
            return node;
        }

        static bool decode(const Node &node, Security_system::Optical &optical)
        {
            if (node["power"])
                optical.set_power(node["power"].as<unsigned>());
            if (node["slots"])
                optical.set_slots(node["slots"].as<unsigned>());
            if (node["radius"])
                optical.set_radius(node["radius"].as<unsigned>());
            if (node["state"])
            {
                bool state = node["state"].as<bool>();
                if (state)
                    optical.turn_on();
                else
                    optical.turn_off();
            }
            return true;
        }
    };

    /**
     * @brief Специализация для сохранения и загрузки Military
     */
    template <>
    struct convert<Security_system::Military>
    {
        static Node encode(const Security_system::Military &military)
        {
            Node node;
            node["power"] = military.get_power();
            node["slots"] = military.get_slots();
            node["radius"] = military.get_radius();
            node["state"] = military.get_state();
            node["time_charge"] = military.get_time();
            node["type"] = "Military";
            return node;
        }

        static bool decode(const Node &node, Security_system::Military &military)
        {
            if (node["power"])
                military.set_power(node["power"].as<unsigned>());
            if (node["slots"])
                military.set_slots(node["slots"].as<unsigned>());
            if (node["radius"])
                military.set_radius(node["radius"].as<unsigned>());
            if (node["state"])
            {
                bool state = node["state"].as<bool>();
                if (state)
                    military.turn_on();
                else
                    military.turn_off();
            }
            if (node["time_charge"])
                military.set_time(node["time_charge"].as<unsigned>());
            return true;
        }
    };
}