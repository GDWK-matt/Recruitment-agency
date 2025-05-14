#include "auth.h"

void AuthSystem::ensureFileExists() {
    std::ifstream testFile(userFile);
    if (!testFile) {
        std::ofstream newFile(userFile);
        // ������� �������������� �� ���������
        newFile << "Matvej 2356 1\n";
    }
}

void AuthSystem::saveUsers() {
    std::ofstream file(userFile);
    for (const auto& user : users) {
        file << user.login << " " << user.password << " " << (user.isAdmin ? 1 : 0) << "\n";
    }
}

void AuthSystem::loadUsers() {
    ensureFileExists();
    std::ifstream file(userFile);

    users.clear();

    std::string login, password;
    int adminFlag;

    while (file >> login >> password >> adminFlag) {
        users.emplace_back(login, password, adminFlag == 1);
    }
}

bool AuthSystem::checkAuth(const std::string& login, const std::string& password, bool& isAdmin) {
    for (const auto& user : users) {
        if (user.login == login && user.password == password) {
            isAdmin = user.isAdmin;
            return true;
        }
    }
    return false;
}

bool AuthSystem::addUser(const std::string& login, const std::string& password, bool isAdmin) {
    for (const auto& user : users) {
        if (user.login == login) return false;
    }

    users.emplace_back(login, password, isAdmin);
    saveUsers();
    return true;
}
    


bool AuthSystem::removeUser(const std::string& login) {
    if (!users.empty() && users[0].login == login && users[0].isAdmin) {
        return false; // ������ ������� ������� ������
    }
  
    for (auto it = users.begin(); it != users.end(); ++it) {
        if (it->login == login) {
            users.erase(it);
            saveUsers();
            return true;
        }
    }
    return false;
}

