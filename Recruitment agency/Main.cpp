#include "Menu.h"
#include <windows.h>

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    AuthSystem auth;
    Agentstvo agency;
    Menu menu;
    agency.loadFromFile();
    auth.loadUsers();

    std::cout << "============================\n";
    std::cout << "       ДОБРО ПОЖАЛОВАТЬ!\n";
    std::cout << "============================\n";

    while (true) {
        std::cout << "1. Войти в систему\n";
        std::cout << "2. Выход\n";
        std::cout << "Выберите: ";

        int choice;
        while (!(std::cin >> choice) || (choice < 1 || choice > 2)) {
            std::cout << "Ошибка ввода. Пожалуйста, введите 1 или 2: ";
            std::cin.clear();
            while (std::cin.get() != '\n') continue;
        }
        if (choice == 2) break;

        switch (choice) {
        case 1: {
            while (true) {
                std::string login, password;
                std::cout << "\n======= ВХОД В СИСТЕМУ =======\n"
                    << "Логин: ";
                std::cin >> login;
                std::cout << "Пароль: ";
                std::cin >> password;

                bool isAdmin;
                if (auth.checkAuth(login, password, isAdmin)) {
                    if (isAdmin) {
                        menu.adminMenu(agency, auth);
                    }
                    else {
                        menu.userMenu(agency);
                    }
                }
                else {
                    std::cout << "Неверный логин или пароль!\n";
                }
            }
        }
        }
    }
    return 0;
}