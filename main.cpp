// main.cpp

#include "system.h"

int main() {
    // Создаем объект системы
    System mySystem("1", "1");

    // Вводим логин и пароль
    std::string inputUsername, inputPassword;
    std::cout << "Enter username: ";
    std::cin >> inputUsername;
    std::cout << "Enter password: ";
    std::cin >> inputPassword;

    // Пытаемся войти в систему
    if (mySystem.login(inputUsername, inputPassword)) {
        // Если вход успешен, регистрируем клиента
        mySystem.registerClient();

        // Вводим имя клиента для пополнения баланса
        std::string clientToDeposit;
        std::cout << "Enter client name to deposit: ";
        std::cin >> clientToDeposit;

        // Вводим количество бонусов для пополнения баланса
        double depositAmount;
        std::cout << "Enter deposit amount: ";
        std::cin >> depositAmount;

        // Пополняем баланс клиента
        mySystem.depositToClientBalance(clientToDeposit, depositAmount);
    }

    return 0;
}
