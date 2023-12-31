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
    std::vector<Client> clients;

    double totalDeposited;  // Общая сумма начисленных бонусов по всем клиентам
    double totalWithdrawn;  // Общая сумма списанных бонусов по всем клиентам

public:
    System(const std::string& username, const std::string& password);

    void userInterface();
    void displayAllClients() const;  // Новый метод
    bool login(const std::string& username, const std::string& password);
    void registerClient();
    void depositToClientBalance(const std::string& clientName, double amount);
    void withdrawFromClientBalance(const std::string& clientName, double amount);
    void displayClientTransactionHistory(const std::string& clientName) const;
    void displayAnnualReport() const;  // Новый метод
    void displayClientsFromFile() const;
    void depositToClientBalance();
    void updateClientInFile(const Client& updatedClient) const;
    void readClientsFromFile(); // Обновленное объявление
    void findClient(const std::string& clientName) const;
    void recordOperation(const std::string& clientName, char operationType, double amount);
    void performOperation(const std::string& clientName, char operationType, double amount);

    void displayClientSummary(const std::string& clientName) const;

    void displayClientOperations(const std::string& clientName) const;
    void displayClientOperationHistory(const std::string& clientName) const;

    int findCardNumberByName(const std::string& clientName) const;


};

#endif // SYSTEM_H
