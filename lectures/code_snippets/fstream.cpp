#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>

int main() {

  std::ofstream fout("test.plot");
  fout << M_PI << std::endl;
  fout.close();

  double pi_val;
  std::ifstream fin("test.plot");
  fin >> pi_val;
  std::cout << pi_val << std::endl;
  fin.close();
}