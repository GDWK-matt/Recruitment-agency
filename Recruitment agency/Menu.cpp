#include "Menu.h"

void Menu::adminMenu(Agentstvo& agency, AuthSystem& auth) {
    while (true) {
        std::cout << "\n======= ���� �������������� =======\n"
            << "1. �������� ���� �����������\n"
            << "2. �������� ����������\n"
            << "3. ����� �� ���������\n"
            << "4. ������� ����������\n"
            << "5. �������� ������\n"
            << "6. �������� ������ ������������\n"
            << "7. ������� ������������\n"
            << "8. �����\n"
            << "�����: ";

        int choice;
        while (!(std::cin >> choice) || (choice < 1 || choice > 8)) {
            std::cout << "������ �����. ����������, ������� 1 - 8: ";
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
              // ... ��������� case � ������������� �����������
        }
    }
}

void Menu::userMenu(Agentstvo& agency) {
    while (true) {
        std::cout << "\n======= ���� ������������ =======\n"
            << "1. �������� ���� �����������\n"
            << "2. ����� �� ���������\n"
            << "3. ������� � ������� ����\n"
            << "�����: ";

        int employerChoice;
        while (!(std::cin >> employerChoice) || (employerChoice < 1 || employerChoice > 3)) {
            std::cout << "������ �����. ����������, ������� 1, 2 ��� 3: ";
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