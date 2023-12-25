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
            std::cout << "2. Operations with client balance\n"; //+
            std::cout << "3. Display client transaction history\n";
            std::cout << "4. Display annual report\n";
            std::cout << "5. Display all clients\n"; //+
            std::cout << "6. Find client\n"; //+
            std::cout << "7. Exit\n";
            std::cout << "Enter your choice: ";

            int choice;
            std::cin >> choice;

            switch (choice) {
                case 1: {
                    // Регистрация нового клиента
                    mySystem.registerClient();
                    system("pause");
                    system("cls");
                    break;
                }
            case 2: {
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
                system("pause");
                system("cls");
                break;
            }

            case 3: {
                // Вывод истории операций для конкретного клиента
                    std::string clientForHistory;
                    std::cout << "Enter client name: ";
                    std::cin >> clientForHistory;

                    mySystem.displayClientOperationHistory(clientForHistory);
                    system("pause");
                    system("cls");
                    break;
            }
                case 4: {
                    // Вывод годового отчета
                    mySystem.displayAnnualReport();
                    system("pause");
                    system("cls");
                    break;
                }
                case 5: {
                    // Вывод информации о всех клиентах
                    mySystem.displayClientsFromFile();
                    system("pause");
                    system("cls");
                    break;
                }
            case 6: {
                // Поиск клиента
                std::string clientToFind;
                std::cout << "Enter client name to find: ";
                std::cin >> clientToFind;

                mySystem.findClient(clientToFind);
                system("pause");
                system("cls");
                break;
            }
                case 7: {
                    // Выход из программы
                    exitMenu = true;
                    system("pause");
                    system("cls");
                    break;
                }
                default:
                    std::cout << "Invalid choice. Please enter a valid option.\n";
            }
        }
    }

    return 0;
}
