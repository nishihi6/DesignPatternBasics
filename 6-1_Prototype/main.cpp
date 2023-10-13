#include "Manager.h"
#include "UnderlinePen.h"
#include "MessageBox.h"

int main() {
    Manager manager;
    UnderlinePen upen('~');
    MessageBox mbox('*');
    MessageBox sbox('/');

    manager.registerProduct("strong message", &upen);
    manager.registerProduct("warning box", &mbox);
    manager.registerProduct("slash box", &sbox);

    Product* p1 = manager.create("strong message");
    p1->use("Hello, world.");

    Product* p2 = manager.create("warning box");
    p2->use("Hello, world.");

    Product* p3 = manager.create("slash box");
    p3->use("Hello, world.");

    // Cleanup
    delete p1;
    delete p2;
    delete p3;

    return 0;
}