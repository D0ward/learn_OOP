#pragma once

#include "../base/component.hpp"

namespace Security_system
{
    /**
     * @brief Класс, представляющий нарушителя в системе безопасности.
     *
     * Intruder - это сущность, которая пытается проникнуть в защищаемую зону
     * и может быть обнаружена и нейтрализована системой безопасности.
     */
    class Intruder : public Component
    {
    private:
        bool is_alive = true; ///< Флаг жизненного состояния нарушителя

    public:
        Intruder() = default;

        Intruder(std::pair<size_t, size_t> p) : Component(p) {}
        /**
         * @brief Нейтрализует нарушителя.
         */
        void kill() { is_alive = false; }

        /**
         * @brief Перемещает нарушителя в среде.
         *
         * @param env Ссылка на окружение системы
         */
        void move(std::shared_ptr<Environment> env);

        /**
         * @brief Выводит информацию о нарушителе в поток.
         *
         * @param out Выходной поток
         */
        void print(std::ostream &out) const override
        {
            if (!is_alive)
                out << "X";
            else
                out << "I";
        }

        bool get_alive() const noexcept { return is_alive; }
    };
}