// system.cpp

#include "system.h"
#include <algorithm>
#include <iomanip>  // Добавим для форматирования вывода
#include <fstream> // Для записи в файл

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

void System::recordOperation(const std::string& clientName, char operationType, double amount) {
    std::ofstream file("D:\\Github rep\\bonuscard-test\\operations.txt", std::ios::app);

    if (file.is_open()) {
        file << "Client Name: " << clientName << "\n";
        file << "Operation Type: " << (operationType == '+' ? "Deposit" : "Withdrawal") << "\n";
        file << "Amount: " << amount << "\n\n";

        file.close();
    } else {
        std::cout << "Unable to open file for writing.\n";
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

        while (std::getline(file, line)) {
            if (line.find("Client Name: " + clientName) != std::string::npos) {
                isClientFound = true;
                std::cout << line << '\n';  // Выводим строку с именем клиента
            } else if (isClientFound && (line.find("Client Name: ") != std::string::npos)) {
                std::getline(file, line);
                std::getline(file, line);
                std::getline(file, line);
            } else if (isClientFound) {
                // Выводим строки с информацией об операции для найденного клиента
                std::cout << line << '\n';
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
        while (getline(file, line)) {
            std::cout << line << '\n';
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

void System::displayAnnualReport() const {
    // Выводим заголовок таблицы
    std::cout << std::setw(20) << "Client Name" << std::setw(15) << "Card Number" << std::setw(20) << "Total Deposited"
              << std::setw(20) << "Total Withdrawn" << std::setw(20) << "Current Balance\n";
    std::cout << "--------------------------------------------------------------------------------\n";

    // Выводим информацию о каждом клиенте
    for (const auto& client : clients) {
        const BonusCard& bonusCard = client.getBonusCard();
        std::cout << std::setw(20) << client.getName() << std::setw(15) << bonusCard.getCardNumber()
                  << std::setw(20) << bonusCard.getTransactionsTotal(Transaction::OperationType::Deposit)
                  << std::setw(20) << bonusCard.getTransactionsTotal(Transaction::OperationType::Withdrawal)
                  << std::setw(20) << bonusCard.getBalance() << "\n";
    }

    // Выводим информацию о суммарных начислениях и списаниях
    std::cout << "\nTotal Deposited: " << totalDeposited << "\n";
    std::cout << "Total Withdrawn: " << totalWithdrawn << "\n";
}
