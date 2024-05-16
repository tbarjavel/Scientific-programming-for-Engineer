#include <vector>
#include <array>
#include <memory>
#include <iostream>


int main() {

    // Cannot share unique pointers
    // auto unique = std::make_unique<std::vector<int>>(10);
    // std::unique_ptr<std::vector<int>> other = nullptr;
    // other = unique;

    // Solution: work with shared pointers
    auto shared = std::shared_ptr<std::vector<int>>(new std::vector<int>(10));
    std::shared_ptr<std::vector<int>> other = nullptr;
    other = shared;
    std::cout << "Successful!" << std::endl;
}
