#include <iostream>
#include <string>
int main() {
    int x;
    std::string str = "";
    while (std::cin >> x) {
        str += std::to_string(7 * x);
        str += ' ';
    }
    std::cout << str;
}
