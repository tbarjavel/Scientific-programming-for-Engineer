#include <iostream>
#include <memory>

std::unique_ptr<double> get_scalar() {
  // create a unique pointer
  return std::make_unique<double>(3);
}

int main() {

  std::unique_ptr<double> ptr = get_scalar();
  // ... do what I need like...
  std::cout << *ptr;
  // no need to delete scalar (will be automatically)

  // cannot be copied => compilation error
  // std::unique_ptr<double> ptr_copy = ptr;
}