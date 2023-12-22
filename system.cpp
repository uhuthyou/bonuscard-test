// system.cpp

#include "system.h"
#include <algorithm>
#include <iomanip>  // Добавим для форматирования вывода
#include <fstream> // Для записи в файл

System::System(const std::string& username, const std::string& password)
    : adminUsername(username), adminPassword(password), totalDeposited(0.0), totalWithdrawn(0.0) {}

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
    std::ofstream file("D:/Github rep/bonuscard-test/clients.txt", std::ios::app);

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

void System::depositToClientBalance(const std::string& clientName, double amount) {
    auto it = std::find_if(clients.begin(), clients.end(),
                           [&clientName](const Client& client) { return client.getName() == clientName; });

    if (it != clients.end()) {
        // Если клиент найден, пополняем его баланс
        it->getBonusCard().addToBalance(amount);

        // Обновляем суммарную информацию
        totalDeposited += amount;
        std::cout << "Deposit successful! Updated balance for client " << clientName << ": " << it->getBonusCard().getBalance() << "\n";
        //it->displayInfo();
    } else {
        std::cout << "Client not found. Deposit failed.\n";
    }
}

void System::readClientsFromFile() const {
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

void System::withdrawFromClientBalance(const std::string& clientName, double amount) {
    auto it = std::find_if(clients.begin(), clients.end(),
                           [&clientName](const Client& client) { return client.getName() == clientName; });

    if (it != clients.end()) {
        // Если клиент найден, списываем бонусы с его баланса
        it->withdrawFromBalance(amount);

        // Обновляем суммарную информацию
        totalWithdrawn += amount;
        std::cout << "Withdrawal successful!\n";        std::cout << "Withdrawal successful! Updated balance for client " << clientName << ": " << it->getBonusCard().getBalance() << "\n";
        //it->displayInfo();
    } else {
        std::cout << "Client not found. Withdrawal failed.\n";
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
