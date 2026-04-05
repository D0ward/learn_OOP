#pragma once
#include <yaml-cpp/yaml.h>
#include <memory>

#include "../component/platform/base/platform.hpp"
#include "../component/intruder/intruder.hpp"
#include "../component/wall/wall.hpp"

namespace YAML
{
    /**
     * @brief Специализация для сохранения и загрузки Component
     */
    template <>
    struct convert<Security_system::Component>
    {
        static Node encode(const Security_system::Component &comp)
        {
            Node node;
            auto pos = comp.get_pos();
            node["position"]["x"] = pos.first;
            node["position"]["y"] = pos.second;
            node["type"] = "Component";
            return node;
        }

        static bool decode(const Node &node, Security_system::Component &comp)
        {
            if (node["position"])
            {
                size_t x = node["position"]["x"].as<size_t>();
                size_t y = node["position"]["y"].as<size_t>();
                comp.set_pos({x, y});
            }
            return true;
        }
    };

    /**
     * @brief Специализация для сохранения и загрузки Intruder
     */
    template <>
    struct convert<Security_system::Intruder>
    {
        static Node encode(const Security_system::Intruder &intruder)
        {
            Node node;
            auto pos = intruder.get_pos();
            node["position"]["x"] = pos.first;
            node["position"]["y"] = pos.second;
            node["type"] = "Intruder";
            return node;
        }

        static bool decode(const Node &node, Security_system::Intruder &intruder)
        {
            if (node["position"])
            {
                size_t x = node["position"]["x"].as<size_t>();
                size_t y = node["position"]["y"].as<size_t>();
                intruder.set_pos({x, y});
            }
            return true;
        }
    };

    /**
     * @brief Специализация для сохранения и загрузки Wall
     */
    template <>
    struct convert<Security_system::Wall>
    {
        static Node encode(const Security_system::Wall &wall)
        {
            Node node;
            auto pos = wall.get_pos();
            node["position"]["x"] = pos.first;
            node["position"]["y"] = pos.second;
            node["type"] = "Wall";
            return node;
        }

        static bool decode(const Node &node, Security_system::Wall &wall)
        {
            if (node["position"])
            {
                size_t x = node["position"]["x"].as<size_t>();
                size_t y = node["position"]["y"].as<size_t>();
                wall.set_pos({x, y});
            }
            return true;
        }
    };
}