#include <iostream>


int main() {
    int c;
    std::cin >> c;
    try {
        if (c < 10) {
            throw std::out_of_range("Invalid Input!");
        };
    }
    catch (std::out_of_range& e) {
        std::cout << e.what() << std::endl;
    }
    return 0;
}
