// system.cpp

#include "system.h"
#include <algorithm>

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

    // Добавляем клиента в вектор
    clients.push_back(newClient);
}

void System::depositToClientBalance(const std::string& clientName, double amount) {
    // Ищем клиента в векторе
    auto it = std::find_if(clients.begin(), clients.end(),
                           [&clientName](const Client& client) { return client.getName() == clientName; });

    if (it != clients.end()) {
        // Если клиент найден, пополняем его баланс
        it->getBonusCard().addToBalance(amount);

        // Выводим информацию о клиенте после пополнения баланса
        std::cout << "Deposit successful!\n";
        it->displayInfo();
    } else {
        std::cout << "Client not found. Deposit failed.\n";
    }
}

void System::withdrawFromClientBalance(const std::string& clientName, double amount) {
    // Ищем клиента в векторе
    auto it = std::find_if(clients.begin(), clients.end(),
                           [&clientName](const Client& client) { return client.getName() == clientName; });

    if (it != clients.end()) {
        // Если клиент найден, списываем бонусы с его баланса
        it->withdrawFromBalance(amount);

        // Выводим информацию о клиенте после списания бонусов
        std::cout << "Withdrawal successful!\n";
        it->displayInfo();
    } else {
        std::cout << "Client not found. Withdrawal failed.\n";
    }
}

void System::displayClientTransactionHistory(const std::string& clientName) const {
    // Ищем клиента в векторе
    auto it = std::find_if(clients.begin(), clients.end(),
                           [&clientName](const Client& client) { return client.getName() == clientName; });

    if (it != clients.end()) {
        // Если клиент найден, выводим историю операций
        it->displayInfo();
    } else {
        std::cout << "Client not found. Unable to display transaction history.\n";
    }
}
