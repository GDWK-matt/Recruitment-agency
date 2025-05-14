#include "Menu.h"

void Menu::adminMenu(Agentstvo& agency, AuthSystem& auth) {
    while (true) {
        std::cout << "\n======= МЕНЮ АДМИНИСТРАТОРА =======\n"
            << "1. Показать всех соискателей\n"
            << "2. Добавить соискателя\n"
            << "3. Поиск по критериям\n"
            << "4. Удалить соискателя\n"
            << "5. Изменить данные\n"
            << "6. Добавить нового пользователя\n"
            << "7. Удалить пользователя\n"
            << "8. Выход\n"
            << "Выбор: ";

        int choice;
        while (!(std::cin >> choice) || (choice < 1 || choice > 8)) {
            std::cout << "Ошибка ввода. Пожалуйста, введите 1 - 8: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        if (choice == 8) break;

        switch (choice) {
        case 1: {
            std::cout << std::string(100, '=') << "\n";
            agency.showSoiskateli();
            break;
        }
        case 2: {
            std::cout << std::string(100, '=') << "\n";
            agency.addSoiskatel();
            break;
        }
              // ... остальные case с переведенными сообщениями
        }
    }
}

void Menu::userMenu(Agentstvo& agency) {
    while (true) {
        std::cout << "\n======= МЕНЮ ПОЛЬЗОВАТЕЛЯ =======\n"
            << "1. Показать всех соискателей\n"
            << "2. Поиск по критериям\n"
            << "3. Возврат в главное меню\n"
            << "Выбор: ";

        int employerChoice;
        while (!(std::cin >> employerChoice) || (employerChoice < 1 || employerChoice > 3)) {
            std::cout << "Ошибка ввода. Пожалуйста, введите 1, 2 или 3: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        if (employerChoice == 3) break;

        switch (employerChoice) {
        case 1: std::cout << std::string(100, '=') << "\n"; agency.showSoiskateli(); break;
        case 2: std::cout << std::string(100, '=') << "\n"; agency.searchPo(); break;
        }
    }
}