#include <algorithm>
#include <iostream>
#include <vector>

int main() {

  std::vector<int> vec(10);

  // indirect call
  auto foo = [](auto &v) { std::cout << v; };
  std::for_each(vec.begin(), vec.end(), foo);

  // inline call
  std::for_each(vec.begin(), vec.end(), [](auto &v) { v += 1; });

  // storing result in another array
  std::vector<int> res;
  std::transform(vec.begin(), vec.end(), std::back_inserter(res),
                 [](auto &val) { return val + 1; });
}