#include <vector>
#include <array>
#include <memory>
#include <iostream>


int main() {
  auto unique = std::make_unique<std::vector<int>>(10);

  std::unique_ptr<std::vector<int>> other = nullptr;
  other = unique;
}
