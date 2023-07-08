#include "src/acl.h"

#include <iostream>

int main() {

    // Creating an ACL instance.
    access::ACL<std::string, std::string, std::string> acl;

    std::cout << "id = ";
    std::cout << acl.GetId("asdfdd");
    std::cout << std::endl;

    // Adding an entity and giving it access to a resource.
    std::cout << "\nAdding an entity and giving it access to a resource.\n";
    acl.AddEntity(1, "resource1", "read");
    acl.ShowEntities();
    acl.AddEntity(1, "resource1", "write");
    acl.ShowEntities();
    std::cout << std::endl;
    acl.AddEntity(2, "resource1", "write");
    acl.ShowEntities();

    // Getting access to a resource for an entity.
    std::cout << "\nGetting access to a resource for an entity.\n";
    std::cout << acl.GetAccessMode(1, "resource1") << std::endl;  // Output: read.
    std::cout << acl.GetAccessMode(2, "resource1") << std::endl;  // Output: write.

    // Setting a new resource access for the entity.
    std::cout << "\nSetting a new resource access for the entity.";
    try {
        acl.SetAccessMode(2, "resource1", "read");
    } catch (const std::out_of_range& msg) {
        std::cerr << msg.what() << std::endl;
    }

    // Checking the changed access.
    std::cout << "\nChecking the changed access.\n" << std::endl;
    std::cout << acl.GetAccessMode(2, "resource1") << std::endl;  // Вывод: read.

    // Deleting an entity from the ACL.
    std::cout << "\nDeleting an entity from the ACL.\n" << std::endl;
    acl.DelEntity(1);
    acl.ShowEntities();

    // An attempt to gain access for a remote entity.
    std::cout << "\nAn attempt to gain access for a remote entity.\n";
    try {
        std::cout << acl.GetAccessMode(1, "resource1") << std::endl;
    } catch (const std::out_of_range& msg) {
        std::cerr << msg.what() << std::endl;
    }

    acl.ShowEntities();

    return 0;
}