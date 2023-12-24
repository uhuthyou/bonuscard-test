// client.h

#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include"bonuscard.h"

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
