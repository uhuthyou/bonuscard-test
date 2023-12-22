// main.cpp

#include "system.h"

int main() {
    // Создаем объект системы
    System mySystem("1234", "1234");

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
    }

    return 0;
}
