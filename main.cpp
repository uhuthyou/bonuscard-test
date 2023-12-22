// main.cpp

#include "system.h"
#include <iostream>

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
        bool exitMenu = false;
        while (!exitMenu) {
            // Выводим меню выбора операций
            std::cout << "\nMenu:\n";
            std::cout << "1. Add client\n";
            std::cout << "2. Deposit to client balance\n";
            std::cout << "3. Withdraw from client balance\n";
            std::cout << "4. Display client transaction history\n";
            std::cout << "5. Display annual report\n"; // Новая опция
            std::cout << "6. Exit\n";
            std::cout << "Enter your choice: ";

            int choice;
            std::cin >> choice;

            switch (choice) {
                case 1: {
                    // Регистрация нового клиента
                    mySystem.registerClient();
                    break;
                }
                case 2: {
                    // Пополнение баланса клиента
                    std::string clientToDeposit;
                    std::cout << "Enter client name to deposit: ";
                    std::cin >> clientToDeposit;

                    double depositAmount;
                    std::cout << "Enter deposit amount: ";
                    std::cin >> depositAmount;

                    mySystem.depositToClientBalance(clientToDeposit, depositAmount);
                    break;
                }
                case 3: {
                    // Списание бонусов с баланса клиента
                    std::string clientToWithdraw;
                    std::cout << "Enter client name to withdraw from: ";
                    std::cin >> clientToWithdraw;

                    double withdrawAmount;
                    std::cout << "Enter withdrawal amount: ";
                    std::cin >> withdrawAmount;

                    mySystem.withdrawFromClientBalance(clientToWithdraw, withdrawAmount);
                    break;
                }
                case 4: {
                    // Вывод детализации операций клиента
                    std::string clientName;
                    std::cout << "Enter client name to display transaction history: ";
                    std::cin >> clientName;

                    mySystem.displayClientTransactionHistory(clientName);
                    break;
                }
                case 5: {
                    // Вывод годового отчета
                    mySystem.displayAnnualReport();
                    break;
                }
                case 6: {
                    // Выход из программы
                    exitMenu = true;
                    break;
                }
                default:
                    std::cout << "Invalid choice. Please enter a valid option.\n";
            }
        }
    }

    return 0;
}
