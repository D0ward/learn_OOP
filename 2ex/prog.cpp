#include <iostream>
#include <limits>

#include "input/input.hpp"
#include "lib/complex_class.hpp"

void foo(train train)
{
    wagon wagon(10, 10, "люкс");
    train += wagon;
    std::cout << "Поезд в функции" << std::endl;
    std::cout << train << std::endl;
}

train boo(train &&train_pupupu)
{
    std::cout << "Перемещающий конструктор" << std::endl;
    wagon wagon(10, 10, "люкс");
    train_pupupu += wagon;
    return train_pupupu;
}

void menu()
{
    std::cout << "Выберите действие:" << std::endl
              << "0. Выход" << std::endl
              << "1. Создать поезд" << std::endl
              << "2. Добавить вагон" << std::endl
              << "3. Изменить вагон" << std::endl
              << "4. Удалить вагон" << std::endl
              << "5. Убрать пустые вагоны" << std::endl
              << "6. Усадить пассажиров в вагон" << std::endl
              << "7. Усадить пассажиров в вагон указанного типа" << std::endl
              << "8. Высадить пассажиров" << std::endl
              << "9. Переместить пассажиров" << std::endl
              << "10. Вставить вагон-ресторан в «оптимальное место" << std::endl
              << "11. Перераспределить пассажиров по вагонам для выравнивания занятости" << std::endl
              << "12. Проверить копирующий конструктор" << std::endl
              << "13. Проверить перемещающий конструктор" << std::endl
              << ">> ";
}

short choose_change_wagon()
{
    std::cout << "Выберите действие:" << std::endl
              << "1. Изменить тип вагона" << std::endl
              << "2. Установить вместимость вагона" << std::endl
              << "3. Установить количество занятых мест" << std::endl
              << ">> ";

    return readint(std::cin, 0, 3);
}

void solve()
{
    train train;
    while (true)
    {
        try
        {
            std::cout << train << std::endl;

            menu();
            short operation = readint(std::cin, 0, 13);
            std::cin.clear();
            // std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            wagon wagon;
            int index = 0;
            int index_2 = 0;
            int new_value = 0;
            std::string new_value_str;

            switch (operation)
            {
            case 0:
                return;

            case 1:
                std::cin >> train;
                break;

            case 2:
                std::cout << "Тип(люкс, ресторан, сидячий, эконом)/Вместимость/Кол-во пассажиров: " << std::endl;
                std::cin >> wagon;
                train += wagon;
                break;

            case 3:
                std::cout << "Введите индекс вагона: ";
                index = readint(std::cin, 0);
                switch (choose_change_wagon())
                {
                case 1:
                    std::cout << "Введите тип: ";
                    new_value_str = readline(std::cin);
                    train[index].set_wagon_type(new_value_str);
                    break;
                case 2:
                    std::cout << "Введите вместимость вагона: ";
                    new_value = readint(std::cin, 0);
                    train[index].set_wagon_capacity(new_value);
                    break;
                case 3:
                    std::cout << "Введите количество занятых мест: ";
                    new_value = readint(std::cin, 0);
                    train[index].set_wagon_occupied(new_value);
                    break;
                }
                break;

            case 4:
                std::cout << "Введите индекс вагона: ";
                index = readint(std::cin, 0);
                train - index;
                break;

            case 5:
                --train;
                break;

            case 6:
                std::cout << "Введите количество пассажиров: ";
                new_value = readint(std::cin, 0);
                std::cout << "Введите индекс вагона: ";
                index = readint(std::cin, 0);
                train[index] + new_value;
                break;

            case 7:
                std::cout << "Введите количество пассажиров: ";
                new_value = readint(std::cin, 0);
                std::cout << "Введите тип вагона: ";
                new_value_str = readline(std::cin);
                train(new_value, new_value_str);
                break;

            case 8:
                std::cout << "Введите количество пассажиров: ";
                new_value = readint(std::cin, 0);
                std::cout << "Введите индекс вагона: ";
                index = readint(std::cin, 0);
                train[index] - new_value;
                break;

            case 9:
                std::cout << "Введите индекс первого вагона: ";
                index = readint(std::cin, 0);
                std::cout << "Введите индекс второго вагона: ";
                index_2 = readint(std::cin, 0);
                train[index_2] >> train[index];
                break;

            case 10:
                train++;
                break;

            case 11:
                !train;
                break;

            case 12:
                foo(train);
                break;
            case 13:
                auto temp = boo(std::move(train));
                std::cout << "temp: " << std::endl;
                std::cout << temp << std::endl;
                break;
            }
        }
        catch (const std::invalid_argument &e)
        {
            std::cout << e.what() << std::endl;
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << std::endl;
            return;
        }
    }
}

int main()
{
    solve();

    std::cout << "Программа завершилась" << std::endl;

    return 0;
}
