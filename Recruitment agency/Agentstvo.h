#ifndef AGENTSTVO_H
#define AGENTSTVO_H

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <fstream>
#include <cstring>
#include <algorithm>

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
    void updateSoiskatel(int index);
    void deleteSoiskatel(int index);
    void searchBySector(const std::string& sector);
    void saveToFile();
    void loadFromFile();
};

#endif // AGENTSTVO_H
