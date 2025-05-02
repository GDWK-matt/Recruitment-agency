#include <iostream>
#include "agentstvo.h"

int main() {
    Agentstvo agency;
    agency.loadFromFile();

    while (true) { // Цикл главного меню
        int choice;
        std::cout << "Vybiraite rol:\n1. Polzovatel\n2. Admin\n3. Vykhod iz programmy\n";

        while (!(std::cin >> choice) || (choice < 1 || choice > 3)) {
            std::cout << "Oshibka vvida. Pozhaluysta, vvedite 1, 2 ili 3: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        if (choice == 3) { // Полный выход из программы
            std::cout << "Zavershenie raboty...\n";
            break;
        }

        switch (choice) {
        case 1: { // Пользователь
            while (true) {
                int employerChoice;
                std::cout << "\nVybiraite deystviye:\n1. Pokazat' vsekh soiskateley\n2. Poisk po Dolzhnosti\n3. Vozvrat v glavnoe menyu\n";
                while (!(std::cin >> employerChoice) || (employerChoice < 1 || employerChoice > 3)) {
                    std::cout << "Oshibka vvida. Pozhaluysta, vvedite 1, 2 ili 3: ";
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }

                if (employerChoice == 3) break; // Возвращаемся в главное меню

                switch (employerChoice) {
                case 1: agency.showSoiskateli(); break;
                case 2: {
                    std::string sector;
                    std::cout << "Vvedite dolzhnost (Nazvanie dolzhnosti vvodite s ZAGLAVNOI bykvi!): ";
                    std::cin >> sector;
                    agency.searchBySector(sector);
                    break;
                }
                }
            }
            break;
        }

        case 2: { // Администратор
            const std::string adminPassword = "123";
            std::string inputPassword;
            std::cout << "Vvedite parol: ";
            std::cin >> inputPassword;

            if (inputPassword == adminPassword) {
                while (true) {
                    int adminChoice;
                    std::cout << "\n1. Pokazat' vsekh soiskateley\n2. Dobavit' soiskatelya\n3. Udalit' soiskatelya\n4. Izmenit dannye\n5. Vozvrat v glavnoe menyu\n";
                    while (!(std::cin >> adminChoice) || (adminChoice < 1 || adminChoice > 5)) {
                        std::cout << "Oshibka vvida. Pozhaluysta, vvedite chislo ot 1 do 5: ";
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    }

                    if (adminChoice == 5) break; // Возвращаемся в главное меню

                    switch (adminChoice) {
                    case 1: agency.showSoiskateli(); break;
                    case 2: agency.addSoiskatel(); break;
                    case 3: {
                        if (agency.soiskateli.empty()) {
                            std::cout << "Net soiskateley dlya udaleniyu.\n";
                            break;
                        }
                        int index;
                        agency.showSoiskateli();
                        std::cout << "Vvedite nomer soiskatelya dlya udaleniyu: ";
                        while (!(std::cin >> index) || index < 1 || index > static_cast<int>(agency.soiskateli.size())) {
                            std::cout << "Oshibka vvida. Pozhaluysta, vvedite korrektnyy nomer soiskatelya: ";
                            std::cin.clear();
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        }
                        agency.deleteSoiskatel(index - 1);
                        break;
                    }
                    case 4: {
                        int ind;
                        std::cout << "Vvedite index soiskatelya, dannie kotorogo hotite izmenit: ";
                        std::cin >> ind;
                        agency.updateSoiskatel(ind - 1);
                        break;
                    }
                    }
                }
            }
            else {
                std::cout << "Nevernyy parol!\n";
            }
            break;
        }
        }
    }

    return 0;
}