#include <vector>
#include <array>
#include <memory>
#include <iostream>

int main() {
  int values;

  for (int& v : values)
    v = 0;

  for (int i = 0; i < 10; ++i)
    std::cout << values[i] << " ";
  std::cout << std::endl;
  return 0;
}
