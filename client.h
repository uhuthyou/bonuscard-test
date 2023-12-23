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
    std::vector<Transaction> transactions;

    static int generateUniqueCardNumber();

public:
    BonusCard();
    int cardNumber;
    double balance;
    int getCardNumber() const;
    double getBalance() const;
    void addToBalance(double amount);
    void withdrawFromBalance(double amount);
    const std::vector<Transaction>& getTransactions() const;
    void setCardNumber(int number);

    // Новый метод
    double getTransactionsTotal(Transaction::OperationType operationType) const;
};

class Client {
private:


public:
    Client(const std::string& clientName);
    std::string name;
    BonusCard card;
    void registerClient();
    void displayInfo() const;
    BonusCard& getBonusCard();
    const BonusCard& getBonusCard() const;
    void withdrawFromBalance(double amount);
    std::string getName() const;
};

#endif // CLIENT_H
