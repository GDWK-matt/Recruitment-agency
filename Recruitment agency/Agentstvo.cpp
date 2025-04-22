#include "agentstvo.h"

void Agentstvo::addSoiskatel() {
    std::string name, sector, email;
    int age, experience;

    std::cout << "Vvedite imya: ";
    std::cin >> name;
    std::cout << "Vvedite vozrast: ";
    while (!(std::cin >> age) || age >= 70 || age <= 18 ) {
        std::cout << "Oshibka vvoda. Pozhaluysta, vvedite tseloe chislo dlya vozrasta ili menshe 70: \n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    std::cout << "Vvedite opyt raboty v godakh: ";
    while (!(std::cin >> experience ) || experience > age - 16 ) {
        std::cout << "Oshibka vvoda(opit ne mozet privishat vremya ot vozmozhnoi raboti (ot 16 let)): ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    std::cout << "Vvedite dolzhnost: ";
    std::cin >> sector;
    std::cout << "Vvedite email: ";
    std::cin >> email;

    Soiskatel newSoiskatel(name, age, experience, sector, email);
    soiskateli.push_back(newSoiskatel);
    saveToFile();
}

void Agentstvo::showSoiskateli() {
    if (soiskateli.empty()) {
        std::cout << "Net soiskateley dlya otobrazheniya.\n";
        return;
    }
    std::cout << "\n#\tImya\tVozrast\t Opit\tDolzhnost\tEmail\n";
    std::cout << "********************************************************\n";

    for (size_t i = 0; i < soiskateli.size(); ++i) {
        const Soiskatel& s = soiskateli[i];
        std::cout << i + 1 << "\t"
            << s.name << "\t" 
            << s.age << "\t "
            << s.experience << "\t" 
            << s.sector << "\t\t" 
            << s.email<< "\n";
    }
}

void Agentstvo::deleteSoiskatel(int index) {
    if (index >= 0 && index < soiskateli.size()) {
        soiskateli.erase(soiskateli.begin() + index);
        saveToFile();
    }
    else {
        std::cout << "Nevernyy indeks\n";
    }
}

void Agentstvo::searchByAge(int age) {
    bool found = false;
    std::cout << "\n#\tImya\tVozrast\t Opit\tDolzhnost\tEmail\n";
    std::cout << "********************************************************\n";
    for (const auto& s : soiskateli) {
       
        if (s.age == age) {
            std::cout << s.name << "\t" 
                << s.age << "\t "
                << s.experience << "\t" 
                << s.sector << "\t" 
                << s.email << "\n";
            found = true;
        }
    }
    if (!found) {
        std::cout << "\nSoiskateli vozrastom " << age << " ne naydeny.\n";
    }
}

void Agentstvo::searchByExperience(int experience) {
    bool found = false;
    std::cout << "\n#\tImya\tVozrast\t Opit\tDolzhnost\tEmail\n";
    std::cout << "********************************************************\n";
    for (const auto& s : soiskateli) {
        if (s.experience == experience) {
            std::cout
                << s.name << "\t"
                << s.age << "\t "
                << s.experience << "\t"
                << s.sector << "\t"
                << s.email << "\n";
            found = true;
        }
    }
    if (!found) {
        std::cout << "\nSoiskateli so stazhem " << experience << " ne naydeny.\n";
    }
}

void Agentstvo::searchBySector(const std::string& sector) {
    bool found = false;
    std::cout << "\n#\tImya\tVozrast\t Opit\tDolzhnost\tEmail\n";
    std::cout << "********************************************************\n";
    for (const auto& s : soiskateli) {
        if (s.sector.find(sector) != std::string::npos) {
            std::cout 
                << s.name << "\t" 
                << s.age << "\t "
                << s.experience << "\t" 
                << s.sector << "\t" 
                << s.email << "\n";
            found = true;
        }
    }
    if (!found) {
        std::cout << "\nSoiskateli s dolzhnost'u " << sector << " ne naydeny.\n";
    }
}

void Agentstvo::saveToFile() {
    std::ofstream file("soiskateli.txt");
    for (const auto& s : soiskateli) {
        file << s.name << "\t"  << s.age << "\t "  << s.experience << "\t" << s.sector << "\t" << s.email << "\n";
    }
}

void Agentstvo::loadFromFile() {
    std::ifstream file("soiskateli.txt");
    std::string line;

    while (std::getline(file, line)) {
        size_t pos = 0;
        std::vector<std::string> data;

        while ((pos = line.find('\t')) != std::string::npos) {
            data.push_back(line.substr(0, pos));
            line.erase(0, pos + 1);
        }
        data.push_back(line); // last element

        if (data.size() == 5) {
            Soiskatel newSoiskatel(data[0], std::stoi(data[1]),
                std::stoi(data[2]), data[3], data[4]);
            soiskateli.push_back(newSoiskatel);
        }
    }
}
