#pragma once

#include "../../../suciruty_system.hpp"

namespace Security_system
{
    /**
     * @brief Класс статической платформы системы безопасности.
     *
     * Static представляет собой неподвижную платформу, которая
     * устанавливается в фиксированной позиции для постоянной защиты.
     */
    class Static : public Platform
    {
    public:
        /**
         * @brief Конструктор по умолчанию.
         */
        Static() : Platform() {}

        /**
         * @brief Конструктор с параметрами.
         *
         * @param desc Описание платформы
         * @param energy Уровень начальной энергии
         * @param cap Вместимость платформы
         */
        Static(const std::string &desc, unsigned energy, unsigned cap)
            : Platform(desc, energy, cap) {}

        Static(const std::string &desc, unsigned energy, unsigned cap, std::pair<size_t, size_t> p)
            : Platform(desc, energy, cap, p) {}
        void print(std::ostream &o) const override { o << 'S'; };
    };
}