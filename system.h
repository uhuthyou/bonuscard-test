// system.h

#ifndef SYSTEM_H
#define SYSTEM_H

#include "client.h"
#include <iostream>
#include <vector>

class System {
private:
    std::string adminUsername;
    std::string adminPassword;

    // Вектор для хранения зарегистрированных клиентов
    std::vector<Client> clients;

public:
    System(const std::string& username, const std::string& password);

    bool login(const std::string& username, const std::string& password);
    void registerClient();
    void depositToClientBalance(const std::string& clientName, double amount);
    void withdrawFromClientBalance(const std::string& clientName, double amount);
    void displayClientTransactionHistory(const std::string& clientName) const; // Новый метод
};

#endif // SYSTEM_H
