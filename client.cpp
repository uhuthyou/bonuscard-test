// client.cpp

#include "client.h"
#include "system.h"
#include <algorithm> // Добавим для std::shuffle
#include <iomanip>   // Добавим для форматирования вывода
#include <ctime>
#include <cstdlib>

// Статический метод для генерации уникального номера карты

Client::Client(const std::string& clientName) : name(clientName) {}

void Client::registerClient() {
    // Генерация уникального номера бонусной карты и регистрация клиента
    std::cout << "Client " << name << " registered successfully.\n";
    std::cout << "Card Number: " << card.getCardNumber() << "\n";
    std::cout << "Balance: " << card.getBalance() << "\n";
}

void Client::displayInfo() const {
    // Вывод информации о клиенте
    std::cout << "Client Name: " << name << "\n";
    std::cout << "Card Number: " << card.getCardNumber() << "\n";
    std::cout << "Balance: " << card.getBalance() << "\n";

    // Вывод истории операций
    const std::vector<Transaction>& transactions = card.getTransactions();
    if (!transactions.empty()) {
        std::cout << "\nTransaction History:\n";
        std::cout << std::setw(20) << "Date & Time" << std::setw(15) << "Operation" << std::setw(15) << "Amount"
                  << std::setw(20) << "Balance After\n";
        std::cout << "-----------------------------------------------\n";
        for (const auto& transaction : transactions) {
//            std::tm* tm_info = std::localtime(&transaction.dateTime);
            char buffer[20];
           // std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", tm_info);

            std::string operationTypeStr = (transaction.operationType == Transaction::OperationType::Deposit)
                                               ? "Deposit"
                                               : "Withdrawal";

            std::cout << std::setw(20) << buffer << std::setw(15) << operationTypeStr << std::setw(15)
                      << transaction.amount << std::setw(20) << transaction.balanceAfterTransaction << "\n";
        }
    }
}

void Client::withdrawFromBalance(double amount) {
    // Списываем бонусы с баланса карты
    card.withdrawFromBalance(amount);
}

std::string Client::getName() const {
    return name;
}
