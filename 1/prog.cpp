#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <algorithm>

#include "lib.hpp"
#include "input_lib/input.hpp"

void menu()
{
    std::cout << "0: Выйти" << std::endl
              << "1: Перевести массив в строку формата application/x-www-form-urlencoded в формате const char*" << std::endl
              << "2: Перевести массив в строку формата application/x-www-form-urlencoded в формате const char* + size_t" << std::endl
              << "3: Перевести массив в строку формата application/x-www-form-urlencoded в формате std::string" << std::endl
              << "4: Перевести строку формата application/x-www-form-urlencoded в массив в формате const char*" << std::endl
              << "5: Перевести строку формата application/x-www-form-urlencoded в массив в формате const char* + size_t" << std::endl
              << "6: Перевести строку формата application/x-www-form-urlencoded в массив в формате std::string" << std::endl
              << "Выберите действие: ";
}

void solve()
{
    int index = 1;
    auto input_array = [index](int &value) mutable
    {
            std::cout << "Введите " << index++ << " элемент массива: ";
            value = readint(std::cin); };
    auto output_array = [](int value)
    { std::cout << value << ' '; };

    while (1)
    {
        menu();

        int operation;
        try
        {
            operation = readint(std::cin);
        }
        catch (std::exception &e)
        {
            return;
        }

        size_t size_array = 0;
        int *array = nullptr;
        std::vector<int> array_vec;
        std::string name_array_str;
        std::string result;
        char *result_c = nullptr;
        const char *name_array_c = nullptr;
        char *name_array = nullptr;
        std::string urlencoded_str;
        const char *urlencoded_c;

        try
        {
            switch (operation)
            {
            case 0:
                return;
            case 1:
                std::cout << "Введите размер массива: ";
                size_array = readint(std::cin, 0);
                array = new int[size_array];
                std::for_each_n(array, size_array, input_array);

                std::cout << "Введите название массива: ";
                name_array_str = readline(std::cin);
                name_array_c = name_array_str.c_str();

                result_c = encode(array, size_array, name_array_c);
                std::cout << "Получившееся строка: " << result_c << std::endl;
                break;
            case 2:
                std::cout << "Введите размер массива: ";
                size_array = readint(std::cin, 0);
                array = new int[size_array];
                std::for_each_n(array, size_array, input_array);

                std::cout << "Введите название массива: ";
                name_array_str = readline(std::cin);
                name_array_c = name_array_str.c_str();

                result_c = encode(array, size_array, name_array_c, strlen(name_array_c));
                std::cout << "Получившееся строка: " << result_c << std::endl;
                break;
            case 3:
                std::cout << "Введите размер массива: ";
                size_array = readint(std::cin, 0);
                array_vec.resize(size_array);

                std::for_each(array_vec.begin(), array_vec.end(), input_array);

                std::cout << "Введите название массива: ";
                name_array_str = readline(std::cin);

                result = encode(array_vec, name_array_str);
                std::cout << "Получившееся строка: " << result << std::endl;
                break;
            case 4:
                std::cout << "Введите строку: ";
                urlencoded_str = readline(std::cin);
                urlencoded_c = urlencoded_str.c_str();
                try
                {
                    array = decode(urlencoded_c, size_array, name_array);
                    std::cout << "Полученный массив: " << name_array << " = ";
                    std::for_each_n(array, size_array, output_array);

                    std::cout << std::endl;
                }
                catch (std::invalid_argument &e)
                {
                    std::cout << "Неправильный формат строки." << std::endl;
                }
                break;
            case 5:
                std::cout << "Введите строку: ";
                urlencoded_str = readline(std::cin);
                urlencoded_c = urlencoded_str.c_str();
                try
                {
                    array = decode(urlencoded_c, urlencoded_str.size(), size_array, name_array);
                    std::cout << "Полученный массив: " << name_array << " = ";
                    std::for_each_n(array, size_array, output_array);

                    std::cout << std::endl;
                }
                catch (std::invalid_argument &e)
                {
                    std::cout << "Неправильный формат строки." << std::endl;
                }
                break;
            case 6:
                std::cout << "Введите строку: ";
                urlencoded_str = readline(std::cin);
                try
                {
                    array_vec = decode(urlencoded_str, name_array_str);

                    std::cout << "Полученный массив: " << name_array_str << " = ";
                    std::for_each(array_vec.begin(), array_vec.end(), output_array);

                    std::cout << std::endl;
                }
                catch (std::invalid_argument &e)
                {
                    std::cout << "Неправильный формат строки." << std::endl;
                }
                break;
            default:
                std::cout << "Такого действия нет" << std::endl;
                break;
            }

            if (array)
            {
                delete[] array;
            }
            if (result_c)
            {
                delete[] result_c;
            }
            if (name_array)
            {
                delete[] name_array;
            }
        }
        catch (std::exception &e)
        {
            if (array)
            {
                delete[] array;
            }
            if (result_c)
            {
                delete[] result_c;
            }
            if (name_array)
            {
                delete[] name_array;
            }
        }
    }
}

int main()
{

    solve();

    std::cout << "Конец программы" << std::endl;

    return 0;
}
