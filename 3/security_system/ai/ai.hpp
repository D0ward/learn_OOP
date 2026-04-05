#pragma once

#include <vector>
#include <memory>
#include "../suciruty_system.hpp"

namespace Security_system
{
    /**
     * @brief Класс искусственного интеллекта для управления системой безопасности.
     *
     * AI отвечает за автоматическое управление платформами безопасности,
     * обнаружение и нейтрализацию нарушителей.
     */
    class AI
    {
        std::shared_ptr<Environment> env; ///< Указатель на окружение системы безопасности

    private:
        std::vector<std::shared_ptr<Platform>> connected_platform; ///< Список подключенных платформ

        /**
         * @brief Нейтрализует нарушителей на конкретной платформе.
         *
         * @param platform Указатель на платформу для обработки
         */
        void kill_intruders(std::shared_ptr<Platform>platform) const;

    public:
        /**
         * @brief Конструктор AI.
         *
         * @param e Указатель на окружение системы
         */
        AI(std::shared_ptr<Environment> e) : env(e) {}

        /**
         * @brief Подключает платформу к системе AI.
         *
         * @param platform Указатель на платформу для подключения
         */
        void connect_platform(std::shared_ptr<Platform> platform);

        /**
         * @brief Нейтрализует нарушителей на всех подключенных платформах.
         */
        void kill_intruders_all() const;

        void set_env(std::shared_ptr<Environment> e) { env = e; }
    };
}