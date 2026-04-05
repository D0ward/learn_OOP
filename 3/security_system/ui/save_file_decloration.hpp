#pragma once
#include <yaml-cpp/yaml.h>
#include <memory>

namespace Security_system
{
    class Component;
    class Platform;
    class Module;
    class Intruder;
    class Wall;
    class Static;
    class Mobile;
    class Network;
    class X_ray;
    class Optical;
    class Military;
    class Environment;
}

namespace YAML
{
    /**
     * @brief Предварительные объявления специализаций для классов системы безопасности
     * 
     * Эти объявления необходимы для правильной компиляции шаблонов
     * и предотвращения циклических зависимостей.
     */
    template <>
    struct convert<Security_system::Component>;
    
    template <>
    struct convert<Security_system::Platform>;
    
    template <>
    struct convert<Security_system::Module>;
    
    template <>
    struct convert<Security_system::Intruder>;
    
    template <>
    struct convert<Security_system::Wall>;
    
    template <>
    struct convert<Security_system::Static>;
    
    template <>
    struct convert<Security_system::Mobile>;
    
    template <>
    struct convert<Security_system::Network>;
    
    template <>
    struct convert<Security_system::X_ray>;
    
    template <>
    struct convert<Security_system::Optical>;
    
    template <>
    struct convert<Security_system::Military>;
    
    template <>
    struct convert<Security_system::Environment>;
}