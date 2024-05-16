#include <iostream>

void foo1() { std::cout << "Hey" << std::endl; }

int main() {

  // call a standard function
  foo1();

  auto foo2 = []() { std::cout << "Hey again !" << std::endl; };

  foo2();

  auto foo3 = [](int a, double b) { std::cout << a << "," << b << std::endl; };

  foo3(10, 102.3);

  int toto = 2;
  // captures 'toto' variable
  auto foo4 = [toto]() { std::cout << toto << std::endl; };

  foo4();

  // captures all in current scope
  auto foo5 = [&]() { std::cout << toto << std::endl; };

  foo5();

  // explicit declaration
  auto foo6 = []() -> int { return 19; };
  auto res = foo6();

  // implicit declaration
  auto foo7 = []() { return 19.3; };
  auto res2 = foo7();
}