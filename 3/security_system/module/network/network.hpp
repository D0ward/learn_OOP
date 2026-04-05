#pragma once
#include "../base/module.hpp"
#include "../../component/platform/base/platform.hpp"
#include "../../table/table.hpp"

namespace Security_system
{
    /**
     * @class Network
     * @brief Класс сетевого модуля для связи между платформами.
     *
     * @details Network модуль позволяет платформам обнаруживать друг друга,
     * устанавливать сетевые соединения и обмениваться информацией.
     * Модуль поддерживает таблицу коммутации для обнаружения соседних платформ
     * и активные сессии для подключенных платформ.
     *
     * @inherits Module
     */
    class Network : public Module
    {
    private:
        Table<std::shared_ptr<Platform>> active_session;        ///< Таблица активных сетевых сессий (подключенные платформы)
        std::vector<std::shared_ptr<Platform>> switching_table; ///< Таблица коммутации (обнаруженные платформы в радиусе действия)

    public:
        /**
         * @brief Конструктор сетевого модуля.
         *
         * @param power Потребляемая мощность модуля
         * @param cnt Количество занимаемых слотов на платформе
         * @param r Радиус действия сетевого модуля
         *
         * @details Создает сетевой модуль с заданными характеристиками.
         * По умолчанию модуль находится в выключенном состоянии (state = false).
         */
        Network(unsigned power, unsigned cnt, unsigned r) : Module(power, cnt, r) {}

        /**
         * @brief Создать таблицу коммутации на основе текущего окружения.
         *
         * @param map Карта окружения для сканирования
         * @param pos Позиция платформы, на которой установлен модуль
         *
         * @details Метод сканирует окружение в радиусе действия модуля и добавляет
         * в таблицу коммутации все обнаруженные платформы, имеющие сетевые модули.
         * Сканирование производится по 8 направлениям на заданном расстоянии.
         *
         * @note Метод не генерирует исключения (noexcept).
         * @note Если карта пуста, метод завершает работу без изменений.
         */
        void create_switching_table(const std::vector<std::vector<std::shared_ptr<Component>>> &map,
                                    std::pair<size_t, size_t> pos) noexcept;

        /**
         * @brief Подключиться к платформе по индексу из таблицы коммутации.
         *
         * @param ind Индекс платформы в таблице коммутации
         *
         * @details Добавляет платформу с указанным индексом в список активных сессий.
         *
         * @throw std::out_of_range Если индекс выходит за границы таблицы коммутации.
         * @throw std::runtime_error Если возникают другие ошибки при подключении.
         */
        void connect(size_t ind);

       

        /**
         * @brief Получить таблицу активных сессий.
         *
         * @return Table<const Platform *> Копия таблицы активных сетевых сессий.
         *
         * @note Возвращается копия таблицы, изменения в которой не влияют на оригинал.
         */
        Table<std::shared_ptr<Platform>> get_active_session()
        {

            return active_session;
        }

        std::vector<std::shared_ptr<Platform>> get_switching_table() { return switching_table; }

        /**
         * @brief Включить сетевой модуль.
         *
         * @details Устанавливает состояние модуля в true.
         * При включении модуль начинает сканировать окружение и может устанавливать соединения.
         *
         * @override
         */
        void turn_on() override
        {
            state = true;
        }

        /**
         * @brief Выключить сетевой модуль.
         *
         * @details Устанавливает состояние модуля в false.
         * При выключении модуль прекращает все активные соединения.
         *
         * @override
         */
        void turn_off() override { state = false; }
    };
}