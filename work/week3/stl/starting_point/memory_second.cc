#include <vector>
#include <array>
#include <memory>
#include <iostream>


std::vector<int>* stack_allocation(int n) {
    std::vector<int> stack_vec(n);
    return &stack_vec;
}

std::vector<int>* heap_allocation(int n) {
    return new std::vector<int>(n);
}

std::unique_ptr<std::vector<int>> heap_allocation_cpp14(int n) {
    return std::make_unique<std::vector<int>>(n);
}


int main() {
    std::vector<int>* stack_values = stack_allocation(10);
    // std::cout << "size of stack array: " << stack_values->size() << std::endl; // -->seg fault !!!

    // std::vector<int>* heap_values = heap_allocation(10);
    std::unique_ptr<std::vector<int>> heap_values = heap_allocation_cpp14(10);
    std::cout << "size of heap array: " << heap_values->size() << std::endl;
    // would require delete statement: delete [] heap_values; ???
    // delete[] heap_values;  // --> seg fault !!!

    return 0;
}
