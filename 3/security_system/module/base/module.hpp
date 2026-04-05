#pragma once

#include <vector>
#include <memory>
#include <list>
#include <algorithm>

namespace Security_system
{
    /**
     * @brief Абстрактный базовый класс модуля системы безопасности.
     *
     * Module представляет собой базовый компонент, который может быть
     * установлен на платформу и обладает определенными характеристиками
     * и функциональностью.
     */
    class Module
    {
    private:
        unsigned power_consumption; ///< Потребляемая мощность модуля
        unsigned count_slots;       ///< Количество занимаемых слотов
        unsigned radius;            ///< Радиус действия модуля

    protected:
        bool state = true; ///< Состояние модуля (включен/выключен)

    public:
        /**
         * @brief Конструктор Module.
         *
         * @param power Потребляемая мощность
         * @param cnt Количество занимаемых слотов
         * @param r Радиус действия
         */
        Module(unsigned power, unsigned cnt, unsigned r) : power_consumption(power), count_slots(cnt), radius(r) {}

        unsigned get_power() const { return power_consumption; }
        unsigned get_slots() const { return count_slots; }
        unsigned get_radius() const { return radius; }
        bool get_state() const { return state; }
        void set_power(unsigned p) { power_consumption = p; }
        void set_slots(unsigned s) { count_slots = s; }
        void set_radius(unsigned r) { radius = r; }

        ~Module() = default;

        /**
         * @brief Включает модуль (чисто виртуальная функция).
         */
        virtual void turn_on() = 0;

        /**
         * @brief Выключает модуль (чисто виртуальная функция).
         */
        virtual void turn_off() = 0;
    };
}