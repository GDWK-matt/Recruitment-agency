#include <fstream>
#include <string>
#include <vector>

class User {
public:
    std::string login;
    std::string password;
    bool isAdmin;

    User(const std::string& l, const std::string& p, bool admin)
        : login(l), password(p), isAdmin(admin) {}
};

class AuthSystem {
public:
    std::vector<User> users;
    const std::string userFile = "users.txt";

    void ensureFileExists() {
        std::ifstream testFile(userFile);
        if (!testFile) {
            std::ofstream newFile(userFile);
            // Создаем администратора по умолчанию
            newFile << "Matvej 2356 1\n";
        }
    }

    void loadUsers() {
        ensureFileExists();

        std::ifstream file(userFile);
        std::string login, password;
        int adminFlag;

        while (file >> login >> password >> adminFlag) {
            users.emplace_back(login, password, adminFlag == 1);
        }
    }

    void saveUsers() {
        std::ofstream file(userFile);
        for (const auto& user : users) {
            file << user.login << " " << user.password << " " << (user.isAdmin ? 1 : 0) << "\n";
        }
    }

    AuthSystem() {
        loadUsers();
    }

    bool checkAuth(const std::string& login, const std::string& password, bool& isAdmin) {
        for (const auto& user : users) {
            if (user.login == login && user.password == password) {
                isAdmin = user.isAdmin;
                return true;
            }
        }
        return false;
    }

    bool addUser(const std::string& login, const std::string& password, bool isAdmin) {
        for (const auto& user : users) {
            if (user.login == login) return false;
        }

        users.emplace_back(login, password, isAdmin);
        saveUsers();
        return true;
    }

    bool removeUser(const std::string& login) {
        if (!users.empty() && users[0].login == login && users[0].isAdmin) {
            return false; // Нельзя удалить первого админа
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
};