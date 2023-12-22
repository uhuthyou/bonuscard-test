// system.h

#ifndef SYSTEM_H
#define SYSTEM_H

#include <iostream>
#include <string>
#include "client.h"

class System {
private:
    std::string adminUsername;
    std::string adminPassword;

public:
    System(const std::string& username, const std::string& password);
    bool login(const std::string& username, const std::string& password);
    void registerClient();
    void depositToClientBalance(const std::string& clientName, double amount); // Добавим новый метод
};

#endif // SYSTEM_H
