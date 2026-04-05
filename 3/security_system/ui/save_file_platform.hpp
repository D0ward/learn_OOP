#pragma once
#include <yaml-cpp/yaml.h>
#include <memory>

#include "../component/platform/base/platform.hpp"
#include "../component/platform/static/static.hpp"
#include "../component/platform/mobile/mobile.hpp"
#include "save_file_module.hpp"

namespace Security_system
{
    /**
     * @brief Фабрика для создания объектов из YAML
     * 
     * ObjectFactory предоставляет статические методы для создания
     * компонентов и модулей на основе данных из YAML-узлов.
     * Все методы возвращают shared_ptr для автоматического управления памятью.
     */
    class ObjectFactory
    {
    public:
        /**
         * @brief Создает компонент из YAML-узла
         * 
         * @param node YAML-узел с данными компонента
         * @return std::shared_ptr<Component> Указатель на созданный компонент
         */
        static std::shared_ptr<Component> createComponent(const YAML::Node &node)
        {
            if (!node["type"])
                return nullptr;

            std::string type = node["type"].as<std::string>();
            std::pair<size_t, size_t> pos;

            if (node["position"])
            {
                pos.first = node["position"]["x"].as<size_t>();
                pos.second = node["position"]["y"].as<size_t>();
            }

            if (type == "Intruder")
            {
                return std::make_shared<Intruder>(pos);
            }
            else if (type == "Wall")
            {
                return std::make_shared<Wall>(pos);
            }
            else if (type == "Static")
            {
                auto static_plat = std::make_shared<Static>(
                    node["description"].as<std::string>(),
                    node["energy"].as<unsigned>(),
                    node["capacity"].as<unsigned>(),
                    pos);

                if (node["modules"])
                {
                    for (const auto &moduleNode : node["modules"])
                    {
                        auto module = createModule(moduleNode);
                        if (module)
                        {
                            static_plat->add_module(module);
                        }
                    }
                }

                return static_plat;
            }
            else if (type == "Mobile")
            {
                auto mobile = std::make_shared<Mobile>(
                    node["description"].as<std::string>(),
                    node["energy"].as<unsigned>(),
                    node["capacity"].as<unsigned>(),
                    node["speed"].as<unsigned>(),
                    pos);

                if (node["modules"])
                {
                    for (const auto &moduleNode : node["modules"])
                    {
                        auto module = createModule(moduleNode);
                        if (module)
                        {
                            mobile->add_module(module);
                        }
                    }
                }

                return mobile;
            }

            return nullptr;
        }

        /**
         * @brief Создает модуль из YAML-узла
         * 
         * @param node YAML-узел с данными модуля
         * @return std::shared_ptr<Module> Указатель на созданный модуль
         */
        static std::shared_ptr<Module> createModule(const YAML::Node &node)
        {
            if (!node["type"])
                return nullptr;

            std::string type = node["type"].as<std::string>();

            if (type == "Network")
            {
                auto network = std::make_shared<Network>(
                    node["power"].as<unsigned>(),
                    node["slots"].as<unsigned>(),
                    node["radius"].as<unsigned>());

                if (node["state"])
                {
                    bool state = node["state"].as<bool>();
                    if (state)
                        network->turn_on();
                }
                return network;
            }
            else if (type == "X_ray")
            {
                auto xray = std::make_shared<X_ray>(
                    node["power"].as<unsigned>(),
                    node["slots"].as<unsigned>(),
                    node["radius"].as<unsigned>());

                if (node["state"])
                {
                    bool state = node["state"].as<bool>();
                    if (state)
                        xray->turn_on();
                }
                return xray;
            }
            else if (type == "Optical")
            {
                auto optical = std::make_shared<Optical>(
                    node["power"].as<unsigned>(),
                    node["slots"].as<unsigned>(),
                    node["radius"].as<unsigned>());

                if (node["state"])
                {
                    bool state = node["state"].as<bool>();
                    if (state)
                        optical->turn_on();
                }
                return optical;
            }
            else if (type == "Military")
            {
                auto military = std::make_shared<Military>(
                    node["power"].as<unsigned>(),
                    node["slots"].as<unsigned>(),
                    node["radius"].as<unsigned>(),
                    node["time_charge"].as<unsigned>());

                if (node["state"])
                {
                    bool state = node["state"].as<bool>();
                    if (state)
                        military->turn_on();
                }
                return military;
            }

            return nullptr;
        }
    };
}

namespace YAML
{
    /**
     * @brief Специализация для сохранения и загрузки Platform
     */
    template <>
    struct convert<Security_system::Platform>
    {
        static Node encode(const Security_system::Platform &platform)
        {
            Node node;
            auto pos = platform.get_pos();
            node["position"]["x"] = pos.first;
            node["position"]["y"] = pos.second;
            node["description"] = platform.get_desc();
            node["energy"] = platform.get_energy();
            node["capacity"] = platform.get_capacity();
            node["type"] = "Platform";

            Node modulesNode;
            auto modules = platform.get_modules();
            for (const auto &module : modules)
            {
                if (auto network = std::dynamic_pointer_cast<Security_system::Network>(module))
                {
                    modulesNode.push_back(convert<Security_system::Network>::encode(*network));
                }
                else if (auto xray = std::dynamic_pointer_cast<Security_system::X_ray>(module))
                {
                    modulesNode.push_back(convert<Security_system::X_ray>::encode(*xray));
                }
                else if (auto optical = std::dynamic_pointer_cast<Security_system::Optical>(module))
                {
                    modulesNode.push_back(convert<Security_system::Optical>::encode(*optical));
                }
                else if (auto military = std::dynamic_pointer_cast<Security_system::Military>(module))
                {
                    modulesNode.push_back(convert<Security_system::Military>::encode(*military));
                }
            }
            node["modules"] = modulesNode;

            return node;
        }

        static bool decode(const Node &node, Security_system::Platform &platform)
        {
            if (node["position"])
            {
                size_t x = node["position"]["x"].as<size_t>();
                size_t y = node["position"]["y"].as<size_t>();
                platform.set_pos({x, y});
            }

            if (node["description"])
                platform.set_desc(node["description"].as<std::string>());
            if (node["energy"])
                platform.set_energy(node["energy"].as<unsigned>());
            if (node["capacity"])
                platform.set_capacity(node["capacity"].as<unsigned>());

            return true;
        }
    };

    /**
     * @brief Специализация для сохранения и загрузки Static
     */
    template <>
    struct convert<Security_system::Static>
    {
        static Node encode(const Security_system::Static &static_plat)
        {
            Node node;
            auto pos = static_plat.get_pos();
            node["position"]["x"] = pos.first;
            node["position"]["y"] = pos.second;
            node["description"] = static_plat.get_desc();
            node["energy"] = static_plat.get_energy();
            node["capacity"] = static_plat.get_capacity();
            node["type"] = "Static";

            Node modulesNode;
            auto modules = static_plat.get_modules();
            for (const auto &module : modules)
            {
                if (auto network = std::dynamic_pointer_cast<Security_system::Network>(module))
                {
                    modulesNode.push_back(convert<Security_system::Network>::encode(*network));
                }
                else if (auto xray = std::dynamic_pointer_cast<Security_system::X_ray>(module))
                {
                    modulesNode.push_back(convert<Security_system::X_ray>::encode(*xray));
                }
                else if (auto optical = std::dynamic_pointer_cast<Security_system::Optical>(module))
                {
                    modulesNode.push_back(convert<Security_system::Optical>::encode(*optical));
                }
                else if (auto military = std::dynamic_pointer_cast<Security_system::Military>(module))
                {
                    modulesNode.push_back(convert<Security_system::Military>::encode(*military));
                }
            }
            node["modules"] = modulesNode;

            return node;
        }

        static bool decode(const Node &node, Security_system::Static &static_plat)
        {
            if (node["position"])
            {
                size_t x = node["position"]["x"].as<size_t>();
                size_t y = node["position"]["y"].as<size_t>();
                static_plat.set_pos({x, y});
            }

            if (node["description"])
                static_plat.set_desc(node["description"].as<std::string>());
            if (node["energy"])
                static_plat.set_energy(node["energy"].as<unsigned>());
            if (node["capacity"])
                static_plat.set_capacity(node["capacity"].as<unsigned>());

            return true;
        }
    };

    /**
     * @brief Специализация для сохранения и загрузки Mobile
     */
    template <>
    struct convert<Security_system::Mobile>
    {
        static Node encode(const Security_system::Mobile &mobile)
        {
            Node node;
            auto pos = mobile.get_pos();
            node["position"]["x"] = pos.first;
            node["position"]["y"] = pos.second;
            node["description"] = mobile.get_desc();
            node["energy"] = mobile.get_energy();
            node["capacity"] = mobile.get_capacity();
            node["speed"] = mobile.get_speed();
            node["type"] = "Mobile";

            Node modulesNode;
            auto modules = mobile.get_modules();
            for (const auto &module : modules)
            {
                if (auto network = std::dynamic_pointer_cast<Security_system::Network>(module))
                {
                    modulesNode.push_back(convert<Security_system::Network>::encode(*network));
                }
                else if (auto xray = std::dynamic_pointer_cast<Security_system::X_ray>(module))
                {
                    modulesNode.push_back(convert<Security_system::X_ray>::encode(*xray));
                }
                else if (auto optical = std::dynamic_pointer_cast<Security_system::Optical>(module))
                {
                    modulesNode.push_back(convert<Security_system::Optical>::encode(*optical));
                }
                else if (auto military = std::dynamic_pointer_cast<Security_system::Military>(module))
                {
                    modulesNode.push_back(convert<Security_system::Military>::encode(*military));
                }
            }
            node["modules"] = modulesNode;

            return node;
        }

        static bool decode(const Node &node, Security_system::Mobile &mobile)
        {
            if (node["position"])
            {
                size_t x = node["position"]["x"].as<size_t>();
                size_t y = node["position"]["y"].as<size_t>();
                mobile.set_pos({x, y});
            }

            if (node["description"])
                mobile.set_desc(node["description"].as<std::string>());
            if (node["energy"])
                mobile.set_energy(node["energy"].as<unsigned>());
            if (node["capacity"])
                mobile.set_capacity(node["capacity"].as<unsigned>());
            if (node["speed"])
                mobile.set_speed(node["speed"].as<unsigned>());

            return true;
        }
    };
}