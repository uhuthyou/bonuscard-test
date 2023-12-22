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
    clients.push_back(newClient);  // Добавляем зарегистрированного клиента в вектор
}

void System::depositToClientBalance(const std::string& clientName, double amount) {
    // Ищем клиента в векторе
    for (auto& client : clients) {
        if (client.getName() == clientName) {
            // Пополняем баланс найденного клиента
            client.getBonusCard().addToBalance(amount);

            // Выводим информацию о клиенте после пополнения баланса
            std::cout << "Deposit successful!\n";
            client.displayInfo();
            return;  // Завершаем выполнение метода после обработки клиента
        }
    }

    std::cout << "Client not found.\n";
}

void System::withdrawFromClientBalance(const std::string& clientName, double amount) {
    // Ищем клиента в векторе
    for (auto& client : clients) {
        if (client.getName() == clientName) {
            // Списываем бонусы с баланса найденного клиента
            client.withdrawFromBalance(amount);

            // Выводим информацию о клиенте после списания бонусов
            std::cout << "Withdrawal successful!\n";
            client.displayInfo();
            return;  // Завершаем выполнение метода после обработки клиента
        }
    }

    std::cout << "Client not found.\n";
}
