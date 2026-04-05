#pragma once

#include <ostream>
#include <vector>
#include "../../suciruty_system.hpp"

namespace Security_system
{
    /**
     * @brief Абстрактный базовый класс компонента системы безопасности.
     *
     * Component представляет собой базовый элемент, который может быть
     * размещен на карте системы безопасности и имеет позицию.
     */
    class Component
    {
    protected:
        std::pair<size_t, size_t> position = std::make_pair(0, 0); ///< Позиция компонента на карте

    public:
        Component() = default;

        /**
         * @brief Конструктор с указанием позиции.
         *
         * @param p Позиция компонента
         */
        Component(std::pair<size_t, size_t> p) : position(p) {}

        ~Component() = default;
        /**
         * @brief Возвращает позицию компонента.
         *
         * @return  std::pair<size_t, size_t> Позиция компонента
         */
        std::pair<size_t, size_t> get_pos() const { return position; }

        void set_pos(std::pair<size_t, size_t> p) { position = p; }

        /**
         * @brief Устанавливает новую позицию компонента в среде.
         *
         * @param pos Новая позиция
         * @param env Ссылка на окружение
         */
        void set_pos(std::pair<size_t, size_t> pos, std::shared_ptr<Environment> env);

        /**
         * @brief Инициализирует позицию компонента (без проверок окружения).
         *
         * @param pos Позиция для инициализации
         */
        void init_pos(std::pair<size_t, size_t> pos) { position = pos; }

        /**
         * @brief Выводит информацию о компоненте в поток.
         *
         * @param out Выходной поток
         */
        virtual void print(std::ostream &out) const
        {
            out << " ";
        };
    };
}