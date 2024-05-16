#include <array>
#include <string>

int main() {
  std::array<double, 3> vec;
  vec[2] = 10.;

  std::array<std::string, 10> vec2;
  vec2[8] = "mars";
}