#pragma once

#include "../../component/intruder/intruder.hpp"
#include "../base/module.hpp"

namespace Security_system
{
    /**
     * @brief Абстрактный базовый класс сенсора для обнаружения нарушителей.
     *
     * Sensor представляет собой модуль, способный сканировать окружающее
     * пространство и обнаруживать нарушителей.
     */
    class Sensor : public Module
    {
    public:
        /**
         * @brief Конструктор Sensor.
         *
         * @param power Потребляемая мощность
         * @param cnt Количество слотов
         * @param r Радиус действия
         */
        Sensor(unsigned power, unsigned cnt, unsigned r) : Module(power, cnt, r) {}

        /**
         * @brief Включает сенсор.
         */
        void turn_on() override { state = true; }

        /**
         * @brief Выключает сенсор.
         */
        void turn_off() override { state = false; }

        /**
         * @brief Сканирует область на наличие нарушителей.
         *
         * @param map Карта системы безопасности
         * @param pos Позиция сенсора на карте
         * @return std::list<Intruder *> Список обнаруженных нарушителей
         */
        [[nodiscard]] virtual std::list<std::shared_ptr<Intruder>> scan(std::vector<std::vector<std::shared_ptr<Component>>> &map, const std::pair<size_t, size_t> pos) const = 0;
    };

    /**
     * @brief Сенсор рентгеновского типа.
     *
     * X_ray способен обнаруживать нарушителей через препятствия.
     */
    class X_ray : public Sensor
    {
    public:
        /**
         * @brief Конструктор X_ray сенсора.
         *
         * @param power Потребляемая мощность
         * @param cnt Количество слотов
         * @param r Радиус действия
         */
        X_ray(unsigned power, unsigned cnt, unsigned r) : Sensor(power, cnt, r) {}

        /**
         * @brief Сканирует область с использованием рентгеновского излучения.
         *
         * @param map Карта системы безопасности
         * @param pos Позиция сенсора на карте
         * @return std::list<Intruder *> Список обнаруженных нарушителей
         */
        [[nodiscard]] std::list<std::shared_ptr<Intruder>> scan(std::vector<std::vector<std::shared_ptr<Component>>> &map, const std::pair<size_t, size_t> pos) const override;
    };

    /**
     * @brief Оптический сенсор.
     *
     * Optical использует видимый свет для обнаружения нарушителей.
     */
    class Optical : public Sensor
    {
    public:
        /**
         * @brief Конструктор Optical сенсора.
         *
         * @param power Потребляемая мощность
         * @param cnt Количество слотов
         * @param r Радиус действия
         */
        Optical(unsigned power, unsigned cnt, unsigned r) : Sensor(power, cnt, r) {}

        /**
         * @brief Сканирует область с использованием оптического датчика.
         *
         * @param map Карта системы безопасности
         * @param pos Позиция сенсора на карте
         * @return std::list<Intruder *> Список обнаруженных нарушителей
         */
        [[nodiscard]] std::list<std::shared_ptr<Intruder>> scan(std::vector<std::vector<std::shared_ptr<Component>>> &map, const std::pair<size_t, size_t> pos) const override;
    };
}
