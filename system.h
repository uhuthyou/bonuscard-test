// system.h

#ifndef SYSTEM_H
#define SYSTEM_H

#include <iostream>
#include <string>
#include <vector>
#include "client.h"

class System {
private:
    std::string adminUsername;
    std::string adminPassword;
    std::vector<Client> clients; // Добавим вектор для хранения зарегистрированных клиентов

public:
    System(const std::string& username, const std::string& password);
    bool login(const std::string& username, const std::string& password);
    void registerClient();
    void depositToClientBalance(const std::string& clientName, double amount);
    void withdrawFromClientBalance(const std::string& clientName, double amount);
};

#endif // SYSTEM_H
