#include "acl.h"

#include <iostream>

int main() {

    // Создание экземпляра ACL
    access::ACL<std::string, std::string, std::string> acl;


    std::cout << acl.getId("asdfdd");

    // Добавление сущности и установка ей доступа к ресурсу
    acl.AddEntity(1, "resource1", "read");
    acl.ShowEntities();
    acl.AddEntity(1, "resource1", "write");
    acl.ShowEntities();
    acl.AddEntity(2, "resource1", "write");

    // Получение доступа к ресурсу для сущности
    std::cout << acl.GetAccessMode(1, "resource1") << std::endl;  // Вывод: read
    std::cout << acl.GetAccessMode(2, "resource1") << std::endl;  // Вывод: write

    // Установка нового доступа к ресурсу для сущности
    try {
        acl.SetAccessMode(2, "resource1", "read");
    } catch (const std::out_of_range& msg) {
        std::cerr << msg.what() << std::endl;
    }

    // Проверка измененного доступа
    std::cout << acl.GetAccessMode(2, "resource1") << std::endl;  // Вывод: read

    // Удаление сущности из ACL
    acl.DelEntity(1);
    acl.DelEntity(1000);

    // Попытка получить доступ для удаленной сущности
    try {
        std::cout << acl.GetAccessMode(1, "resource1") << std::endl;
    } catch (const std::out_of_range& msg) {
        std::cerr << msg.what() << std::endl;
    }

    acl.SetAccessMode(4, "resource1", "read");

    acl.ShowEntities();

    return 0;
}