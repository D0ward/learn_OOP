#pragma once

#include "../base/component.hpp"

namespace Security_system
{
    /**
     * @brief Класс, представляющий стену в системе безопасности.
     *
     * Wall является препятствием, которое блокирует перемещение
     * нарушителей и может ограничивать обзор сенсоров.
     */
    class Wall : public Component
    {
    public:
        Wall() = default;

        Wall(std::pair<size_t, size_t> p) : Component(p) {}
        /**
         * @brief Выводит информацию о стене в поток.
         *
         * @param out Выходной поток
         */
        void print(std::ostream &out) const override { out << "W"; }
    };
}