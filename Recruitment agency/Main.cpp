#include "agentstvo.h"
#include "auth.h"

void adminMenu(Agentstvo& agency, AuthSystem& auth) {
    while (true) {
        std::cout << "\n=== ADMIN MENU ===\n"
            << "1. Pokazat vsekh soiskateley\n"
            << "2. Dobavit soiskatelya\n"
            << "3. Udalit soiskatelya\n"
            << "4. Izmenit dannye\n"
            << "5. Dobavit novogo polzovatelya\n"
            << "6. Udalit polzovatelya\n"
            << "7. Vykhod\n"
            << "Vybor: ";

        int choice;
        while (!(std::cin >> choice) || (choice < 1 || choice > 7)) {
            std::cout << "Oshibka vvoda. Pozhaluysta, vvedite 1 - 7: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        if (choice == 7) break;
        
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
            case 3: {
                std::cout << std::string(100, '=') << "\n";
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
                std::cout << std::string(100, '=') << "\n";
                break;
            }
            case 4: {
                std::cout << std::string(100, '=') << "\n";
                int ind;
                std::cout << "Vvedite index soiskatelya, dannie kotorogo hotite izmenit: ";
                std::cin >> ind;
                agency.updateSoiskatel(ind - 1);
                break;
            }
            case 5: {
                std::cout << std::string(100, '=') << "\n";
                std::string login, password;
                std::cout << "Vvedite login: ";
                std::cin >> login;
                std::cout << "Vvedite password: ";
                std::cin >> password;
                std::cout << "Dostup (1 - admin, 0 - user): ";
                int access;
                std::cin >> access;
                if (auth.addUser(login, password, access == 1)) {
                    std::cout << "Polzovatel uspeshno dobavlen!\n";
                }
                else {
                    std::cout << "Oshibka: login uzhe sushchestvuet!\n";
                }
                break;
            }
            case 6: {
                std::cout << std::string(100, '=') << "\n";
                std::cout << "Vvedite login dlya udaleniya: ";
                std::string login;
                std::cin >> login;
                if (auth.removeUser(login)) {
                    std::cout << std::string(100, '=') << "\n";
                    std::cout << "Polzovatel uspeshno udalen!\n";
                    std::cout << std::string(100, '=') << "\n";
                }
                else {
                    std::cout << std::string(100, '=') << "\n";
                    std::cout << "Oshibka: polzovatel ne nayden!\n";
                    std::cout << std::string(100, '=') << "\n";
                }
                break;
            }
            default:
                std::cout << "Nekorrektny vybor!\n";
                std::cout << std::string(100, '=') << "\n";
            }
        
    }
}

void userMenu(Agentstvo& agency){ 
    while (true) {
        int employerChoice;
        std::cout << "\n=== USER MENU ===\n"
            <<"1. Pokazat' vsekh soiskateley \n"
            <<"2. Poisk po ...\n"
            <<"3. Vozvrat v glavnoe menyu\n"
            << "Vybor: ";

        while (!(std::cin >> employerChoice) || (employerChoice < 1 || employerChoice > 3)) {
            std::cout << "Oshibka vvoda. Pozhaluysta, vvedite 1, 2 ili 3: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        if (employerChoice == 3) break; // Возвращаемся в главное меню

        switch (employerChoice) {
        case 1: std::cout << std::string(100, '=') << "\n"; agency.showSoiskateli(); break;
        case 2: std::cout << std::string(100, '=') << "\n"; agency.searchPo(); break;
      
        }
    }
}


    int main() {
        AuthSystem auth;
        Agentstvo agency;
        agency.loadFromFile();

        while (true) {
            std::string login, password;
            std::cout << "\n=== VHOD V SYSTEMU ===\n"
                << "Login: ";
            std::cin >> login;
            std::cout << "Password: ";
            std::cin >> password;

            bool isAdmin;
            if (auth.checkAuth(login, password, isAdmin)) {
                if (isAdmin) {
                    adminMenu(agency, auth);
                }
                else {
                    userMenu(agency);
                }
            }
            else {
                std::cout << "Nepravilny login ili parol!\n";
            }
        }

        return 0;
    }