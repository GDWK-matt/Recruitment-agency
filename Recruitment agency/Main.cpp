#include <iostream>
#include "agentstvo.h"

int main() {
    Agentstvo agency;
    agency.loadFromFile();

    int choice;

    std::cout << "Vybiraite rol:\n1. Polzovatel\n2. Admin\n";

    while (!(std::cin >> choice) || (choice < 1 || choice > 2)) {
        std::cout << "Oshibka vvida. Pozhaluysta, vvedite 1 ili 2: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    switch (choice) {
    case 1: { // Polzovatel
        int userType;
        std::cout << "\nVybiraite tip polzovatelya:\n1. Soiskatel\n2. Rabotodatel\n";

        while (!(std::cin >> userType) || (userType < 1 || userType > 2)) {
            std::cout << "Oshibka vvida. Pozhaluysta, vvedite 1 ili 2: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        switch (userType) {
        case 1: // Soiskatel
            agency.addSoiskatel();
            break;

        case 2: { // Rabotodatel
            int employerChoice;
            do {
                std::cout << "\nVybiraite deystviye:\n1. Pokazat' vsekh soiskateley\n2. Poisk po parametram\n3. Vykhod\n";
                while (!(std::cin >> employerChoice) || (employerChoice < 1 || employerChoice > 3)) {
                    std::cout << "Oshibka vvida. Pozhaluysta, vvedite 1, 2 ili 3: ";
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }

                switch (employerChoice) {
                case 1:
                    agency.showSoiskateli();
                    break;

                case 2: { // Poisk po parametram
                    int searchType;
                    std::cout << "Poisk po:\n1. Vozrastu\n2. Stazhu\n3. Sektoru\n";
                    while (!(std::cin >> searchType) || (searchType < 1 || searchType > 3)) {
                        std::cout << "Oshibka vvida. Pozhaluysta, vvedite 1, 2 ili 3: ";
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    }

                    switch (searchType) {
                    case 1: { // Poisk po vozrastu
                        int age;
                        std::cout << "Vvedite vozrast: ";
                        while (!(std::cin >> age)) {
                            std::cout << "Oshibka vvida. Pozhaluysta, vvedite tseloe chislo dlya vozrasta: ";
                            std::cin.clear();
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        }
                        agency.searchByAge(age);
                        break;
                    }
                    case 2: { // Poisk po stazhu
                        int exp;
                        std::cout << "Vvedite stazh raboty: ";
                        while (!(std::cin >> exp)) {
                            std::cout << "Oshibka vvoda. Pozhaluysta, vvedite tseloe chislo dlya stazha: ";
                            std::cin.clear();
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        }
                        agency.searchByExperience(exp);
                        break;
                    }

                    case 3: { // Poisk po sektoru
                        std::string sector;
                        std::cout << "Vvedite dolzhnost: ";
                        std::cin >> sector;
                        agency.searchBySector(sector);
                        break;
                    }
                    }
                    break;
                }

                case 3:
                    break; // Vykhod iz menyu rabotodatela
                }
            } while (employerChoice != 3);
            break;
        }
        }
        break; // Konets bloka polzovatelya
    }

    case 2: { // Admin
        const std::string adminPassword = "123"; 
        std::string inputPassword;
        bool correct = true;
        while (correct == true) {
            std::cout << "Vvedite parol: ";
            std::cin >> inputPassword;

            if (inputPassword == adminPassword) {
                correct = false;
                while (true) {
                    int adminChoice;
                    std::cout << "1. Pokazat' vsekh soiskateley\n2. Dobavit' soiskatelya\n3. Udalit' soiskatelya\n4. Vykhod\n";
                    while (!(std::cin >> adminChoice) || (adminChoice < 1 || adminChoice > 4)) {
                        std::cout << "Oshibka vvida. Pozhaluysta, vvedite chislo ot 1 do 4: ";
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    }

                    switch (adminChoice) {
                    case 1:
                        agency.showSoiskateli();
                        break;

                    case 2:
                        agency.addSoiskatel();
                        break;

                    case 3: { // Udaleniye soiskatelya
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

                        agency.deleteSoiskatel(index - 1); // umenshayem na 1 dlya korrektnogo indeksa
                        break;
                    }

                    case 4:
                        return false; // vykhod iz programmy
                    }
                }
            }
            else {
                std::cout << "Nevernyy parol!\n";
            }
        }
        break; // Konets bloka admina
    }
    }

    return 0;
}
