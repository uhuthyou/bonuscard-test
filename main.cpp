// main.cpp

#include "system.h"
#include <iostream>


int main() {
    // Создаем объект системы
    System mySystem("1", "1");

    // Вводим логин и пароль
    std::cout << "-------------------- Log in to the system -------------------- \n";
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
            std::cout << "1. Add client\n"; //+
            std::cout << "2. Deposit to client balance\n"; //+
            std::cout << "3. Withdraw from client balance\n"; //+
            std::cout << "4. Display client transaction history\n";
            std::cout << "5. Display annual report\n";
            std::cout << "6. Display all clients\n"; //+
            std::cout << "7. Find client\n"; //+
            std::cout << "8. Exit\n";
            std::cout << "9. Operation test\n";
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

                // Вызываем метод depositToClientBalance
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
                    // Вывод информации о всех клиентах
                    mySystem.displayClientsFromFile();
                    break;
                }
            case 7: {
                // Поиск клиента
                std::string clientToFind;
                std::cout << "Enter client name to find: ";
                std::cin >> clientToFind;

                mySystem.findClient(clientToFind);
                break;
            }
                case 8: {
                    // Выход из программы
                    exitMenu = true;
                    break;
                }
            case 9: {
                // Запись операции в файл
                std::string clientForOperation;
                char operationType;
                double operationAmount;

                std::cout << "Enter client name: ";
                std::cin >> clientForOperation;

                std::cout << "Enter operation type (+ for deposit, - for withdrawal): ";
                std::cin >> operationType;

                std::cout << "Enter operation amount: ";
                std::cin >> operationAmount;

                mySystem.performOperation(clientForOperation, operationType, operationAmount);
                break;
            }

                default:
                    std::cout << "Invalid choice. Please enter a valid option.\n";
            }
        }
    }

    return 0;
}
