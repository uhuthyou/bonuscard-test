#ifndef BONUSCARD
#define BONUSCARD

#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include "transaction.h"

class BonusCard {
private:
    //static int nextCardNumber;
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
#endif // BONUSCARD

