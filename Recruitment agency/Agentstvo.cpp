#include "agentstvo.h"

void Agentstvo::addSoiskatel() {
    std::string name, sector, email;
    int age, experience;
    bool education;
    int eduInput;

    std::cout << "Vvedite imya: ";
    std::cin >> name;
    std::cout << "Vvedite vozrast: ";
    while (!(std::cin >> age) || age >= 70 || age < 18) {
        std::cout << "Oshibka vvoda. Vvedite celoe chislo dlya vozrasta (18-70 let): ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    std::cout << "Vysshee obrazovanie? (1 - Da, 0 - Net): ";
    while (!(std::cin >> eduInput) || (eduInput != 0 && eduInput != 1)) {
        std::cout << "Oshibka vvoda. Vvedite 1 (Da) ili 0 (Net): ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    education = (eduInput == 1);

    std::cout << "Vvedite opyt raboty v godah: ";
    while (!(std::cin >> experience) || experience > age - 16) {
        std::cout << "Oshibka vvoda (opyt ne mozhet prevyshat vremya ot vozmozhnoj raboty (s 16 let)): ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    std::cout << "Vvedite dolzhnost: ";
    std::cin >> sector;
    std::cout << "Vvedite email: ";
    std::cin >> email;

    Soiskatel newSoiskatel(name, age, education, experience, sector, email);
    soiskateli.push_back(newSoiskatel);
    saveToFile();
    std::cout << std::string(100, '=') << "\n";
}

void Agentstvo::showSoiskateli() {
    if (soiskateli.empty()) {
        std::cout << std::string(100, '=') << "\n";
        std::cout << "Net soiskatelej dlya otobrazheniya.\n";
        std::cout << std::string(100, '=') << "\n";
        return;
    }

    std::sort(soiskateli.begin(), soiskateli.end(), [](const Soiskatel& a, const Soiskatel& b) {
        if (a.sector == b.sector) {
            return a.experience > b.experience;
            return a.education > b.education;
        }
        return a.sector < b.sector;
        });

    std::cout << std::left << std::setw(6) << "#"
        << std::setw(15) << "Imya"
        << std::setw(10) << "Vozrast"
        << std::setw(18) << "Vish. Obrazov."
        << std::setw(10) << "Opyt"
        << std::setw(20) << "Dolzhnost"
        << std::setw(30) << "Email" << "\n";

    std::cout << std::string(100, '=') << "\n";

    for (size_t i = 0; i < soiskateli.size(); ++i) {
        const Soiskatel& s = soiskateli[i];
        std::cout << std::left << std::setw(6) << i + 1
            << std::setw(15) << s.name
            << std::setw(10) << s.age
            << std::setw(18) << (s.education ? "Da" : "Net")
            << std::setw(10) << s.experience
            << std::setw(20) << s.sector
            << std::setw(30) << s.email << "\n";
        std::cout << std::string(100, '_') << "\n";
    }
}

void Agentstvo::updateSoiskatel(int index) {
    if (index < 0 || index >= soiskateli.size()) {
        std::cout << std::string(100, '=') << "\n";
        std::cout << "Nevernyj indeks soiskatelya!\n";
        std::cout << std::string(100, '=') << "\n";
        return;
    }

    Soiskatel& s = soiskateli[index];

    int ch;
    std::cout << "\nVyberite, chto izmenit:\n";
    std::cout << "1. Imya\n";
    std::cout << "2. Vozrast\n";
    std::cout << "3. Vysshee obrazovanie\n";
    std::cout << "4. Opyt raboty\n";
    std::cout << "5. Dolzhnost\n";
    std::cout << "6. Email\n";
    std::cout << "7. Nazad\n";
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
        std::cout << "Vvedite novyj vozrast: ";
        while (!(std::cin >> newAge) || newAge >= 70 || newAge <= 18) {
            std::cout << "Oshibka vvoda. Vvedite korrektnyj vozrast (18-70 let): ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        s.age = newAge;
        break;
    }
    case 3: {
        int eduInput;
        std::cout << "Vysshee obrazovanie? (1 - Da, 0 - Net): ";
        while (!(std::cin >> eduInput) || (eduInput != 0 && eduInput != 1)) {
            std::cout << "Oshibka vvoda. Vvedite 1 (Da) ili 0 (Net): ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        s.education = (eduInput == 1);
        break;
    }
    case 4: {
        int newExperience;
        std::cout << "Vvedite novyj opyt raboty: ";
        while (!(std::cin >> newExperience) || newExperience > s.age - 16) {
            std::cout << "Oshibka vvoda. Opyt ne mozhet prevyshat vremya ot vozmozhnoj raboty (s 16 let): ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        s.experience = newExperience;
        break;
    }
    case 5: {
        std::cout << "Vvedite novuyu dolzhnost (s zaglavnoj bukvy!): ";
        std::cin >> s.sector;
        break;
    }
    case 6: {
        std::cout << "Vvedite novyj email: ";
        std::cin >> s.email;
        break;
    }
    case 7: {
        break;
    }
    default:
        std::cout << "Nepravilnyj vybor. Poprobujte eshche raz.\n";
        return;
    }
    std::cout << std::string(100, '=') << "\n";
    std::cout << "Dannye uspeshno izmeneny!\n";
    std::cout << std::string(100, '=') << "\n";
    saveToFile();
}

void Agentstvo::deleteSoiskatel(int index) {
    if (index >= 0 && index < soiskateli.size()) {
        soiskateli.erase(soiskateli.begin() + index);
        saveToFile();
        std::cout << std::string(100, '=') << "\n";
        std::cout << "Soiskatel uspeshno udalen.\n";
        std::cout << std::string(100, '=') << "\n";
    }
    else {
        std::cout << std::string(100, '=') << "\n";
        std::cout << "Nevernyj indeks\n";
        std::cout << std::string(100, '=') << "\n";
    }
}

void Agentstvo::searchBySector(const std::string& sector) {
    bool found = false;
    std::cout << std::left << std::setw(15) << "Imya"
        << std::setw(10) << "Vozrast"
        << std::setw(18) << "Vish. Obrazov."
        << std::setw(10) << "Opyt"
        << std::setw(20) << "Dolzhnost"
        << std::setw(30) << "Email" << "\n";
    std::cout << std::string(100, '=') << "\n";
    for (const auto& s : soiskateli) {
        if (s.sector.find(sector) != std::string::npos) {
            std::cout << std::left << std::setw(15) << s.name
                << std::setw(10) << s.age
                << std::setw(18) << (s.education ? "Da" : "Net")
                << std::setw(10) << s.experience
                << std::setw(20) << s.sector
                << std::setw(30) << s.email << "\n";
            found = true;
            std::cout << std::string(100, '_') << "\n";
        }
        
    }
    if (!found) {
        std::cout << "\nSoiskateli s dolzhnostyu " << sector << " ne najdeny.\n";
        std::cout << std::string(100, '_') << "\n";
    }
   
}

void Agentstvo::searchByOpyt(int minexp) {
    bool found = false;
    std::cout << std::left << std::setw(15) << "Imya"
        << std::setw(10) << "Vozrast"
        << std::setw(18) << "Vish. Obrazov."
        << std::setw(10) << "Opyt"
        << std::setw(20) << "Dolzhnost"
        << std::setw(30) << "Email" << "\n";
    std::cout << std::string(100, '=') << "\n";
    for (const auto& s : soiskateli) {
        if (s.experience >= minexp) {
            std::cout << std::left << std::setw(15) << s.name
                << std::setw(10) << s.age
                << std::setw(18) << (s.education ? "Da" : "Net")
                << std::setw(10) << s.experience
                << std::setw(20) << s.sector
                << std::setw(30) << s.email << "\n";
            found = true;
            std::cout << std::string(100, '_') << "\n";
        }
    }
    if (!found) {
        std::cout << "\nSoiskateli s opytim raboty ot " << minexp << " ne najdeny.\n";
        std::cout << std::string(100, '_') << "\n";
    }
}

void Agentstvo::searchByEducation(bool educ) {
    bool found = false;
    std::cout << std::left << std::setw(15) << "Imya"
        << std::setw(10) << "Vozrast"
        << std::setw(18) << "Vish. Obrazov."
        << std::setw(10) << "Opyt"
        << std::setw(20) << "Dolzhnost"
        << std::setw(30) << "Email" << "\n";
    std::cout << std::string(100, '=') << "\n";

    for (const auto& s : soiskateli) {
        if (s.education == educ) {
            std::cout << std::left << std::setw(15) << s.name
                << std::setw(10) << s.age
                << std::setw(18) << (s.education ? "Da" : "Net")
                << std::setw(10) << s.experience
                << std::setw(20) << s.sector
                << std::setw(30) << s.email << "\n";
            found = true;
            std::cout << std::string(100, '_') << "\n";
        }
    }

    if (!found) {
        std::cout << "Soiskateli " << (educ ? "s" : "bez") << " vish. obrazov. ne naydeno\n";
        std::cout << std::string(100, '_') << "\n";
    }
}

void Agentstvo::searchPo() {
    int vib;
    std::cout << "Vyberite poisk:\n";
    std::cout << "1. Dolzhnost'\n";
    std::cout << "2. Nalichie vish. obrazov.\n";
    std::cout << "3. Minimal'niy opyt raboty\n";
    std::cout << "4. Nazad\n";

    std::cout << "Vybor: ";
    while (!(std::cin >> vib) || (vib < 1 || vib > 4)) {
        std::cout << "Oshibka vvoda. Pozhaluysta, vvedite 1, 2, 3 ili 4: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::cout << "\n";

    switch (vib) {
    case 1: {
        std::string sector;
        std::cout << "Vvedite dolzhnost (Nazvanie dolzhnosti vvodite s ZAGLAVNOI bykvi!): ";
        std::cin >> sector;
        std::cout << "\n";
        searchBySector(sector);
        break;
    }
    case 2: {
        bool educ;
        std::cout << "Da (1) | Net (0): ";
        std::cin >> educ;
        std::cout << "\n";
        searchByEducation(educ);
        break;
    }
    case 3: {
        int minexp;
        std::cout << "Vvedite minimal'niy opyt raboty: ";
        std::cin >> minexp;
        std::cout << "\n";
        searchByOpyt(minexp);
        break;
    }
    case 4: {
        break;
    }
    default:
        std::cout << "Nepravilnyj vybor. Poprobujte eshche raz.\n";
        std::cout << std::string(100, '=') << "\n";
        return;
    }
    
}

void Agentstvo::saveToFile() {
    std::ofstream file("soiskateli.txt");
    if (!file) {
        std::cout << std::string(100, '=') << "\n";
        std::cerr << "OSHIBKA: Nelzya otkrit file dlya chteniya!\n";
        std::cout << std::string(100, '=') << "\n";
        return;
    }

    for (const auto& s : soiskateli) {
        file << s.name << '\n'
            << s.age << '\n'
            << (s.education ? 1 : 0) << '\n'
            << s.experience << '\n'
            << s.sector << '\n'
            << s.email << '\n';
    }
}


void Agentstvo::loadFromFile() {
    std::ifstream file("soiskateli.txt");
    if (!file) {
        std::cout << std::string(100, '=') << "\n";
        std::cout << "PREDUPREZHDENIE: file ne naiden! Noviy budet sozdan pri sohranenii!\n";
        std::cout << std::string(100, '=') << "\n";
        return;
    }// Если файл не открылся, просто выходим

    soiskateli.clear(); // Очищаем старые данные

    // Читаем файл построчно и заполняем вектор
    std::string name, sector, email;
    int age, experience;
    bool education;
    while (file >> name >> age >> education >> experience >> sector >> email) { 
    soiskateli.emplace_back(name, age, education, experience, sector, email);
    }
}