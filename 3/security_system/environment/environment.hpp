#pragma once

#include <iostream>
#include <list>
#include <vector>
#include <memory>
#include <typeinfo>
#include <algorithm>

#include "../suciruty_system.hpp"
#include "../component/base/component.hpp"

namespace Security_system
{
    /**
     * @class Environment
     * @brief Класс, представляющий игровое окружение/карту для системы безопасности.
     *
     * @details Environment представляет собой двумерную карту размера X×Y, на которой
     * размещаются различные компоненты системы безопасности (платформы, злоумышленники, стены).
     * Класс управляет позиционированием компонентов на карте и предоставляет методы
     * для взаимодействия с ними.
     *
     * @note Класс не поддерживает копирование (copy semantics), но поддерживает перемещение.
     */
    class Environment
    {
    private:
        std::pair<size_t, size_t> size;            ///< Размеры карты (ширина, высота)
        std::vector<std::vector<std::shared_ptr<Component>>> map; ///< Двумерная карта указателей на компоненты

    public:
        Environment() = default;
        /**
         * @brief Конструктор класса Environment.
         *
         * @param x Ширина карты (количество столбцов)
         * @param y Высота карты (количество строк)
         *
         * @details Создает карту заданного размера и инициализирует все ячейки значением nullptr.
         *
         * @throw std::bad_alloc Если недостаточно памяти для создания карты.
         */
        Environment(size_t x, size_t y)
        {
            size = std::make_pair(x, y);
            map.resize(x);
            for (size_t i = 0; i < x; i++)
                map[i].resize(y, nullptr);
        };

        /**
         * @brief Деструктор класса Environment (по умолчанию).
         *
         * @note Деструктор не удаляет компоненты, хранящиеся на карте.
         * Управление памятью компонентов должно осуществляться вызывающим кодом.
         */
        ~Environment() = default;

        /**
         * @brief Удаленный конструктор копирования.
         *
         * @details Копирование объектов Environment запрещено для предотвращения
         * дублирования указателей на компоненты.
         */
        Environment(const Environment &) = delete;

        /**
         * @brief Удаленный оператор присваивания.
         *
         * @details Присваивание объектов Environment запрещено для предотвращения
         * дублирования указателей на компоненты.
         */
        Environment &operator=(const Environment &) = delete;

        /**
         * @brief Конструктор перемещения (по умолчанию).
         *
         * @details Перемещает владение картой и ее содержимым в новый объект.
         */
        Environment(Environment &&) = default;

        /**
         * @brief Оператор перемещения (по умолчанию).
         *
         * @details Перемещает владение картой и ее содержимым в текущий объект.
         */
        Environment &operator=(Environment &&) = default;

        /**
         * @brief Получить копию карты окружения.
         *
         * @return std::vector<std::vector<Component *>> Копия двумерной карты указателей на компоненты.
         *
         * @note Возвращается копия карты, изменения в которой не влияют на оригинал.
         */
        std::vector<std::vector<std::shared_ptr<Component>>> get_map() const noexcept { return map; }

        void set_size(size_t x, size_t y)
        {
            size = std::make_pair(x, y);
            map.resize(x);
            for (size_t i = 0; i < x; i++)
                map[i].resize(y, nullptr);
        }

        /**
         * @brief Добавить компонент на карту.
         *
         * @param comp Указатель на добавляемый компонент.
         *
         * @details Компонент добавляется в позицию, полученную вызовом comp->get_pos().
         * Если позиция выходит за границы карты или уже занята другим компонентом,
         * добавление не производится.
         *
         * @warning Метод не проверяет валидность указателя comp.
         * @warning Метод не управляет памятью компонента.
         */
        void add_component(std::shared_ptr<Component> comp);

        /**
         * @brief Проверить, пуста ли ячейка на карте.
         *
         * @param x Координата X ячейки (столбец)
         * @param y Координата Y ячейки (строка)
         * @return true если ячейка пуста (содержит nullptr), false в противном случае.
         *
         * @note Если координаты выходят за границы карты, возвращает false.
         */
        bool is_empty(size_t x, size_t y) const;

        /**
         * @brief Получить размеры карты.
         *
         * @return std::pair<size_t, size_t> Пара (ширина, высота) карты.
         */
        std::pair<size_t, size_t> get_size() const { return size; }

        /**
         * @brief Поменять местами два компонента на карте.
         *
         * @param p1 Позиция первого компонента
         * @param p2 Позиция второго компонента
         *
         * @details Меняет местами указатели в указанных позициях на карте.
         *
         * @warning Не проверяет выход за границы карты.
         * @warning Не проверяет, содержатся ли компоненты в указанных позициях.
         */
        void change_pos(std::pair<size_t, size_t> p1, std::pair<size_t, size_t> p2)
        {
            std::swap(map[p1.first][p1.second], map[p2.first][p2.second]);
        }

        /**
         * @brief Оператор доступа к компоненту по позиции (неконстантная версия).
         *
         * @param pos Позиция на карте в виде пары (x, y)
         * @return Component*& Ссылка на указатель на компонент в указанной позиции.
         *
         * @throw std::out_of_range Если позиция выходит за границы карты.
         *
         * @note Возвращает ссылку на указатель, что позволяет изменять содержимое ячейки.
         */
        std::shared_ptr<Component> &operator[](const std::pair<size_t, size_t> &pos)
        {
            if (pos.first >= size.first || pos.second >= size.second)
            {
                throw std::out_of_range("Position out of range");
            }

            return map[pos.first][pos.second];
        }

        
    };
}