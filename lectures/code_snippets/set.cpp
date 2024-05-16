#include <set>

int main() {
  std::set<int> set1;
  set1.insert(100);
  set1.insert(101);
  set1.insert(101);
  set1.erase(100);
}