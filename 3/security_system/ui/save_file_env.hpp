#pragma once
#include <yaml-cpp/yaml.h>
#include <memory>

#include "../environment/environment.hpp"
#include "save_file_comp.hpp"
#include "save_file_platform.hpp"

namespace YAML
{
    /**
     * @brief Специализация для сохранения и загрузки Environment
     * 
     * Предоставляет методы для сериализации и десериализации
     * всего окружения системы безопасности, включая все компоненты
     * и их расположение на карте.
     */
    template <>
    struct convert<Security_system::Environment>
    {
        /**
         * @brief Сериализует Environment в YAML-узел
         * 
         * @param env Ссылка на Environment для сохранения
         * @return Node YAML-узел с данными окружения
         */
        static Node encode(const Security_system::Environment &env)
        {
            Node node;
            auto size = env.get_size();
            node["metadata"]["width"] = size.first;
            node["metadata"]["height"] = size.second;
            node["metadata"]["version"] = "1.0";

            Node componentsNode;
            auto map = env.get_map();
            for (size_t i = 0; i < map.size(); ++i)
            {
                for (size_t j = 0; j < map[i].size(); ++j)
                {
                    if (map[i][j])
                    {
                        Node componentNode;

                        if (auto intruder = std::dynamic_pointer_cast<Security_system::Intruder>(map[i][j]))
                        {
                            componentNode = convert<Security_system::Intruder>::encode(*intruder);
                        }
                        else if (auto wall = std::dynamic_pointer_cast<Security_system::Wall>(map[i][j]))
                        {
                            componentNode = convert<Security_system::Wall>::encode(*wall);
                        }
                        else if (auto static_plat = std::dynamic_pointer_cast<Security_system::Static>(map[i][j]))
                        {
                            componentNode = convert<Security_system::Static>::encode(*static_plat);
                        }
                        else if (auto mobile = std::dynamic_pointer_cast<Security_system::Mobile>(map[i][j]))
                        {
                            componentNode = convert<Security_system::Mobile>::encode(*mobile);
                        }

                        if (!componentNode.IsNull())
                        {
                            componentNode["grid_x"] = i;
                            componentNode["grid_y"] = j;
                            componentsNode.push_back(componentNode);
                        }
                    }
                }
            }

            node["components"] = componentsNode;
            return node;
        }

        /**
         * @brief Десериализует Environment из YAML-узла
         * 
         * @param node YAML-узел с данными окружения
         * @param env Ссылка на Environment для загрузки данных
         * @return true Если десериализация успешна
         * @return false Если десериализация не удалась
         */
        static bool decode(const Node &node, Security_system::Environment &env)
        {
            if (node["metadata"])
            {
                size_t width = node["metadata"]["width"].as<size_t>();
                size_t height = node["metadata"]["height"].as<size_t>();
                env.set_size(width, height);
            }

            if (node["components"])
            {
                for (const auto &componentNode : node["components"])
                {
                    auto component = Security_system::ObjectFactory::createComponent(componentNode);
                    if (component)
                    {
                        env.add_component(component);
                    }
                }
            }

            return true;
        }
    };
}