#pragma once

#include <cmath>
#include "../base/platform.hpp"

#include "../../../suciruty_system.hpp"

namespace Security_system
{
    /**
     * @brief Класс мобильной платформы системы безопасности.
     *
     * Mobile представляет собой передвижную платформу, которая может
     * перемещаться по территории для усиления защиты или преследования нарушителей.
     */
    class Mobile : public Platform
    {
    private:
        unsigned speed; ///< Скорость перемещения платформы

    public:
        /**
         * @brief Конструктор по умолчанию.
         */
        Mobile() : Platform(), speed(0) {}

        /**
         * @brief Конструктор с параметрами.
         *
         * @param desc Описание платформы
         * @param energy Уровень начальной энергии
         * @param cap Вместимость платформы
         * @param spd Скорость перемещения
         */
        Mobile(const std::string &desc, unsigned energy, unsigned cap, unsigned spd)
            : Platform(desc, energy, cap), speed(spd) {}

        Mobile(const std::string &desc, unsigned energy, unsigned cap, unsigned spd, std::pair<size_t, size_t> p)
            : Platform(desc, energy, cap, p), speed(spd) {}
        /**
         * @brief Перемещает платформу в указанную позицию.
         *
         * @param env Ссылка на окружение системы
         * @param target Целевая позиция
         */
        void move(std::shared_ptr<Environment> env, std::pair<size_t, size_t> target);

        unsigned get_speed() const { return speed; }
        void set_speed(unsigned s) { speed = s; }

        void print(std::ostream &o) const override { o << 'M'; };
    };
}