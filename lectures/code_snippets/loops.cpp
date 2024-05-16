#include <array>
#include <vector>

int main() {

  std::vector<int> vec(10);
  for (int i = 0; i < 10; ++i) {
    vec[i] = 10;
  }

  std::array<int, 10> array;
  for (int i = 0; i < 10; ++i) {
    array[i] = 10;
  }

  {
    // vector loop with iterators
    std::vector<int>::iterator it = vec.begin();
    std::vector<int>::iterator end = vec.end();
    for (; it != end; ++it) {
      *it = 10.;
    }
  }

  {
    // with the auto
    auto it = vec.begin();
    auto end = vec.end();
    for (; it != end; ++it) {
      *it = 10.;
    }
  }

  {
    // with the range loop
    for (auto &v : vec) {
      v = 10.;
    }
  }
}