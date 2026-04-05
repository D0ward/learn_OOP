#include <iostream>
#include <vector>
#include <iomanip>
#include <memory>

#include "../ai/ai.hpp"
#include "../component/platform/base/platform.hpp"
#include "../component/platform/static/static.hpp"
#include "../component/platform/mobile/mobile.hpp"
#include "../component/intruder/intruder.hpp"
#include "../module/base/module.hpp"
#include "../module/sensor/sensor.hpp"
#include "../module/military/military.hpp"
#include "../module/network/network.hpp"
#include "../environment/environment.hpp"
#include "controller.hpp"
#include "app.hpp"

namespace Security_system
{
    void App::print_map()
    {
        auto map = controller.get_map();
        size_t x = map.size();
        size_t y = map[0].size();

        std::cout << "     ";
        for (size_t j = 0; j < y; j++)
        {
            std::cout << std::setw(2) << j + 1 << "  ";
        }
        std::cout << "\n";

        std::cout << "    +";
        for (size_t j = 0; j < y; j++)
        {
            std::cout << "---+";
        }
        std::cout << "\n";

        for (size_t i = 0; i < x; i++)
        {
            std::cout << " " << std::setw(2) << i + 1 << " |";
            for (size_t j = 0; j < y; j++)
            {
                std::cout << " ";
                if (!map[i][j])
                    std::cout << ".";
                else
                    map[i][j]->print(std::cout);
                std::cout << " |";
            }
            std::cout << " " << i + 1 << "\n";

            if (i < x - 1)
            {
                std::cout << "    +";
                for (size_t j = 0; j < y; j++)
                {
                    std::cout << "---+";
                }
                std::cout << "\n";
            }
        }

        std::cout << "    +";
        for (size_t j = 0; j < y; j++)
        {
            std::cout << "---+";
        }
        std::cout << "\n";

        std::cout << "     ";
        for (size_t j = 0; j < y; j++)
        {
            std::cout << std::setw(2) << j + 1 << "  ";
        }
        std::cout << "\n";

        std::cout << "S - Статическая платформа." << std::endl 
                << "M - Мобильная платформа." << std::endl 
                << "W - Стена." << std::endl 
                << "I/X - Живой/Мертвый нарушитель." << std::endl;
    }

    void App::menu_add_comp()
    {
        std::cout << "Введите координаты нового компонента: ";
        std::pair<size_t, size_t> pos;
        std::cin >> pos.first >> pos.second;
        pos.first--;
        pos.second--;

        std::cout
            << "1. Статическая платформа" << std::endl
            << "2. Мобильная платформа" << std::endl
            << "3. Нарушитель" << std::endl
            << "4. Стена" << std::endl
            << "Выберите компонент: ";
        int choose_comp;
        std::cin >> choose_comp;

        std::string decs;
        unsigned level, capacity, speed;
        switch (choose_comp)
        {
        case 1:
            std::cout << "Введите свойства <Описание платформы, Уровень начальной энергии, Вместимость>:" << std::endl;
            std::cin >> decs >> level >> capacity;
            controller.add_component('s', decs, level, capacity, pos);
            break;
        case 2:
            std::cout << "Введите свойства <Описание платформы, Уровень начальной энергии, Вместимость, Скорость>:" << std::endl;
            std::cin >> decs >> level >> capacity >> speed;
            controller.add_component('m', decs, level, capacity, speed, pos);
            break;
        case 3:
            controller.add_component('i', pos);
            break;
        case 4:
            controller.add_component('w', pos);
            break;
        default:
            break;
        }
    }

    void App::menu_move()
    {
        std::vector<std::pair<size_t, size_t>> mobiles = controller.get_component('m');
        for (size_t i = 0; i < mobiles.size(); i++)
        {
            std::cout << i + 1 << ": " << mobiles[i].first << ' ' << mobiles[i].second << std::endl;
        }
        std::cout << "Выберите платформу: ";
        int choose;
        std::cin >> choose;

        std::cout << "Введите новые координаты: ";
        std::pair<size_t, size_t> new_pos;
        std::cin >> new_pos.first >> new_pos.second;

        try
        {
            controller.move_platform(mobiles[choose - 1], new_pos);
        }
        catch (...)
        {
            std::cout << "Платформа не передвинулась" << std::endl;
        }
    }

    void App::menu_add_module()
    {
        std::vector<std::pair<size_t, size_t>> platforms = controller.get_component('p');
        for (size_t i = 0; i < platforms.size(); i++)
        {
            std::cout << i + 1 << ": " << platforms[i].first << ' ' << platforms[i].second << std::endl;
        }
        std::cout << "Выберите платформу: ";
        int choose_platform;
        std::cin >> choose_platform;

        std::cout << "1. Сетевой" << std::endl
                  << "2. Вооруженный" << std::endl
                  << "3. Сканирующий оптический" << std::endl
                  << "4. Сканирующий рентгеновский" << std::endl
                  << "Выберите модуль: ";
        int choose;
        std::cin >> choose;

        std::cout << "Введите свойства: <Потребляемая мощность> <Количество слотов> <Радиус действия> ";
        unsigned power, slots, radius;
        std::cin >> power >> slots >> radius;

        unsigned time;

        switch (choose)
        {
        case 1:
            controller.add_module('n', platforms[choose_platform - 1], power, slots, radius);
            break;
        case 2:
            std::cout << "Введите время заряда: ";
            std::cin >> time;
            controller.add_module('m', platforms[choose_platform - 1], power, slots, radius, time);
            break;
        case 3:
            controller.add_module('o', platforms[choose_platform - 1], power, slots, radius);
            break;
        case 4:
            controller.add_module('x', platforms[choose_platform - 1], power, slots, radius);
            break;
        default:
            break;
        }
    }

    void App::menu_connect_network()
    {
        std::vector<std::pair<size_t, size_t>> platforms = controller.get_component('p');
        for (size_t i = 0; i < platforms.size(); i++)
        {
            std::cout << i + 1 << ": " << platforms[i].first << ' ' << platforms[i].second << std::endl;

            std::vector<std::shared_ptr<Module>> modules = controller.get_modules(platforms[i]);
            std::cout << "Модули:" << std::endl;
            for (size_t j = 0; j < modules.size(); j++)
            {
                if (std::dynamic_pointer_cast<Network>(modules[j]))
                {
                    std::cout << j + 1 << " Сетевой модуль" << std::endl;
                }
                else if (std::dynamic_pointer_cast<X_ray>(modules[j]))
                {
                    std::cout << j + 1 << " Рентгеновский сканер" << std::endl;
                }
                else if (std::dynamic_pointer_cast<Optical>(modules[j]))
                {
                    std::cout << j + 1 << " Оптический сканер" << std::endl;
                }
                else if (std::dynamic_pointer_cast<Military>(modules[j]))
                {
                    std::cout << j + 1 << " Вооруженный модуль" << std::endl;
                }
            }
        }
        std::cout << "Выберите платформу и модуль: ";
        unsigned choose_plat, choose_module;
        std::cin >> choose_plat >> choose_module;

        std::vector<std::shared_ptr<Platform>> active_session = 
            controller.get_active_session(platforms[choose_plat - 1], choose_module - 1);

        std::cout << "Возможные платформы для подключения:" << std::endl;
        for (size_t i = 0; i < active_session.size(); i++)
        {
            auto pos = active_session[i]->get_pos();
            std::cout << i + 1 << ' ' << pos.first << ' ' << pos.second << std::endl;
        }
        std::cout << "Выберите платформу: ";
        unsigned choose_plat_2;
        std::cin >> choose_plat_2;

        controller.connect_network(platforms[choose_plat - 1], choose_module - 1, choose_plat_2 - 1);
    }

    int App::menu_main()
    {
        std::cout << "1. Добавить компонент" << std::endl
                  << "2. Переместить мобильную платформу" << std::endl
                  << "3. Добавить модуль" << std::endl
                  << "4. Соединить платформы" << std::endl
                  << "5. Неитрализовать нарушителей" << std::endl
                  << "6. Сохранить в файл" << std::endl
                  << "7. Загрузить сохранение" << std::endl
                  << "0. Выйти" << std::endl
                  << "Выберите действие: ";

        int choose;

        std::cin >> choose;
        if (!std::cin.good())
            return 1;

        switch (choose)
        {
        case 0:
            return 1;
        case 1:
            menu_add_comp();
            break;
        case 2:
            menu_move();
            break;
        case 3:
            menu_add_module();
            break;
        case 4:
            menu_connect_network();
            break;
        case 5:
            controller.kill_intruders();
            break;
        case 6:
            controller.save_file(config_file_name);
            break;
        default:
            break;
        }
        return 0;
    }

    void App::run()
    {
        while (true)
        {
            print_map();
            if (menu_main())
                break;
        }
    }
}