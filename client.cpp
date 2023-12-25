// client.cpp

#include "client.h"
#include <algorithm> // Добавим для std::shuffle
//#include <random>    // Добавим для std::default_random_engine
#include <iomanip>   // Добавим для форматирования вывода
#include <ctime>
#include <cstdlib>

// Инициализация статической переменной для уникального номера карты
//int BonusCard::nextCardNumber = 123456789;

// Статический метод для генерации уникального номера карты
int BonusCard::generateUniqueCardNumber() {
    std::mt19937 generator(static_cast<unsigned int>(std::time(nullptr)));
            std::uniform_int_distribution<int> distribution(1000000000, 9999999999);

            int uniqueNumber = distribution(generator);

            return uniqueNumber;
        }

BonusCard::BonusCard() : cardNumber(generateUniqueCardNumber()), balance(0.0) {}

int BonusCard::getCardNumber() const {
    return cardNumber;
}

double BonusCard::getBalance() const {
    return balance;
}

void BonusCard::addToBalance(double amount) {
    balance += amount;

    // Записываем операцию в историю
    Transaction transaction;
    transaction.dateTime = std::time(nullptr);
    transaction.operationType = Transaction::OperationType::Deposit;
    transaction.amount = amount;
    transaction.balanceAfterTransaction = balance;

    transactions.push_back(transaction);
}

void BonusCard::withdrawFromBalance(double amount) {
    // Проверка наличия достаточного баланса перед списанием
    if (balance >= amount) {
        balance -= amount;

        // Записываем операцию в историю
        Transaction transaction;
        transaction.dateTime = std::time(nullptr);
        transaction.operationType = Transaction::OperationType::Withdrawal;
        transaction.amount = amount;
        transaction.balanceAfterTransaction = balance;

        transactions.push_back(transaction);
    } else {
        std::cout << "Insufficient funds. Withdrawal failed.\n";
    }
}

const std::vector<Transaction>& BonusCard::getTransactions() const {
    return transactions;
}

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
            std::tm* tm_info = std::localtime(&transaction.dateTime);
            char buffer[20];
            std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", tm_info);

            std::string operationTypeStr = (transaction.operationType == Transaction::OperationType::Deposit)
                                               ? "Deposit"
                                               : "Withdrawal";

            std::cout << std::setw(20) << buffer << std::setw(15) << operationTypeStr << std::setw(15)
                      << transaction.amount << std::setw(20) << transaction.balanceAfterTransaction << "\n";
        }
    }
}

BonusCard& Client::getBonusCard() {
    return card;
}

const BonusCard& Client::getBonusCard() const {
    return card;
}

void Client::withdrawFromBalance(double amount) {
    // Списываем бонусы с баланса карты
    card.withdrawFromBalance(amount);
}

std::string Client::getName() const {
    return name;
}

double BonusCard::getTransactionsTotal(Transaction::OperationType operationType) const {
    double total = 0.0;

    for (const Transaction& transaction : transactions) {
        if (transaction.operationType == operationType) {
            total += transaction.amount;
        }
    }

    return total;
}

void BonusCard::setCardNumber(int number) {
    cardNumber = number;
}
