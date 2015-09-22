#include <iostream>

#include <lockfreestack.h>

int main(int argc, char** argv) try {
    lockfree::LockfreeStack<int> stack;
    stack.push(0);
    stack.push(1);

    while (auto res = stack.pop())
        std::cout << *res << " ";
    std::cout << std::endl;

    return 0;
}
catch (std::exception& e) {
    std::cerr << e.what() << std::endl;
    return 0;
}
