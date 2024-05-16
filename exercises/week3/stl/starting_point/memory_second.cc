#include <vector>
#include <array>
#include <memory>
#include <iostream>

std::vector<int>* stack_allocation(int n) {
  return nullptr;
}

std::vector<int>* heap_allocation(int n) {
  return nullptr;
}

int main() {
  std::vector<int> * stack_values = stack_allocation(10);
  std::vector<int> * heap_values = heap_allocation(10);

  std::cout << stack_values->size() << ", " << heap_values->size() << std::endl;
  return 0;
}
