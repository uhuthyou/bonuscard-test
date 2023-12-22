// client.h

#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>
#include <string>
#include <vector>

class BonusCard {
private:
    static int nextCardNumber;
    int cardNumber;
    double balance;

    // Добавим статический метод для генерации уникального номера карты
    static int generateUniqueCardNumber();

public:
    BonusCard();
    int getCardNumber() const;
    double getBalance() const;
    void addToBalance(double amount);
};

class Client {
private:
    std::string name;
    BonusCard card;

public:
    Client(const std::string& clientName);
    void registerClient();
    void displayInfo() const;
};

#endif // CLIENT_H