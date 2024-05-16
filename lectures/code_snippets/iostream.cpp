#include <iostream>

int main() {
  int obj;

  std::cout << obj << std::endl;

  std::cout << "flush now!" << std::flush << std::endl;

  std::cerr << obj << std::endl;
}