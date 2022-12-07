#include <iostream>
#include <string>

int main() {
    int x;
    int sum = 0;
    while (std::cin >> x) {
        sum += x;
    }
    std::cout << std::to_string(sum);
}
