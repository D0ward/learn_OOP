#include <iostream>
#include <string>

#include "security_system/ui/app.hpp"

int main()
{

    std::cout << "1. Новая игра" << std::endl
              << "2. Загрузить сохранение" << std::endl
              << ">> ";
    int choose;
    std::cin >> choose;
    if (choose == 1)
    {
        Security_system::App app;
        app.run();
    }
    else
    {
        std::cout << "Введите название файла: ";

        std::string file_name;
        std::cin >> file_name;
        Security_system::App app(file_name);
        app.run();
    }
    return 0;
}
