#pragma once

#include <vector>
#include <memory>
#include <string>
#include <iostream>

#include "../suciruty_system.hpp"
#include "controller.hpp"

namespace Security_system
{
    /**
     * @class App
     * @brief Главный класс приложения системы безопасности
     *
     * @details App управляет основным циклом приложения, отображением карты,
     * обработкой пользовательского ввода и координацией работы контроллера.
     * Предоставляет текстовый интерфейс для взаимодействия с системой безопасности.
     */
    class App
    {
    private:
        std::string config_file_name = "save.yml"; ///< Имя файла для сохранения/загрузки
        Controller controller;                     ///< Контроллер системы безопасности

        /**
         * @brief Выводит текущую карту системы в консоль
         */
        void print_map();

        /**
         * @brief Отображает главное меню и обрабатывает выбор пользователя
         * @return int 1 - выход из приложения, 0 - продолжение работы
         */
        int menu_main();

        /**
         * @brief Меню добавления нового компонента
         */
        void menu_add_comp();

        /**
         * @brief Меню перемещения мобильной платформы
         */
        void menu_move();

        /**
         * @brief Меню добавления модуля к платформе
         */
        void menu_add_module();

        /**
         * @brief Меню подключения платформ через сетевые модули
         */
        void menu_connect_network();

    public:
        /**
         * @brief Конструктор по умолчанию
         * @details Запрашивает у пользователя размер карты и инициализирует систему
         */
        App()
        {
            std::cout << "Введите размер карты: ";
            size_t x, y;
            std::cin >> x >> y;
            controller.set_size(x, y);
        };

        /**
         * @brief Конструктор с загрузкой из файла
         * @param name Имя файла для загрузки конфигурации
         */
        App(const std::string &name) : config_file_name(name) 
        { 
            controller.load_file(config_file_name); 
        }

        /**
         * @brief Запускает главный цикл приложения
         */
        void run();
    };
}