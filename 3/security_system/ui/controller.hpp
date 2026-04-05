#pragma once

#include <vector>
#include <string>
#include <memory>
#include <fstream>

#include "../ai/ai.hpp"
#include "../component/platform/base/platform.hpp"
#include "../component/platform/static/static.hpp"
#include "../component/platform/mobile/mobile.hpp"
#include "../component/intruder/intruder.hpp"
#include "../component/wall/wall.hpp"
#include "../module/base/module.hpp"
#include "../module/sensor/sensor.hpp"
#include "../module/military/military.hpp"
#include "../module/network/network.hpp"
#include "../environment/environment.hpp"
#include "save_file.hpp"

namespace Security_system
{
    /**
     * @class Controller
     * @brief Центральный контроллер системы безопасности
     *
     * @details Controller координирует взаимодействие между всеми компонентами системы:
     * окружением, ИИ и пользовательским интерфейсом. Предоставляет API для управления
     * платформами, модулями, нарушителями и другими объектами системы.
     */
    class Controller
    {
    private:
        std::shared_ptr<Environment> env; ///< Умный указатель на окружение системы
        AI ai;                            ///< Искусственный интеллект системы

    public:
        /**
         * @brief Конструктор по умолчанию
         * @details Создает пустое окружение и инициализирует ИИ
         */
        Controller() : env(std::make_shared<Environment>()), ai(env) {}

        /**
         * @brief Конструктор с заданными размерами карты
         * @param x Ширина карты
         * @param y Высота карты
         */
        Controller(size_t x, size_t y) : env(std::make_shared<Environment>(x, y)), ai(env) {}

        /**
         * @brief Устанавливает размеры карты
         * @param x Ширина карты
         * @param y Высота карты
         */
        void set_size(size_t x, size_t y);

        /**
         * @brief Добавляет нарушителя на карту
         * @param p Позиция нарушителя
         */
        void add_intruder(std::pair<size_t, size_t> p);

        /**
         * @brief Добавляет статическую платформу на карту
         * @param desc Описание платформы
         * @param energy Уровень энергии
         * @param cap Вместимость
         * @param p Позиция платформы
         */
        void add_static(const std::string &desc, unsigned energy, unsigned cap, std::pair<size_t, size_t> p);

        /**
         * @brief Добавляет мобильную платформу на карту
         * @param desc Описание платформы
         * @param energy Уровень энергии
         * @param cap Вместимость
         * @param spd Скорость
         * @param p Позиция платформы
         */
        void add_mobile(const std::string &desc, unsigned energy, unsigned cap, unsigned spd, std::pair<size_t, size_t> p);

        /**
         * @brief Добавляет стену на карту
         * @param p Позиция стены
         */
        void add_wall(std::pair<size_t, size_t> p);

        /**
         * @brief Добавляет сетевой модуль на платформу
         * @param p Позиция платформы
         * @param power Потребляемая мощность
         * @param cnt Количество слотов
         * @param r Радиус действия
         */
        void add_network(std::pair<size_t, size_t> p, unsigned power, unsigned cnt, unsigned r);

        /**
         * @brief Добавляет рентгеновский сканер на платформу
         * @param p Позиция платформы
         * @param power Потребляемая мощность
         * @param cnt Количество слотов
         * @param r Радиус действия
         */
        void add_x_ray(std::pair<size_t, size_t> p, unsigned power, unsigned cnt, unsigned r);

        /**
         * @brief Добавляет оптический сканер на платформу
         * @param p Позиция платформы
         * @param power Потребляемая мощность
         * @param cnt Количество слотов
         * @param r Радиус действия
         */
        void add_optical(std::pair<size_t, size_t> p, unsigned power, unsigned cnt, unsigned r);

        /**
         * @brief Добавляет военный модуль на платформу
         * @param p Позиция платформы
         * @param power Потребляемая мощность
         * @param cnt Количество слотов
         * @param r Радиус действия
         * @param time Время заряда
         */
        void add_military(std::pair<size_t, size_t> p, unsigned power, unsigned cnt, unsigned r, unsigned time);

        /**
         * @brief Добавляет компонент по типу (без дополнительных параметров)
         * @param type Тип компонента ('i' - нарушитель, 'w' - стена)
         * @param p Позиция компонента
         * @throws std::runtime_error если тип невалидный
         */
        void add_component(char type, std::pair<size_t, size_t> p)
        {
            switch (type)
            {
            case 'i':
                add_intruder(p);
                break;
            case 'w':
                add_wall(p);
                break;
            default:
                throw std::runtime_error("Invalid component type");
            }
        }

        /**
         * @brief Добавляет компонент по типу (с параметрами)
         * @param type Тип компонента ('s' - статическая платформа)
         * @param desc Описание компонента
         * @param energy Уровень энергии
         * @param cap Вместимость
         * @param p Позиция компонента
         * @throws std::runtime_error если тип невалидный
         */
        void add_component(char type, const std::string &desc, unsigned energy, unsigned cap, std::pair<size_t, size_t> p)
        {
            switch (type)
            {
            case 's':
                add_static(desc, energy, cap, p);
                break;
            default:
                throw std::runtime_error("Invalid component type");
            }
        }

        /**
         * @brief Добавляет компонент по типу (с параметрами скорости)
         * @param type Тип компонента ('m' - мобильная платформа)
         * @param desc Описание компонента
         * @param energy Уровень энергии
         * @param cap Вместимость
         * @param spd Скорость
         * @param p Позиция компонента
         * @throws std::runtime_error если тип невалидный
         */
        void add_component(char type, const std::string &desc, unsigned energy, unsigned cap, unsigned spd, std::pair<size_t, size_t> p)
        {
            switch (type)
            {
            case 'm':
                add_mobile(desc, energy, cap, spd, p);
                break;
            default:
                throw std::runtime_error("Invalid component type");
            }
        }

        /**
         * @brief Добавляет модуль по типу (без времени заряда)
         * @param type Тип модуля ('n' - сетевой, 'x' - рентгеновский, 'o' - оптический)
         * @param p Позиция платформы
         * @param power Потребляемая мощность
         * @param cnt Количество слотов
         * @param r Радиус действия
         */
        void add_module(const char type, std::pair<size_t, size_t> p, unsigned power, unsigned cnt, unsigned r)
        {
            if (type == 'n')
                add_network(p, power, cnt, r);
            else if (type == 'x')
                add_x_ray(p, power, cnt, r);
            else if (type == 'o')
                add_optical(p, power, cnt, r);
        }

        /**
         * @brief Добавляет модуль по типу (с временем заряда)
         * @param type Тип модуля ('m' - военный)
         * @param p Позиция платформы
         * @param power Потребляемая мощность
         * @param cnt Количество слотов
         * @param r Радиус действия
         * @param time Время заряда
         */
        void add_module(const char type, std::pair<size_t, size_t> p, unsigned power, unsigned cnt, unsigned r, unsigned time)
        {
            if (type == 'm')
                add_military(p, power, cnt, r, time);
        }

        /**
         * @brief Получает список позиций компонентов определенного типа
         * @param type Тип компонента ('i' - нарушитель, 'p' - платформа, 's' - статическая,
         *             'm' - мобильная, 'w' - стена)
         * @return Вектор позиций компонентов
         */
        std::vector<std::pair<size_t, size_t>> get_component(const char type);

        /**
         * @brief Получает список модулей на платформе
         * @param p Позиция платформы
         * @return Вектор умных указателей на модули
         */
        std::vector<std::shared_ptr<Module>> get_modules(std::pair<size_t, size_t> p);

        /**
         * @brief Запускает нейтрализацию всех нарушителей через ИИ
         */
        void kill_intruders();

        /**
         * @brief Подключает сетевой модуль к другой платформе
         * @param pos Позиция платформы с сетевым модулем
         * @param ind Индекс сетевого модуля на платформе
         * @param ind2 Индекс платформы для подключения в таблице коммутации
         */
        void connect_network(std::pair<size_t, size_t> pos, size_t ind, size_t ind2);

        /**
         * @brief Получает список доступных для подключения платформ
         * @param pos Позиция платформы с сетевым модулем
         * @param ind Индекс сетевого модуля на платформе
         * @return Вектор умных указателей на доступные платформы
         */
        std::vector<std::shared_ptr<Platform>> get_active_session(std::pair<size_t, size_t> pos, size_t ind);

        /**
         * @brief Перемещает мобильную платформу
         * @param p Текущая позиция платформы
         * @param new_p Новая позиция платформы
         */
        void move_platform(std::pair<size_t, size_t> p, std::pair<size_t, size_t> new_p);

        /**
         * @brief Включает модуль на платформе
         * @param x Координата X платформы
         * @param y Координата Y платформы
         * @param ind Индекс модуля на платформе
         */
        void turn_on_module(size_t x, size_t y, size_t ind)
        {
            auto platform = std::dynamic_pointer_cast<Platform>(env->operator[](std::make_pair(x, y)));
            if (platform)
            {
                (*platform)[ind]->turn_on();
            }
        }

        /**
         * @brief Выключает модуль на платформе
         * @param x Координата X платформы
         * @param y Координата Y платформы
         * @param ind Индекс модуля на платформе
         */
        void turn_off_module(size_t x, size_t y, size_t ind)
        {
            auto platform = std::dynamic_pointer_cast<Platform>(env->operator[](std::make_pair(x, y)));
            if (platform)
            {
                (*platform)[ind]->turn_off();
            }
        }

        /**
         * @brief Получает копию карты окружения
         * @return Двумерный вектор умных указателей на компоненты
         */
        std::vector<std::vector<std::shared_ptr<Component>>> get_map() { return env->get_map(); }

        /**
         * @brief Сохраняет состояние системы в файл
         * @param filename Имя файла для сохранения
         */
        void save_file(const std::string &filename)
        {
            YAML::Node node;
            node = YAML::convert<Environment>::encode(*env);

            std::ofstream fout(filename);
            fout << node;
        }

        /**
         * @brief Загружает состояние системы из файла
         * @param filename Имя файла для загрузки
         */
        void load_file(const std::string &filename)
        {
            auto new_env = std::make_shared<Environment>();
            YAML::Node node = YAML::LoadFile(filename);
            YAML::convert<Environment>::decode(node, *new_env);

            env = new_env;
            ai.set_env(env);
            std::vector<std::pair<size_t, size_t>> statics = get_component('s');
            for (auto p : statics)
                ai.connect_platform(std::dynamic_pointer_cast<Platform>(env->operator[](p)));
        }

        /**
         * @brief Получает окружение системы
         * @return Умный указатель на окружение
         */
        std::shared_ptr<Environment> get_environment() const { return env; }
    };
}