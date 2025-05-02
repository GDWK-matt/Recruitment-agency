#include "agentstvo.h"

void Agentstvo::addSoiskatel() {
    std::string name, sector, email;
    int age, experience;

    std::cout << "Vvedite imya: ";
    std::cin >> name;
    std::cout << "Vvedite vozrast: ";
    while (!(std::cin >> age) || age >= 70 || age < 18 ) {
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

    std::sort(soiskateli.begin(), soiskateli.end(), [](const Soiskatel& a, const Soiskatel& b) {
        if (a.sector == b.sector) {
            return a.experience > b.experience; // Стаж в порядке убывания
        }
        return a.sector < b.sector; // Профессия в алфавитном порядке
        });

    std::cout << std::left << std::setw(6) << "#"
        << std::setw(15) << "Imya"
        << std::setw(8) << "Vozrast"
        << std::setw(10) << "Opyt"
        << std::setw(20) << "Dolzhnost"
        << std::setw(30) << "Email" << "\n";
        
    std::cout << std::string(83, '*') << "\n"; // Линия-разделитель

    for (size_t i = 0; i < soiskateli.size(); ++i) {
        const Soiskatel& s = soiskateli[i];
        std::cout << std::left << std::setw(6) << i+1
            << std::setw(15) << s.name
            << std::setw(8) << s.age
            << std::setw(10) << s.experience
            << std::setw(20) << s.sector
            << std::setw(30) << s.email << "\n";
    }
    std::cout << std::string(83, '*') << "\n";
}

void Agentstvo::updateSoiskatel(int index) {
    if (index < 0 || index >= soiskateli.size()) {
        std::cout << "Nevernyy indeks soiskatelya!\n";
        return;
    }

    Soiskatel& s = soiskateli[index];

    int ch;
    std::cout << "\nVyberite, chto izmenit:\n";
    std::cout << "1. Imya\n";
    std::cout << "2. Vozrast\n";
    std::cout << "3. Opyt raboty\n";
    std::cout << "4. Dolzhnost\n";
    std::cout << "5. Email\n";
    std::cout << "Vybor: ";
    std::cin >> ch;

    switch (ch) {
    case 1: {
        std::cout << "Vvedite novoe imya: ";
        std::cin >> s.name;
        break;
    }
    case 2: {
        int newAge;
        std::cout << "Vvedite novyy vozrast: ";
        while (!(std::cin >> newAge) || newAge >= 70 || newAge <= 18) {
            std::cout << "Oshibka vvoda. Vvedite korrektnyy vozrast (18-70 let): ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        s.age = newAge;
        break;
    }
    case 3: {
        int newExperience;
        std::cout << "Vvedite novyy opyt raboty: ";
        while (!(std::cin >> newExperience) || newExperience > s.age - 16) {
            std::cout << "Oshibka vvoda. Opyt ne mozhet prevyshat vremya ot vozmozhnoi raboty (s 16 let): ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        s.experience = newExperience;
        break;
    }
    case 4: {
        std::cout << "Vvedite novuyu dolzhnost(s ZAGLAVNOI bykvi!): ";
        std::cin >> s.sector;
        break;
    }
    case 5: {
        std::cout << "Vvedite novyy email: ";
        std::cin >> s.email;
        break;
    }
    default:
        std::cout << "Nepravilnyy vybor. Poprobuyte eshche raz.\n";
        return;
    }

    std::cout << "Dannye uspeshno izmeneny!\n";
    saveToFile(); // Сохранение изменений в файл
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

void Agentstvo::searchBySector(const std::string& sector) {
    bool found = false;
    std::cout << std::left << std::setw(15) << "Imya"
        << std::setw(8) << "Vozrast"
        << std::setw(10) << "Opyt"
        << std::setw(20) << "Dolzhnost"
        << std::setw(30) << "Email" << "\n";
    std::cout << std::string(83, '*') << "\n"; 
    for (const auto& s : soiskateli) {
        if (s.sector.find(sector) != std::string::npos) {
            std::cout << std::left << std::setw(15) << s.name
                << std::setw(8) << s.age
                << std::setw(10) << s.experience
                << std::setw(20) << s.sector
                << std::setw(30) << s.email << "\n";
            found = true;
        }
    }
    if (!found) {
        std::cout << "\nSoiskateli s dolzhnost'u " << sector << " ne naydeny.\n";
    }
    std::cout << std::string(83, '*') << "\n";
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
