// system.cpp

#include "system.h"

System::System(const std::string& username, const std::string& password)
    : adminUsername(username), adminPassword(password) {}

bool System::login(const std::string& username, const std::string& password) {
    if (username == adminUsername && password == adminPassword) {
        std::cout << "Successfully logged in!\n";
        return true;
    } else {
        std::cout << "Login failed. Please check your username and password.\n";
        return false;
    }
}

void System::registerClient() {
    std::string clientName;
    std::cout << "Enter client name: ";
    std::cin >> clientName;

    // Создаем объект клиента и регистрируем его
    Client newClient(clientName);
    newClient.registerClient();
}

void System::depositToClientBalance(const std::string& clientName, double amount) {
    // Создаем объект клиента и пополняем его баланс
    Client client(clientName);
    client.getBonusCard().addToBalance(amount);

    // Выводим информацию о клиенте после пополнения баланса
    std::cout << "Deposit successful!\n";
    client.displayInfo();
}
