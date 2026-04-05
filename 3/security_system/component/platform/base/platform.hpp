#pragma once

#include <iostream>
#include <string>
#include <memory>

#include "../../base/component.hpp"
#include "../../../module/base/module.hpp"
#include "../../../suciruty_system.hpp"

namespace Security_system
{
    class Platform : public Component
    {
    private:
        std::string description;
        unsigned energy_level;
        unsigned capacity;

        std::vector<std::shared_ptr<Module>> modules;

    public:
        Platform() : description(""), energy_level(0), capacity(0) {}

        Platform(const std::string &desc, unsigned energy, unsigned cap)
            : description(desc), energy_level(energy), capacity(cap) {}

        Platform(const std::string &desc, unsigned energy, unsigned cap, std::pair<size_t, size_t> p)
            : Component(p), description(desc), energy_level(energy), capacity(cap) {}

        Platform(const Platform &other)
            : Component(other),
              description(other.description),
              energy_level(other.energy_level),
              capacity(other.capacity),
              modules(other.modules)
        {
        }

        Platform(Platform &&other) noexcept
        {
            std::swap(description, other.description);
            std::swap(energy_level, other.energy_level);
            std::swap(capacity, other.capacity);
            std::swap(modules, other.modules);
        }

        Platform &operator=(const Platform &other)
        {
            if (this != &other)
            {
                description = other.description;
                energy_level = other.energy_level;
                capacity = other.capacity;
                modules = other.modules;
            }
            return *this;
        }

        ~Platform() = default;

        std::string get_desc() const { return description; }
        unsigned get_energy() const { return energy_level; }
        unsigned get_capacity() const { return capacity; }
        void set_desc(const std::string &desc) { description = desc; }
        void set_energy(unsigned e) { energy_level = e; }
        void set_capacity(unsigned c) { capacity = c; }

        std::vector<std::shared_ptr<Module>> get_modules() const noexcept { return modules; }

        void add_module(std::shared_ptr<Module> module);

        void remove_module(size_t index);

        void print(std::ostream &out) const override
        {
            out << "P";
        }

        std::shared_ptr<Module> operator[](const size_t &pos)
        {
            return modules[pos];
        }

        const std::shared_ptr<Module> operator[](const size_t &pos) const
        {
            return modules[pos];
        }

        std::vector<std::shared_ptr<Network>> find_network() const noexcept;

        std::vector<std::shared_ptr<Military>> find_military() const noexcept;

        std::vector<std::shared_ptr<Sensor>> find_sensor() const noexcept;
    };
}