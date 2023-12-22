// client.h

#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>
#include <string>
#include <vector>
#include <ctime>

class Transaction {
public:
    enum class OperationType {
        Deposit,
        Withdrawal
    };

    std::time_t dateTime;
    OperationType operationType;
    double amount;
    double balanceAfterTransaction;
};

class BonusCard {
private:
    static int nextCardNumber;
    int cardNumber;
    double balance;
    std::vector<Transaction> transactions; // Вектор для хранения операций

    // Добавим статический метод для генерации уникального номера карты
    static int generateUniqueCardNumber();

public:
    BonusCard();
    int getCardNumber() const;
    double getBalance() const;
    void addToBalance(double amount);
    void withdrawFromBalance(double amount);
    const std::vector<Transaction>& getTransactions() const; // Новый метод
};

class Client {
private:
    std::string name;
    BonusCard card;

public:
    Client(const std::string& clientName);
    void registerClient();
    void displayInfo() const;
    BonusCard& getBonusCard();
    void withdrawFromBalance(double amount);
    std::string getName() const;
};

#endif // CLIENT_H
