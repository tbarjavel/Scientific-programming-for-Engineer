#include <iomanip>
#include <iostream>
#include <cmath>

int main(){
    
  // for this output
  std::cout << std::scientific 
            << std::setprecision(15)
            << M_PI << std::endl;
            
  //permanent
  std::cout.precision(15);
  std::cout.setf(std::ios::scientific);
}