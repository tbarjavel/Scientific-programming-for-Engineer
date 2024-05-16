#include <iostream>
#include <memory>

std::shared_ptr<double> get_vector(int n) {
  return std::shared_ptr<double>(new double[n]);
}

int main() {

  std::shared_ptr<double> ptr1 = get_vector(10);
  std::shared_ptr<double> ptr2 = ptr1;

  // memory of pointer freed when ptr1 and ptr2 are out of scope
}