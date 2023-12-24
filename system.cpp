// system.cpp

#include "system.h"
#include <algorithm>
#include <iomanip>  // Добавим для форматирования вывода
#include <fstream> // Для записи в файл
#include <map>

System::System(const std::string& username, const std::string& password)
    : adminUsername(username), adminPassword(password), totalDeposited(0.0), totalWithdrawn(0.0) {System::readClientsFromFile();}

bool System::login(const std::string& username, const std::string& password) {
    if (username == adminUsername && password == adminPassword) {
        std::cout << "Successfully logged in!\n";
        std::cout << "--------------------------------------------------------------\n";
        return true;
    } else {
        std::cout << "Login failed. Please check your username and password.\n";
        std::cout << "--------------------------------------------------------------\n";
        return false;
    }
}
void writeClientToFile(const Client& newClient) {
    // Открываем файл для записи в конец
    std::ofstream file("D:\\Github rep\\bonuscard-test\\clients.txt", std::ios::app);

    if (file.is_open()) {
        // Записываем информацию о новом клиенте
        file << "Client Name: " << newClient.getName() << "\n";
        file << "Card Number: " << newClient.getBonusCard().getCardNumber() << "\n";
        file << "Balance: " << newClient.getBonusCard().getBalance() << "\n\n";

        // Закрываем файл
        file.close();
    } else {
        std::cout << "Unable to open file for writing.\n";
    }
}

void System::registerClient() {
    std::string clientName;
    std::cout << "Enter client name: ";
    std::cin >> clientName;

    // Создаем объект клиента и регистрируем его
    Client newClient(clientName);
    newClient.registerClient();

    // Добавляем клиента в вектор
    clients.push_back(newClient);

    //Записываем клиента в файл
    writeClientToFile(newClient);
}

void System::displayAllClients() const {
    if (clients.empty()) {
        std::cout << "No clients registered yet.\n";
        return;
    }

    // Выводим заголовок таблицы
    std::cout << std::setw(20) << "Client Name" << std::setw(15) << "Card Number" << std::setw(10) << "Balance\n";
    std::cout << "-----------------------------------------------\n";

    // Выводим информацию о каждом клиенте
    for (const Client& client : clients) {
        std::cout << std::setw(20) << client.getName() << std::setw(15) << client.getBonusCard().getCardNumber()
                  << std::setw(10) << client.getBonusCard().getBalance() << "\n";
    }
}

void System::readClientsFromFile() {
        std::ifstream file("D:\\Github rep\\bonuscard-test\\clients.txt");

        if (!file.is_open()) {
            std::cerr << "Unable to open file: " << std::endl;
            return;
        }

        std::string line;
        std::string name;
        int cardNumber;
        double balance;

        while (std::getline(file, line)) {
            if (line.find("Client Name: ") != std::string::npos) {
                name = line.substr(13);
            } else if (line.find("Card number: ") != std::string::npos) {
                cardNumber = std::stoi(line.substr(13));
            } else if (line.find("Balance: ") != std::string::npos) {
                balance = std::stod(line.substr(9));

                // Создаем объекты BonusCard и Client и добавляем их в вектор
                BonusCard card;
                card.cardNumber = cardNumber;
                card.balance = balance;

                Client client(name);
                client.card = card;

                clients.push_back(client);
            }
        }

        file.close();
    }

void System::findClient(const std::string& clientName) const {
    std::ifstream file("D:\\Github rep\\bonuscard-test\\clients.txt");

    if (file.is_open()) {
        std::string line;
        bool found = false;

        while (getline(file, line)) {
            if (line.find("Client Name: " + clientName) != std::string::npos) {
                found = true;

                // Выводим заголовок таблицы
                std::cout << std::setw(20) << "Client Name" << std::setw(15) << "Card Number" << std::setw(10) << "Balance\n";
                std::cout << "-----------------------------------------------\n";

                // Выводим информацию о клиенте
                std::cout << std::setw(20) << clientName;

                for (int i = 0; i < 2; ++i) {
                    getline(file, line);
                    std::cout << std::setw(15) << line.substr(line.find(": ") + 2);
                }

                std::cout << "\n";
                break;
            }
        }

        if (!found) {
            std::cout << "Client not found.\n";
        }

        file.close();
    } else {
        std::cout << "Unable to open file for reading.\n";
    }
}

int System::findCardNumberByName(const std::string& clientName) const {
    std::ifstream file("D:\\Github rep\\bonuscard-test\\clients.txt");

    if (file.is_open()) {
        std::string line;
        int cardNumber = -1;

        while (std::getline(file, line)) {
            if (line.find("Client Name: " + clientName) != std::string::npos) {
                // Найден клиент, теперь найдем номер его бонусной карты
                while (std::getline(file, line)) {
                    if (line.find("Card Number: ") != std::string::npos) {
                        cardNumber = std::stoi(line.substr(13));
                        break;
                    }
                }
                break;
            }
        }

        file.close();
        return cardNumber;
    } else {
        std::cout << "Unable to open file for reading.\n";
        return -1;
    }
}

void System::recordOperation(const std::string& clientName, char operationType, double amount) {
    int cardNumber = findCardNumberByName(clientName);

    if (cardNumber != -1) {
        std::ofstream file("D:\\Github rep\\bonuscard-test\\operations.txt", std::ios::app);

        if (file.is_open()) {
            file << "Client Name: " << clientName << "\n";
            file << "Card Number: " << cardNumber << "\n";
            file << "Operation Type: " << (operationType == '+' ? "Deposit" : "Withdrawal") << "\n";
            file << "Amount: " << amount << "\n\n";

            file.close();
        } else {
            std::cout << "Unable to open file for writing.\n";
        }
    } else {
        std::cout << "Client not found. Unable to record operation.\n";
    }
}

void System::performOperation(const std::string& clientName, char operationType, double amount) {
    auto it = std::find_if(clients.begin(), clients.end(),
                           [&clientName](const Client& client) { return client.getName() == clientName; });

    if (it != clients.end()) {
        if (operationType == '+') {
            it->getBonusCard().addToBalance(amount);
            totalDeposited += amount;
        } else if (operationType == '-') {
            it->getBonusCard().withdrawFromBalance(amount);
            totalWithdrawn += amount;
        }

        updateClientInFile(*it);
        std::cout << "Operation successful! Updated balance for client " << clientName << ": " << it->getBonusCard().getBalance() << "\n";
        recordOperation(clientName, operationType, amount);
    } else {
        std::cout << "Client not found. Operation failed.\n";
    }
}

void System::displayClientOperationHistory(const std::string& clientName) const {
    std::ifstream file("D:\\Github rep\\bonuscard-test\\operations.txt");

    if (file.is_open()) {
            std::string line;
            bool isClientFound = false;
            std::string operationType;
            std::string amount;
            std::cout << std::setw(20) << "Operation type" << " | " << std::setw(10) << "Amount" << '\n';
            while (std::getline(file, line)) {
                if (line.find("Client Name: " + clientName) != std::string::npos) {
                    isClientFound = true;
                    std::cout << std::string(40, '-') << '\n';  // Выводим разделитель
                } else if (isClientFound && (line.find("Client Name: ") != std::string::npos)) {
                  std::getline(file, line);
                  std::getline(file, line);
                  std::getline(file, line);

                } else if (isClientFound) {
                    if (line.find("Operation Type: ") != std::string::npos) {
                        operationType = line.substr(line.find(": ") + 2);  // Извлекаем тип операции
                    } else if (line.find("Amount: ") != std::string::npos) {
                        amount = line.substr(line.find(": ") + 2);  // Извлекаем количество баллов
                        std::cout << std::setw(20) << operationType << " | " << std::setw(10) << amount << '\n';  // Выводим строку таблицы
                    }
                }
            }

            if (!isClientFound) {
                std::cout << "Client not found in the operation history.\n";
            }

            file.close();
        } else {
            std::cout << "Unable to open file for reading.\n";
        }
    }

void System::displayClientSummary(const std::string& clientName) const {
    auto it = std::find_if(clients.begin(), clients.end(),
                           [&clientName](const Client& client) { return client.getName() == clientName; });

    if (it != clients.end()) {
        const BonusCard& bonusCard = it->getBonusCard();
        double totalDeposit = bonusCard.getTransactionsTotal(Transaction::OperationType::Deposit);
        double totalWithdraw = bonusCard.getTransactionsTotal(Transaction::OperationType::Withdrawal);

        // Выводим заголовок таблицы
        std::cout << std::setw(15) << "Client Name" << std::setw(15) << "Total deposit" << std::setw(15) << "Total withdraw"
                  << std::setw(15) << "Balance\n";
        std::cout << "---------------------------------------------------------------------\n";

        // Выводим информацию о клиенте
        std::cout << std::setw(15) << clientName << std::setw(15) << totalDeposit << std::setw(15) << totalWithdraw
                  << std::setw(15) << bonusCard.getBalance() << "\n";
    } else {
        std::cout << "Client not found. Unable to display summary.\n";
    }
}


void System::depositToClientBalance(const std::string& clientName, double amount) {
    auto it = std::find_if(clients.begin(), clients.end(),
                           [&clientName](const Client& client) { return client.getName() == clientName; });

    if (it != clients.end()) {
        // Пополняем баланс клиента
        it->getBonusCard().addToBalance(amount);

        // Обновляем суммарную информацию
        totalDeposited += amount;
        std::cout << "Deposit successful! Updated balance for client " << clientName << ": " << it->getBonusCard().getBalance() << "\n";

        // Обновляем информацию в файле
        updateClientInFile(*it);
    } else {
        std::cout << "Client not found. Deposit failed.\n";
    }
}

void System::withdrawFromClientBalance(const std::string& clientName, double amount) {
    auto it = std::find_if(clients.begin(), clients.end(),
                           [&clientName](const Client& client) { return client.getName() == clientName; });

    if (it != clients.end()) {
        // Пополняем баланс клиента
        it->getBonusCard().withdrawFromBalance(amount);

        // Обновляем суммарную информацию
        totalDeposited -= amount;
        std::cout << "withdraw successful! Updated balance for client " << clientName << ": " << it->getBonusCard().getBalance() << "\n";

        // Обновляем информацию в файле
        updateClientInFile(*it);
    } else {
        std::cout << "Client not found. Deposit failed.\n";
    }
}

void System::updateClientInFile(const Client& updatedClient) const {
    std::ifstream inFile("D:\\Github rep\\bonuscard-test\\clients.txt");
        std::ofstream outFile("D:\\Github rep\\bonuscard-test\\temp.txt");
        int count = 1;

        if (inFile.is_open() && outFile.is_open()) {
            std::string line;

            while (getline(inFile, line)) {
                if (line.find("Client Name: " + updatedClient.getName()) != std::string::npos) {
                    count = -1;
                    outFile << line << std::endl;
                } else {
                    if ((line.find("Balance: ") != std::string::npos) && (count == 1)) {
                        outFile << "Balance: " << updatedClient.getBonusCard().getBalance() << std::endl;
                    }
                    else {
                        outFile << line << std::endl;
                    }
                }
                count++;
            }

            inFile.close();
            outFile.close();

            remove("D:\\Github rep\\bonuscard-test\\clients.txt");
            rename("D:\\Github rep\\bonuscard-test\\temp.txt", "D:\\Github rep\\bonuscard-test\\clients.txt");

            std::cout << "Client information updated in file.\n";
        } else {
            std::cout << "Unable to open file for updating.\n";
        }
}

void System::displayClientsFromFile() const {
    std::ifstream file("D:\\Github rep\\bonuscard-test\\clients.txt");

    if (file.is_open()) {
            std::string line;
            std::string clientName;
            std::string cardNumber;
            std::string balance;

            std::cout << std::setw(20) << "Client Name" << " | " << std::setw(20) << "Card Number" << " | " << std::setw(10) << "Balance" << '\n';
            std::cout << std::string(60, '-') << '\n';  // Выводим разделитель

            while (getline(file, line)) {
                if (line.find("Client Name: ") != std::string::npos) {
                    clientName = line.substr(line.find(": ") + 2);  // Извлекаем имя клиента
                } else if (line.find("Card Number: ") != std::string::npos) {
                    cardNumber = line.substr(line.find(": ") + 2);  // Извлекаем номер карты
                } else if (line.find("Balance: ") != std::string::npos) {
                    balance = line.substr(line.find(": ") + 2);  // Извлекаем баланс
                    std::cout << std::setw(20) << clientName << " | " << std::setw(20) << cardNumber << " | " << std::setw(10) << balance << '\n';  // Выводим строку таблицы
                }
            }

            file.close();
        } else {
            std::cout << "Unable to open file for reading.\n";
        }
    }
void System::displayClientTransactionHistory(const std::string& clientName) const {
    auto it = std::find_if(clients.begin(), clients.end(),
                           [&clientName](const Client& client) { return client.getName() == clientName; });

    if (it != clients.end()) {
        it->displayInfo();
    } else {
        std::cout << "Client not found. Unable to display transaction history.\n";
    }
}

/*void System::displayAnnualReport() const { //НЕТУ НОМЕРА КАРТЫ
    std::ifstream file("D:\\Github rep\\bonuscard-test\\operations.txt");

    if (file.is_open()) {
        std::string line;
        std::string clientName;
        std::string operationType;
        std::string amount;
        std::map<std::string, std::tuple<int, double, double>> clientOperations;  // Карта для хранения операций каждого клиента

        while (std::getline(file, line)) {
            if (line.find("Client Name: ") != std::string::npos) {
                clientName = line.substr(line.find(": ") + 2);  // Извлекаем имя клиента
            } else if (line.find("Card Number: ") != std::string::npos) {
                int cardNumber = std::stoi(line.substr(line.find(": ") + 2));  // Извлекаем номер карты клиента
                clientOperations[clientName] = std::make_tuple(cardNumber, 0.0, 0.0);
            } else if (line.find("Operation Type: ") != std::string::npos) {
                operationType = line.substr(line.find(": ") + 2);  // Извлекаем тип операции
            } else if (line.find("Amount: ") != std::string::npos) {
                amount = line.substr(line.find(": ") + 2);  // Извлекаем количество баллов
                if (operationType == "Deposit") {
                    std::get<1>(clientOperations[clientName]) += std::stod(amount);
                } else if (operationType == "Withdrawal") {
                    std::get<2>(clientOperations[clientName]) += std::stod(amount);
                }
            }
        }

        std::cout << std::setw(20) << "Client Name" << " | " << std::setw(20) << "Card number" << " | "
                  << std::setw(10) << "Deposit" << " | " << std::setw(10) << "Widthdraw" << " | "
                  << std::setw(20) << "Balance" << '\n';
        std::cout << std::string(90, '-') << '\n';  // Выводим разделитель

        double totalDeposited = 0;
        double totalWithdrawn = 0;

        for (const auto& client : clientOperations) {
            totalDeposited += std::get<1>(client.second);
            totalWithdrawn += std::get<2>(client.second);
            std::cout << std::setw(20) << client.first << " | " << std::setw(20) << std::get<0>(client.second)
                      << " | " << std::setw(10) << std::get<1>(client.second) << " | "
                      << std::setw(10) << std::get<2>(client.second) << " | "
                      << std::setw(20) << (std::get<1>(client.second) - std::get<2>(client.second)) << '\n';  // Выводим строку таблицы
        }

        std::cout << "All deposit: " << totalDeposited << '\n';
        std::cout << "All widthdraw: " << totalWithdrawn << '\n';

        file.close();
    } else {
        std::cout << "Unable to open file for reading.\n";
    }
}*/

void System::displayAnnualReport() const {
    std::ifstream file("D:\\Github rep\\bonuscard-test\\operations.txt");

    if (file.is_open()) {
        std::string line;
        std::string clientName;
        int cardNumber;  // Добавляем переменную для хранения номера карты
        std::string operationType;
        std::string amount;
        std::map<std::string, std::tuple<int, double, double>> clientOperations;  // Изменяем структуру хранения операций каждого клиента

        while (std::getline(file, line)) {
            if (line.find("Client Name: ") != std::string::npos) {
                clientName = line.substr(line.find(": ") + 2);  // Извлекаем имя клиента
            } else if (line.find("Card Number: ") != std::string::npos) {
                cardNumber = std::stoi(line.substr(line.find(": ") + 2));  // Извлекаем номер карты
            } else if (line.find("Operation Type: ") != std::string::npos) {
                operationType = line.substr(line.find(": ") + 2);  // Извлекаем тип операции
            } else if (line.find("Amount: ") != std::string::npos) {
                amount = line.substr(line.find(": ") + 2);  // Извлекаем количество баллов
                if (operationType == "Deposit") {
                    std::get<1>(clientOperations[clientName]) += std::stod(amount);
                } else if (operationType == "Withdrawal") {
                    std::get<2>(clientOperations[clientName]) += std::stod(amount);
                }
            }
        }

        std::cout << std::setw(20) << "Client Name" << " | " << std::setw(20) << "Card Number" << " | " << std::setw(10) << "Deposit" << " | " << std::setw(10) << "Withdraw" << " | " << std::setw(20) << "Balance" << '\n';
        std::cout << std::string(90, '-') << '\n';  // Выводим разделитель

        double totalDeposited = 0;
        double totalWithdrawn = 0;

        for (const auto& client : clientOperations) {
            totalDeposited += std::get<1>(client.second);
            totalWithdrawn += std::get<2>(client.second);
            std::cout << std::setw(20) << client.first << " | " << std::setw(20) << std::get<0>(client.second) << " | " << std::setw(10) << std::get<1>(client.second) << " | " << std::setw(10) << std::get<2>(client.second) << " | " << std::setw(20) << (std::get<1>(client.second) - std::get<2>(client.second)) << '\n';  // Выводим строку таблицы
        }

        std::cout << "Total Deposit: " << totalDeposited << '\n';
        std::cout << "Total Withdraw: " << totalWithdrawn << '\n';

        file.close();
    } else {
        std::cout << "Unable to open file for reading.\n";
    }
}
