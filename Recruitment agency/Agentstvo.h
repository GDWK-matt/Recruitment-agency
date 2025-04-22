#ifndef AGENTSTVO_H
#define AGENTSTVO_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cstring>

class Soiskatel {
public:
    std::string name;
    int age;
    int experience;
    std::string sector;
    std::string email;

    Soiskatel(std::string n, int a, int exp, std::string s, std::string e)
        : name(n), age(a), experience(exp), sector(s), email(e) {}
};

class Agentstvo {
private:
   

public: 
    std::vector<Soiskatel> soiskateli;
    void addSoiskatel();
    void showSoiskateli();
    void deleteSoiskatel(int index);
    void searchByAge(int age);
    void searchByExperience(int experience);
    void searchBySector(const std::string& sector);
    void saveToFile();
    void loadFromFile();
};

#endif // AGENTSTVO_H
