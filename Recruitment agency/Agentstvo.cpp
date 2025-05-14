#include "agentstvo.h"

void Agentstvo::addSoiskatel() {
    std::string name, sector, email;
    int age, experience;
    bool education;
    int eduInput;

    std::cout << "������� ���: ";
    std::cin >> name;
    std::cout << "������� �������: ";
    while (!(std::cin >> age) || age >= 70 || age < 18) {
        std::cout << "������ �����. ������� ����� ����� ��� �������� (18-70 ���): ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    std::cout << "������ �����������? (1 - ��, 0 - ���): ";
    while (!(std::cin >> eduInput) || (eduInput != 0 && eduInput != 1)) {
        std::cout << "������ �����. ������� 1 (��) ��� 0 (���): ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    education = (eduInput == 1);

    std::cout << "������� ���� ������ � �����: ";
    while (!(std::cin >> experience) || experience > age - 16) {
        std::cout << "������ ����� (���� �� ����� ��������� ����� �� ��������� ������ (� 16 ���)): ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    std::cout << "������� ���������: ";
    std::cin >> sector;
    std::cout << "������� email: ";
    std::cin >> email;

    Soiskatel newSoiskatel(name, age, education, experience, sector, email);
    soiskateli.push_back(newSoiskatel);
    saveToFile();
    std::cout << std::string(100, '=') << "\n";
}

void Agentstvo::showSoiskateli() {
    if (soiskateli.empty()) {
        std::cout << std::string(100, '=') << "\n";
        std::cout << "��� ����������� ��� �����������.\n";
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
        << std::setw(15) << "���"
        << std::setw(10) << "�������"
        << std::setw(18) << "����. �������."
        << std::setw(10) << "����"
        << std::setw(20) << "���������"
        << std::setw(30) << "Email" << "\n";

    std::cout << std::string(100, '=') << "\n";

    for (size_t i = 0; i < soiskateli.size(); ++i) {
        const Soiskatel& s = soiskateli[i];
        std::cout << std::left << std::setw(6) << i + 1
            << std::setw(15) << s.name
            << std::setw(10) << s.age
            << std::setw(18) << (s.education ? "��" : "���")
            << std::setw(10) << s.experience
            << std::setw(20) << s.sector
            << std::setw(30) << s.email << "\n";
        std::cout << std::string(100, '_') << "\n";
    }
}

void Agentstvo::updateSoiskatel(int index) {
    if (index < 0 || index >= soiskateli.size()) {
        std::cout << std::string(100, '=') << "\n";
        std::cout << "�������� ������ ����������!\n";
        std::cout << std::string(100, '=') << "\n";
        return;
    }

    Soiskatel& s = soiskateli[index];
    while (true) {
        int ch;
        std::cout << "\n��������, ��� ��������:\n";
        std::cout << "1. ���\n";
        std::cout << "2. �������\n";
        std::cout << "3. ������ �����������\n";
        std::cout << "4. ���� ������\n";
        std::cout << "5. ���������\n";
        std::cout << "6. ��. �����\n";
        std::cout << "7. �����\n";
        std::cout << "�����: ";
        std::cin >> ch;
        if (ch == 7) break;

        switch (ch) {
        case 1: {
            std::cout << "������� ����� ���: ";
            std::cin >> s.name;
            break;
        }
        case 2: {
            int newAge;
            std::cout << "������� ����� �������: ";
            while (!(std::cin >> newAge) || newAge >= 70 || newAge <= 18) {
                std::cout << "������ �����. ������� ������� �� 18-70 ���: ";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            s.age = newAge;
            break;
        }
        case 3: {
            int eduInput;
            std::cout << "������ �����������? (1 - ��, 0 - ���): ";
            while (!(std::cin >> eduInput) || (eduInput != 0 && eduInput != 1)) {
                std::cout << "������ �����. ������� 1 (��) ��� 0 (���): ";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            s.education = (eduInput == 1);
            break;
        }
        case 4: {
            int newExperience;
            std::cout << "������� ����� ���� ������: ";
            while (!(std::cin >> newExperience) || newExperience > s.age - 18) {
                std::cout << "������ �����. ���� �� ����� ��������� ����� �� ���������� ������������ (� 18 ���): ";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            s.experience = newExperience;
            break;
        }
        case 5: {
            std::cout << "������� ����� ��������� (� ��������� �����!): ";
            std::cin >> s.sector;
            break;
        }
        case 6: {
            std::cout << "������� ����� ��. �����: ";
            std::cin >> s.email;
            break;
        }
       
        default:
            std::cout << "�������� �����. ���������� ��� ���!\n";
            return;
        }
        std::cout << std::string(100, '=') << "\n";
        std::cout << "������ ������� ��������!\n";
        std::cout << std::string(100, '=') << "\n";
        saveToFile();
    }
}
void Agentstvo::deleteSoiskatel(int index) {
    if (index >= 0 && index < soiskateli.size()) {
        soiskateli.erase(soiskateli.begin() + index);
        saveToFile();
        std::cout << std::string(100, '=') << "\n";
        std::cout << "���������� ������� ������.\n";
        std::cout << std::string(100, '=') << "\n";
    }
    else {
        std::cout << std::string(100, '=') << "\n";
        std::cout << "�������� ������\n";
        std::cout << std::string(100, '=') << "\n";
    }
}

void Agentstvo::searchBySector(const std::string& sector) {
    bool found = false;
    std::cout << std::left << std::setw(15) << "���"
        << std::setw(10) << "�������"
        << std::setw(18) << "���. �������."
        << std::setw(10) << "����"
        << std::setw(20) << "���������"
        << std::setw(30) << "Email" << "\n";
    std::cout << std::string(100, '=') << "\n";
    for (const auto& s : soiskateli) {
        if (s.sector.find(sector) != std::string::npos) {
            std::cout << std::left << std::setw(15) << s.name
                << std::setw(10) << s.age
                << std::setw(18) << (s.education ? "��" : "���")
                << std::setw(10) << s.experience
                << std::setw(20) << s.sector
                << std::setw(30) << s.email << "\n";
            found = true;
            std::cout << std::string(100, '_') << "\n";
        }

    }
    if (!found) {
        std::cout << "\n���������� � ���������� " << sector << " �� �������.\n";
        std::cout << std::string(100, '_') << "\n";
    }

}

void Agentstvo::searchByOpyt(int minexp) {
    bool found = false;
    std::cout << std::left << std::setw(15) << "���"
        << std::setw(10) << "�������"
        << std::setw(18) << "���. �������."
        << std::setw(10) << "����"
        << std::setw(20) << "���������"
        << std::setw(30) << "Email" << "\n";
    std::cout << std::string(100, '=') << "\n";
    for (const auto& s : soiskateli) {
        if (s.experience >= minexp) {
            std::cout << std::left << std::setw(15) << s.name
                << std::setw(10) << s.age
                << std::setw(18) << (s.education ? "��" : "���")
                << std::setw(10) << s.experience
                << std::setw(20) << s.sector
                << std::setw(30) << s.email << "\n";
            found = true;
            std::cout << std::string(100, '_') << "\n";
        }
    }
    if (!found) {
        std::cout << "\n���������� � ������ ������ �� " << minexp << " �� �������.\n";
        std::cout << std::string(100, '_') << "\n";
    }
}

void Agentstvo::searchByEducation(bool educ) {
    bool found = false;
    std::cout << std::left << std::setw(15) << "���"
        << std::setw(10) << "�������"
        << std::setw(18) << "���. �������."
        << std::setw(10) << "����"
        << std::setw(20) << "���������"
        << std::setw(30) << "Email" << "\n";
    std::cout << std::string(100, '=') << "\n";

    for (const auto& s : soiskateli) {
        if (s.education == educ) {
            std::cout << std::left << std::setw(15) << s.name
                << std::setw(10) << s.age
                << std::setw(18) << (s.education ? "��" : "���")
                << std::setw(10) << s.experience
                << std::setw(20) << s.sector
                << std::setw(30) << s.email << "\n";
            found = true;
            std::cout << std::string(100, '_') << "\n";
        }
    }

    if (!found) {
        std::cout << "���������� " << (educ ? "�" : "���") << " ���. �������. �� �������\n";
        std::cout << std::string(100, '_') << "\n";
    }
}

void Agentstvo::searchPo() {

    int vib;
    std::cout << "�������� �����:\n";
    std::cout << "1. ���������\n";
    std::cout << "2. ������� ���. ���������.\n";
    std::cout << "3. ����������� ���� ������\n";
    std::cout << "4. �����\n";

    std::cout << "�����: ";
    while (!(std::cin >> vib) || (vib < 1 || vib > 4)) {
        std::cout << "������ �����. ����������, ������� 1, 2, 3 ��� 4: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::cout << "\n";

    switch (vib) {
    case 1: {
        std::string sector;
        std::cout << "������� ��������� (�������� ��������� ������� � ��������� �����!): ";
        std::cin >> sector;
        std::cout << "\n";
        searchBySector(sector);
        break;
    }
    case 2: {
        bool educ;
        std::cout << "�� (1) | ��� (0): ";
        std::cin >> educ;
        std::cout << "\n";
        searchByEducation(educ);
        break;
    }
    case 3: {
        int minexp;
        std::cout << "������� ����������� ���� ������: ";
        std::cin >> minexp;
        std::cout << "\n";
        searchByOpyt(minexp);
        break;
    }
    case 4: {
        break;
    }
    default:
        std::cout << "������������ �����. ���������� ��� ���.\n";
        std::cout << std::string(100, '=') << "\n";
        return;
    }

}

void Agentstvo::saveToFile() {
    std::ofstream file("soiskateli.txt");
    if (!file) {
        std::cout << std::string(100, '=') << "\n";
        std::cerr << "������: ������ ������� ���� soiskateli.txt ��� ������!\n";
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
        std::cout << "��������������: ���� soiskateli.txt �� ������! ����� ����� ������ ��� ����������!\n";
        std::cout << std::string(100, '=') << "\n";
        return;
    }
    soiskateli.clear(); // ������� ������ ������

    // ������ ���� ��������� � ��������� ������
    std::string name, sector, email;
    int age, experience;
    bool education;
    while (file >> name >> age >> education >> experience >> sector >> email) { 
    soiskateli.emplace_back(name, age, education, experience, sector, email);
    }
}