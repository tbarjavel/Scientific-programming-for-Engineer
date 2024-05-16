#include <iostream>
#include <sstream>

int main() {
  std::stringstream sstr("1 2 3.14");
  int i, j;
  double k;

  sstr >> i >> j >> k;
  std::cout << i << " " << j << " " << k << std::endl;

  std::stringstream sstr2;
  sstr2 << 142;
  std::cout << sstr2.str() << std::endl;
}