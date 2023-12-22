// client.cpp

#include "client.h"
#include <algorithm> // Добавим для std::shuffle
#include <random>    // Добавим для std::default_random_engine

// Инициализация статической переменной для уникального номера карты
int BonusCard::nextCardNumber = 123456789;

// Статический метод для генерации уникального номера карты
int BonusCard::generateUniqueCardNumber() {
    std::vector<int> digits{1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::random_device rd;
    std::default_random_engine rng(rd());
    std::shuffle(digits.begin(), digits.end(), rng);

    int uniqueNumber = 0;
    for (int digit : digits) {
        uniqueNumber = uniqueNumber * 10 + digit;
    }

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
}

void BonusCard::withdrawFromBalance(double amount) {
    // Проверка наличия достаточного баланса перед списанием
    if (balance >= amount) {
        balance -= amount;
    } else {
        std::cout << "Insufficient funds. Withdrawal failed.\n";
    }
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
}

BonusCard& Client::getBonusCard() {
    return card;
}

void Client::withdrawFromBalance(double amount) {
    // Списываем бонусы с баланса карты
    card.withdrawFromBalance(amount);
}

std::string Client::getName() const {
    return name;
}
