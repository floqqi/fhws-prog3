#include <iostream>
#include "List.h"

int main() {
    List<int> myList;

    myList.pushBack(1);
    myList.pushBack(2);
    myList.pushBack(3);

    std::cout << "Elements…" << '\n';
    std::cout << myList[0] << '\n';
    std::cout << myList[1] << '\n';
    std::cout << myList[2] << '\n';
    std::cout << std::endl;

    myList.removeAt(0);

    std::cout << "Elements after deletion…" << '\n';
    std::cout << myList[0] << '\n';
    std::cout << myList[1] << '\n';
    std::cout << std::endl;

    return 0;
}
