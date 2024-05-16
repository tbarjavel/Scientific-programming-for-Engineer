#include <vector>
#include <array>
#include <memory>
#include <iostream>


int main() {

    // stack array
    // int values[10];
    std::array<int, 10> values;
    for (int& v : values) {
        v = 0;
    }
    std::cout << "stack array: ";
    for (int i = 0; i < 10; ++i) {
        std::cout << values[i] << " ";
    }
    std::cout << std::endl;

    // heap array
    // int *values2 = new int[10];
    std::vector<int> values2(10);
    for (int i = 0; i < 10; ++i) {  // cannot use default iterator
        values2[i] = 0;
    }
    std::cout << "heap array: ";
    for (int i = 0; i < 10; ++i) {
        std::cout << values2[i] << " ";
    }
    std::cout << std::endl;
    // delete[] values2;

    return 0;
}
