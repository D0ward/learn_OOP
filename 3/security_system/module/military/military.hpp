#pragma once

#include <cmath>
#include "../base/module.hpp"
#include "../../component/intruder/intruder.hpp"

namespace Security_system
{
    /**
     * @brief Класс военного модуля для нейтрализации нарушителей.
     *
     * Military представляет собой модуль, способный нейтрализовать
     * обнаруженных нарушителей с использованием различных методов.
     */
    class Military : public Module
    {
    private:
        unsigned time_charge; ///< Время перезарядки модуля

        /**
         * @brief Процесс зарядки модуля.
         *
         * TODO: Реализовать функцию зарядки
         */
        void charge() {}

    public:
        /**
         * @brief Конструктор Military модуля.
         *
         * @param power Потребляемая мощность
         * @param cnt Количество слотов
         * @param r Радиус действия
         * @param time Время перезарядки
         */
        Military(unsigned power, unsigned cnt, unsigned r, unsigned time) : Module(power, cnt, r), time_charge(time) {}

        /**
         * @brief Включает военный модуль.
         */
        void turn_on() override { state = true; }

        /**
         * @brief Выключает военный модуль.
         */
        void turn_off() override { state = false; }

        unsigned get_time() const noexcept { return time_charge; }
        void set_time(unsigned s) { time_charge = s; }

        /**
         * @brief Нейтрализует нарушителя.
         *
         * @param intruder Указатель на нарушителя для нейтрализации
         * @param pos Позиция модуля
         */
        void kill_intruder(std::shared_ptr<Intruder> intruder, const std::pair<size_t, size_t> pos) const;
    };
}