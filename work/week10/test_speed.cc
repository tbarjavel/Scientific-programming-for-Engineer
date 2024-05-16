#include <iostream>

int foo(const int &i) {return i + 18;}

int main(){
  unsigned long res = 0;
  for (long i = 1; i < 1000000000; ++i){
    res += i + foo(i);
  }
  std::cout << "Hello, World!" << res << std::endl;
  return 0;
}