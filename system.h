// system.h

#ifndef SYSTEM_H
#define SYSTEM_H

#include <iostream>
#include <string>
#include "client.h" // Добавим включение заголовочного файла с классом Client

class System {
private:
    std::string adminUsername;
    std::string adminPassword;

public:
    System(const std::string& username, const std::string& password);
    bool login(const std::string& username, const std::string& password);
    void registerClient(); // Добавим объявление нового метода
};

#endif // SYSTEM_H
